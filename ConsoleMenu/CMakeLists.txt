cmake_minimum_required(VERSION 3.17)
project(CMenu)

set(CMAKE_CXX_STANDARD 20)

set(SRC
        CMenu.cpp
        ItemMenu.cpp
        )

add_library(CMenu ${SRC})
