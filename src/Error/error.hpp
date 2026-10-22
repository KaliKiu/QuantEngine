#pragma once

#include <string_view>
#include <variant>
#include <string_view>

class Error{

    public: 

    enum class HttpError {
        EmptyBuffer,
        NetworkFailure,
        Timeout,
    };
    
    template<typename T>
    static void log_error(T error_code){
        std::cout <<"[Error] "<<to_string(error_code) <<std::endl;
    }
    
};

template<typename T>
    std::string_view to_string(T error);

    template<>
    inline std::string_view to_string(Error::HttpError error){
        switch(error){
            case Error::HttpError::EmptyBuffer: return "EmptyBuffer";
            case Error::HttpError::NetworkFailure: return "NetworkFailure";
            case Error::HttpError::Timeout: return "Timeout";
        }
        return "Unknown Error";
    }