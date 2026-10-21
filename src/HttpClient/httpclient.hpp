#pragma once

#include <tl/expected.hpp>
#include "../Error/error.hpp"

class HttpClient{
    private:
    std::string buffer;
    std::uint32_t count;
    std::string apiUrl;

    public:
    HttpClient(std::string apiUrl);
    HttpClient(const HttpClient& other);
    ~HttpClient();

    tl::expected<std::string,Error::HttpError> getSingleData();
    void pushData();
};