#include "influxclient.hpp"


InfluxDBClient::InfluxDBClient(){
    token = std::getenv("INFLUXDB3_AUTH_TOKEN");
    if(!token){
        throw std::runtime_error("Failed to construct InfluxDBClient");
    }

}

void InfluxDBClient::write(std::string data){
    
} 
