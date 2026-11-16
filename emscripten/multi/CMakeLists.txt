cmake_minimum_required(VERSION 3.20)
project(multi LANGUAGES CXX C)

#add_library(multi STATIC timesTwo.cpp timesThree.cpp timesFour.cpp)

file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp" "*.c")
add_library(multi STATIC ${SOURCES})

target_include_directories(multi
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
