#include <string>
#include <curl/curl.h>
#include <iostream>
#include "httpclient.hpp"


    HttpClient::HttpClient (){}

    HttpClient::~HttpClient(){

    }

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    void HttpClient::getData(){

        CURL *curl;
        CURLcode res;
        std::string buffer;
        std::string xausdurl = "https://biquote.io/api/latest?&symbols=XAUUSD";
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, xausdurl.c_str());
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA, &buffer);
        
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::cout <<this->count++;
        this->buffer = buffer;
        std::cout<< this->buffer;
    }
    std::string HttpClient::pushData(){
        this->getData();
        if(this->buffer.empty()){
            std::cout<<"empty string";
            return "";
        }
        std::string buff = this->buffer;
        this->buffer = "";
        return buff;
    }
