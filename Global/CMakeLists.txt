cmake_minimum_required(VERSION 3.17)
project(Global)

set(CMAKE_CXX_STANDARD 20)

FILE(GLOB SRC *.cpp)

add_library(Global ${SRC})
