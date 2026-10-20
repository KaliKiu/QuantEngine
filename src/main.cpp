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
#include "Engine/engine.hpp"

static constexpr const char* CONFIG_FILE_DIR =  "../data/config.json";



//THREAD SYSTEM IS OUT OF DATE, ITS NOT SAFE THIS WAY. Will be updated
int main(){
    

}

