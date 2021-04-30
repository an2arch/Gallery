cmake_minimum_required(VERSION 3.17)
project(Models)

set(CMAKE_CXX_STANDARD 20)

FILE(GLOB_RECURSE SOURCES *.cpp)

include_directories(
        Account
        Photo
)

add_library(Models ${SOURCES})
