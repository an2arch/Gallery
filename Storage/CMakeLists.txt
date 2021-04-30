cmake_minimum_required(VERSION 3.17)
project(Storage)

set(CMAKE_CXX_STANDARD 20)

FILE(GLOB_RECURSE SRC *.cpp)

add_library(Storage ${SRC})

target_link_libraries(Storage Models)
