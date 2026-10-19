#pragma once

#include "../Queue/queue.hpp"
#include "../Data/marketdata.hpp"

class HttpClient{
    private:
    std::string buffer;
    std::uint32_t count;

    public:
    HttpClient();
    HttpClient(HttpClient httpclient);
    ~HttpClient();

    void getData(Queue<std::string>& queue);
    void pushData(Queue<std::string>& queue);
};