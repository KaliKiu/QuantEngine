#pragma once

#include <tl/expected.hpp>
#include <iostream>
#include "../Error/error.hpp"
#include "../Data/marketdata.hpp"

namespace Influxserializer{
    tl::expected<std::string,Error::InfluxDBError> serialize_latest(MarketData::Latest data);
}