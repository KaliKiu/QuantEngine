#pragma once


#include "iostream"
#include "marketdata.hpp"
#include "../Queue/queue.hpp"



class Parser{
    public:
    static MarketData::Latest parseLatest(const std::string& raw);
    static MarketData::Ohlc parseOhlc(Queue<std::string>& queue);
};