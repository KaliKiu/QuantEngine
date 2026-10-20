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

        //sources can emit multiple values.
        template <class T, class F>
        Output<T> addSource(std::string name, F producer){
            const auto id = registerNode(std::move(name), typeid(void), tpyeid(T));

        }

        private:
            struct InternalNode {
                std::string name;
                //warpper of type_info
                std::type_index input;
                std::type_index output;

                std::function<void(const std::any&)> process;
                std::function<void()> source;

                std::vector<std::size_t> downstream;
            };

            std::vector<InternalNode> nodes_;
            std::vector<std::size_t> sources_;

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
    };
}