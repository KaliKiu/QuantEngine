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


add_executable(meow
    src/main.cpp
    src/HttpClient/httpclient.cpp
    src/Data/parser.cpp
    src/InfluxDB/influxserializer.cpp
)

target_include_directories(meow PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/json/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/external/expected/include
)

target_link_libraries(meow PRIVATE 
    CURL::libcurl
)
##pull submodules before compilation : git submodule update --init --recursive