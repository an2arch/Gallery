cmake_minimum_required(VERSION 3.17)
project(App)

set(CMAKE_CXX_STANDARD 20)

set(SRC App.cpp)

include_directories(../ConsoleMenu)
include_directories(../Utility)
include_directories(../Models)
include_directories(../Screen)
include_directories(../Storage)
include_directories(../Global)

add_library(App ${SRC})

target_link_libraries(App Screen Storage Global)
