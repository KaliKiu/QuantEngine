#include <iostream>
#include <curl/curl.h>
#include <thread>
#include <variant>

#include "HttpClient/httpclient.hpp"
#include "Config/config.hpp"
#include "Queue/queue.hpp"
#include "Data/marketdata.hpp"
#include "Data/data.hpp"
#include "Data/parser.hpp"
#include "Analyze/analyzer.hpp"
#include "Analyze/momentumanalyzer.hpp"

static constexpr const char* CONFIG_FILE_DIR =  "../data/config.json";



//THREAD SYSTEM IS OUT OF DATE, ITS NOT SAFE THIS WAY. Will be updated
int main(){
    std::cout <<"meow";
    Config::loadconfig(CONFIG_FILE_DIR);
    Queue<std::string> queue;
    HttpClient http;
    Data data;
    MarketData::StructType datatype = MarketData::Latest{};

    std::cout<<"mo";
    std::thread t([&http, &queue](){
        for(int i = 0; i<100; i++){
            http.pushData(queue);
        }
    });

    if(t.joinable()){
        std::cout<<"thread joined";
        t.detach();
    }
    std::thread p([&data,&queue,&datatype](){
        while(true){
            
            data.addData(Parser::parseLatest(queue));
        }
        
    });

    if(p.joinable()){
        std::cout <<"thread joined";
        p.join();
    }

    std::unique_ptr<Analyzer> ok = std::make_unique<MomentumAnalyzer>();

}

