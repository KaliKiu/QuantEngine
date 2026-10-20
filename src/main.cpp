#include <iostream>
#include <curl/curl.h>
#include <thread>
#include <variant>
#include "Engine/engine.hpp"

/*
#include "HttpClient/httpclient.hpp"
#include "Config/config.hpp"
#include "Queue/queue.hpp"
#include "Data/marketdata.hpp"
#include "Data/data.hpp"
#include "Data/parser.hpp"
#include "Analyze/analyzer.hpp"
#include "Analyze/momentumanalyzer.hpp"

static constexpr const char* CONFIG_FILE_DIR =  "../data/config.json";

*/

//THREAD SYSTEM IS OUT OF DATE, ITS NOT SAFE THIS WAY. Will be updated
int main(){
    std::cout <<"meow";
    quant::Engine engine;

    auto source = engine.addSource<int>("Source",
        [](auto meow){
            meow(11);
            meow(12);
        });

    auto transform = engine.addTransform<int,double>("Transform",
        [](const int& value)mutable{
            return static_cast<double>(value)+0.1;
        });

    auto sink = engine.addSink<double>("Sink",
        [](const double& value){
            std::cout<<value <<"\n";
        });

    engine.connect(source,transform.input);
    engine.connect(transform.output,sink);
    engine.run();
}

