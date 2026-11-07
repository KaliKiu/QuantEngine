#pragma once

#include <curl/curl.h>
#include <iostream>
#include <tl/expected.hpp>

class InfluxDBClient{
    private:
    std::string database;
    const char* token;
    CURL* curl;
    struct curl_slist* headers;

    public:
    InfluxDBClient(std::string);
    ~InfluxDBClient();

    
    void write(std::string);
    std::string test();
};