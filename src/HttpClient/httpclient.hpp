#pragma once

#include "../Queue/queue.hpp"
#include "../Data/marketdata.hpp"

class HttpClient{
    private:
    std::string buffer;
    std::uint32_t count;

    public:
    HttpClient();
    HttpClient();
    ~HttpClient();

    std::string getData();
    void pushData(Queue<std::string>& queue);
};