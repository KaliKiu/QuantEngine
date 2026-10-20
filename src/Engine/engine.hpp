#pragma once

#include <any>
#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <utility>
#include <vector>
#include <string>

/*changed quant engine to build an dataflow framework
    3 main pillars: 
    -Source -> produces data | out
    -Transform -> processes data | in & out
    -Sink -> consumes data | in
*/

namespace quant {

    class Engine{
        public:

        template <class T>
        struct Output {
            std::size_t id;
        };
        template <class T>
        struct Input {
            std::size_t id;
        };
        template <class In, class Out>
        struct Transform {
            Input <In> input;
            Output <Out> output;
        };

        //sources can emit multiple values., executes when run()
        template <class T, class F>
        Output<T> addSource(std::string name, F&& producer){
            const auto id = registerNode(std::move(name), typeid(void), typeid(T));
            nodes_[id].source = [this,id,producer = std::forward<F>(producer)]() mutable {
                producer([this,id](T value){
                    dispatch(id,std::any(std::move(value)));
                });
            };
            sources_.push_back(id);
            return {id};
        }

        //receives In, produces Out
        template <class In, class Out, class F>
        Transform<In,Out> addTransform(std::string name, F&& transform){
            const auto id = registerNode(std::move(name), typeid(In), typeid(Out));
            nodes_[id].process = [this, id, transform = std::forward<F>(transform)](const std::any& value) mutable{
                auto result = transform(std::any_cast<const In&>(value));
                dispatch(id, std::any(std::move(result)));
            };

            return {{id},{id}};
        }

        
        template<class T, class F>
        Input<T> addSink(std::string name, F&& consumer){
            const auto id = registerNode(std::move(name),typeid(T),typeid(void));
            nodes_[id].process = [consumer = std::forward<F>(consumer)](const std::any& value) mutable{
                consumer(std::any_cast<const T&>(value));
            };
        
            return {id};
        }

        template <class T>
        void connect(Output<T> from, Input<T> to){
            if(from.id >= nodes_.size() || to.id >= nodes_.size()){
                throw std::out_of_range("Unknown component");
            }

            if(nodes_[from.id].output != typeid(T) || nodes_[to.id].input != typeid(T)){
                throw std::logic_error("Incompatible port");
            }

            if(from.id == to.id || reachable(to.id, from.id)) {
                throw std::logic_error("Connection would create a cycle");
            }

            nodes_[from.id].downstream.push_back(to.id);
        }

        void run () {
            for(auto id : sources_){
                nodes_[id].source();
            }
        }

        private:
            //wrapper of an component representing it iwithing execution graph
            struct InternalNode {
                std::string name;

                std::type_index input;
                std::type_index output;

                std::function<void(const std::any&)> process;
                std::function<void()> source;

                std::vector<std::size_t> downstream;
            };

            std::vector<InternalNode> nodes_; //holds all InternalNodes
            std::vector<std::size_t> sources_; //Holds all 

            std::size_t registerNode(std::string name, std::type_index in, std::type_index out) {
                const auto id = nodes_.size();

                nodes_.push_back({
                    std::move(name),
                    in,
                    out,
                    {},{},{}
                });
                return id;
            }

            bool reachable(std::size_t start, std::size_t target) const {
                if(start==target) return true;

                std::vector<bool> visited(nodes_.size(), false);
                std::vector<std::size_t> pending{start};

                while(!pending.empty()) {
                    auto current = pending.back();
                    pending.pop_back();

                    if(visited[current]) continue;
                    visited[current] = true;

                    for(auto next : nodes_[current].downstream){
                        if(next == target) return true;
                        pending.push_back(next);
                    }
                }
                return false;
            }

            void dispatch(std::size_t sender, const std::any& value){
                for(auto next : nodes_[sender].downstream){
                    nodes_[next].process(value);
                }
            }
    };
}