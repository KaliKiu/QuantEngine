#include <iostream>
#include <curl/curl.h>
#include <thread>
#include <variant>

#include "Error/error.hpp"
#include "Engine/engine.hpp"
#include "HttpClient/httpclient.hpp"
/*


#include "Queue/queue.hpp"
#include "Data/marketdata.hpp"
#include "Data/data.hpp"
#include "Data/parser.hpp"
#include "Analyze/analyzer.hpp"
#include "Analyze/momentumanalyzer.hpp"

static constexpr const char* CONFIG_FILE_DIR =  "../data/config.json";

*/

int main(){
    quant::Engine engine;
    HttpClient http("https://bite.io/api/latest?&symbols=XAUUSD");
    
    
    auto source = engine.addSource<std::string>("Source",
    //producer lamda
        [&http](auto push){
            for(int i=0; i<10; i++){
                auto data = http.getSingleData();
                if(!data){
                    auto err = data.error();
                    std::cerr<<Error::toString(err)<<std::endl;
                    break;
                }
                push(*data);
            }
        });

    auto sink = engine.addSink<std::string>("Sink",
        [](std::string value){
            std::cout<<value <<"\n";
        });

    engine.connect(source,sink);
    engine.run();
}

