cmake_minimum_required(VERSION 3.10)
project(hyperloglog
        DESCRIPTION "a basic hyperloglog implementation"
        LANGUAGES CXX)
        
message(STATUS "You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main src/main.cpp)
