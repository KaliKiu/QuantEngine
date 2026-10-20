#include <string>
#include <curl/curl.h>
#include <iostream>
#include "../Config/config.hpp"
#include "../Queue/queue.hpp"
#include "../Data/marketdata.hpp"
#include "httpclient.hpp"


    HttpClient::HttpClient (){}
    HttpClient::~HttpClient(){

    }

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string HttpClient::getData(){

        CURL *curl;
        CURLcode res;
        std::string buffer;

        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, Config::config.XAUUSD.apiXAUUSD.c_str());
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA, &buffer);
        
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::cout <<this->count++;
        this->buffer = buffer;
        std::cout<< this->buffer;

        return this->buffer;
    }
    void HttpClient::pushData(Queue<std::string>& queue){
        this->getData(queue);
        if(this->buffer.empty()){
            std::cout<<"empty string";
            return;
        }
        queue.push(this->buffer);
        this->buffer = "";
    }
