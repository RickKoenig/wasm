cmake_minimum_required(VERSION 3.20)
project(multi LANGUAGES CXX C)

add_library(multi STATIC timesTwo.cpp timesThree.cpp timesFour.cpp)

target_include_directories(multi
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
