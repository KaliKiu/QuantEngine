#include <nlohmann/json.hpp>
#include "marketdata.hpp"
#include "data.hpp"
#include "parser.hpp"

using json = nlohmann::json;

MarketData::Latest Parser::parseLatest(std::string buffer){
    
    
    const json rawentry_top = json::parse(buffer);
    std::string market = "BTCUSD";
    const auto& rawentry = rawentry_top[market];

    MarketData::Latest data{
        .market = rawentry_top.at(market).at("symbol").get<std::string>(),
        .bid = rawentry.at("bid").get<double>(),
        .ask = rawentry.at("ask").get<double>(),
        .last = rawentry.at("last").get<double>(),
        .high = rawentry.at("high").get<double>(),
        .low = rawentry.at("low").get<double>(),
        .dayDiffPercent = rawentry.at("dayDiffPercent").get<double>(),
        .spread = rawentry.at("spread").get<double>(),
        .mid = rawentry.at("mid").get<double>(),
        .quoteAgeSeconds = rawentry.at("quoteAgeSeconds").get<int>(),
        .marketState = rawentry.at("marketState").get<std::string>(),
        .direction = rawentry.at("direction").get<std::string>(),
        .timestamp = rawentry.at("timestamp").get<std::string>()
    };

    return data;
}
