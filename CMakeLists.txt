cmake_minimum_required(VERSION 3.23)
project(meow)
set(CMAKE_CXX_STANDARD 17)
find_package( CURL REQUIRED )

message(STATUS "C Compiler Path: ${CMAKE_C_COMPILER}")
message(STATUS "C Compiler Version: ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "CXX Compiler Path: ${CMAKE_CXX_COMPILER}")
message(STATUS "CXX Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

#add_executable(meow 
#               src/main.cpp 
#               src/HttpClient/httpclient.cpp
#                src/Analyze/momentumanalyzer.cpp
#                src/Data/parser.cpp 
#                src/config.cpp)
#

add_executable(meow
                src/main.cpp
                src/Engine/engine.hpp)       
target_include_directories(meow PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(meow curl CURL::libcurl )
