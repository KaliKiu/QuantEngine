cmake_minimum_required(VERSION 3.20)
project(meow LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(CURL REQUIRED)

message(STATUS "C Compiler Path: ${CMAKE_C_COMPILER}")
message(STATUS "C Compiler Version: ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "CXX Compiler Path: ${CMAKE_CXX_COMPILER}")
message(STATUS "CXX Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

add_subdirectory(external/json)

add_executable(meow
    src/main.cpp
    src/Engine/engine.hpp
    src/HttpClient/httpclient.hpp
    src/HttpClient/httpclient.cpp
)

target_include_directories(meow PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/expected/include
)

target_link_libraries(meow PRIVATE 
    CURL::libcurl
    nlohmann_json::nlohmann_json
)