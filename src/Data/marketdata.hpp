#pragma once

#include <variant>
#include "iostream"
#include "nlohmann/json.hpp"


namespace MarketData{

    struct Ohlc{
        std::string market;
        double open{};
        double high{};
        double low{};
        double close{};

        void dump() const {
            nlohmann::json j = {
                {"market", market},
                {"open", open},
                {"high", high},
                {"low", low},
                {"close", close}
            };
            std::cout << j.dump(4) << "\n";
        }
    };

    struct Latest {
        std::string market;
        double bid{};
        double ask{};
        double last{};
        double high{};
        double low{};
        double dayDiffPercent{};
        double spread{};
        double mid{};
        int quoteAgeSeconds{};
        std::string marketState;
        std::string direction;
        std::string timestamp;
        

        void dump() const {
            nlohmann::json j = {
                {"market", market},
                {"high", high},
                {"low", low},
                {"bid", bid},
                {"ask", ask},
                {"last", last},
                {"state", marketState},
                {"spread", spread},
                {"time", timestamp}
            };
            std::cout << j.dump(4) << "\n";
        }
    };

    using StructType = std::variant<MarketData::Ohlc, MarketData::Latest>;
}