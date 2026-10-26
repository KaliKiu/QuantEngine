#pragma once


#include "iostream"
#include "marketdata.hpp"



class Parser{
    public:
    static MarketData::Latest parseLatest(std::string buffer);
    static MarketData::Ohlc parseOhlc(std::string buffer);
};