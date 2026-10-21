#pragma once

#include <string_view>
#include <variant>

namespace Error{

    enum class HttpError {
        EmptyBuffer,
        NetworkFailure,
        Timeout,
    };

    constexpr std::string_view toString(HttpError err) {
        switch (err) {
            case HttpError::EmptyBuffer:    return "Empty Buffer";
            case HttpError::Timeout:        return "Timeout";
            case HttpError::NetworkFailure: return "Network Failure";
        }
        return "Unknown Error";
    }

}