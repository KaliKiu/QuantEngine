
#include <tl/expected.hpp>
#include <iostream>
#include <sstream>
#include "influxserializer.hpp"
#include "../Error/error.hpp"
#include "../Data/marketdata.hpp"

tl::expected<std::string,Error::InfluxDBError> Influxserializer::serialize_latest(MarketData::Latest data){
    std::ostringstream ss;
    ss << "market_latest," <<"symbol="<<data.market
    <<" bid="<<data.bid
    <<",ask="<<data.ask
    <<",spread="<<data.spread
    <<",mid="<<data.mid
    <<",quoteAgeSeconods="<<data.quoteAgeSeconds
    <<",high="<<data.high
    <<",low="<<data.low
    <<",last="<<data.last
    <<",timestamp="<<data.timestamp;
    if(!ss){
        return tl::make_unexpected(Error::InfluxDBError::SerializingError);
    }
    return ss.str();
}