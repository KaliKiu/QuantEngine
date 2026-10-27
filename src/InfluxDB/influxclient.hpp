#pragma once

#include <curl/curl.h>
#include <iostream>
#include <tl/expected.hpp>

class InfluxDBClient{
    private:
    const char* token;

    public:
    InfluxDBClient();

    
    void write(std::string&& data);
};