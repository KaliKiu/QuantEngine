#include <string>
#include <curl/curl.h>
#include <iostream>
#include <tl/expected.hpp>

#include "../Error/error.hpp"
#include "httpclient.hpp"


    HttpClient::HttpClient(std::string apiUrl_): apiUrl{std::move(apiUrl_)} {}
    HttpClient::HttpClient(const HttpClient& other) : apiUrl{std::move(other.apiUrl)}{}
    HttpClient::~HttpClient(){}

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    void HttpClient::pushData(){
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA, &buffer);
        
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
   tl::expected<std::string, Error::HttpError> HttpClient::getSingleData(){
        this->pushData();
        if(this->buffer.empty()){
            return tl::make_unexpected(Error::HttpError::EmptyBuffer);
        }
        std::string buff = std::move(this->buffer);
        this->buffer.clear();
        return buff;
    }
