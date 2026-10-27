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
#include "InfluxDB/influxclient.hpp"
#include "InfluxDB/influxserializer.hpp"


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
                push(*data);
            }
        });

    auto transform = engine.addTransform<std::string, MarketData::Latest>("Transform",
        [](std::string value) -> MarketData::Latest{
            return Parser::parseLatest(value);
        });

    auto serialize = engine.addTransform<MarketData::Latest, std::string>("Serialize",
        [](MarketData::Latest value) -> std::string{
            auto result = Influxserializer::serialize_latest(value);
            if(!result){
                Error::log_error(result.error());
            }
            return *result;
        });

    auto sink = engine.addSink<std::string>("Sink",
        [](std::string value){
            std::cout<<value<<std::endl<<std::endl;
        });
    
    engine.connect(source, transform.input);
    engine.connect(transform.output, serialize.input);
    engine.connect(serialize.output,sink);

    engine.run();
}

