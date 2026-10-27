#include <iostream>
#include <curl/curl.h>
#include <thread>
#include <variant>

#include "Error/error.hpp"
#include "Engine/engine.hpp"
#include "HttpClient/httpclient.hpp"
#include "Data/marketdata.hpp"
#include "Data/data.hpp"
#include "Data/parser.hpp"



#include "Queue/queue.hpp"
#include "Analyze/analyzer.hpp"
#include "Analyze/momentumanalyzer.hpp"



//EXAMPLE DAG GRAPH FOR API DATA FETCHING + PARSING + SINKING
int main(){
    quant::Engine engine;
    HttpClient http("https://biquote.io/api/latest?&symbols=XAUUSD");
    
    
    auto source = engine.addSource<std::string>("Source",
    //producer lamda
        [&http](auto push){
            for(int i=0; i<10; i++){
                auto data = http.getSingleData();
                if(!data){
                    Error::log_error(data.error());
                    break;
                }
                //push(*data);
                push(*data);
            }
        });

    auto transform = engine.addTransform<std::string, MarketData::Latest>("Transform",
        [](std::string value){
            return Parser::parseLatest(value);
        });

    auto sink = engine.addSink<MarketData::Latest>("Sink",
        [](MarketData::Latest value){
            value.dump();
        });
    
    engine.connect(source, transform.input);
    engine.connect(transform.output, sink);
    engine.run();
}

