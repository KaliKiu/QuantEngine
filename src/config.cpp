#include <iostream>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <fstream>
#include "Config/config.hpp"

using json = nlohmann::json;

namespace Config{

    Config config;

    void loadconfig(const char* CONFIG_FILE_DIR){
        std::ifstream config_file(CONFIG_FILE_DIR);
        if(!config_file.is_open()){
            std::cerr <<"error opening file";
            return;
        }
        json configjson = json::parse(config_file);
        
        config.XAUUSD.apiXAUUSD = configjson["XAUUSD"]["apiXAUUSD"];
        config.XAUUSD.apiXAUUSD_OHLC = configjson["XAUUSD"]["apiXAUUSD_OHLC"];
        config.BTCUSD.apiBTCUSD = configjson["BTCUSD"]["apiBTCUSD"];
        config.BTCUSD.apiBTCUSD_OHLC = configjson["BTCUSD"]["apiBTCUSD_OHLC"];
    }

}  