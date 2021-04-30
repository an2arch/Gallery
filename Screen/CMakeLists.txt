cmake_minimum_required(VERSION 3.17)
project(Screen)

set(CMAKE_CXX_STANDARD 20)

include_directories(../Models)
include_directories(../Global)
include_directories(../CMenu)
include_directories(../Storage)
include_directories(../Utility)

FILE(GLOB_RECURSE SRC *.cpp)

add_library(Screen ${SRC} AlbumList/AlbumList.cpp AlbumList/AlbumList.h)

target_link_libraries(Screen Utility CMenu)
