#include "influxclient.hpp"


InfluxDBClient::InfluxDBClient(std::string database_) : database{std::move(database_)}{
    token = std::getenv("INFLUXDB3_AUTH_TOKEN");
    if(!token){
        throw std::runtime_error("Failed to construct InfluxDBClient");
    }
    curl = curl_easy_init();
    std::string buff = "Authorization: Bearer ";
    buff.append(token);
    headers = nullptr;
    headers = curl_slist_append(headers,buff.c_str());
    headers = curl_slist_append(headers, "Content-Type: text/plain; charset=utf-8");

}
InfluxDBClient::~InfluxDBClient(){

}

void InfluxDBClient::write(std::string data){
    
} 

std::string InfluxDBClient::test(){
    
}