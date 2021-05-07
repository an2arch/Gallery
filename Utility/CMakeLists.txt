cmake_minimum_required(VERSION 3.17)
project(Utility)

set(CMAKE_CXX_STANDARD 20)

# FILE(GLOB_RECURSE SRC *.cpp)
set(SRC Utility.cpp TablePrint/TablePrint.cpp)

add_library(Utility ${SRC})
