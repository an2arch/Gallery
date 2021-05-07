cmake_minimum_required(VERSION 3.17)
project(Gallery)

set(CMAKE_CXX_STANDARD 20)

set(TARGET Gallery)

include_directories(
        Storage
        Storage/Action
        Storage/ActionTypes
        Storage/State
        Utility
        Models
        Models/Account
        Models/Photo
        Models/Album
        ConsoleMenu
        Screen
        App
        Global
)

add_subdirectory(Global)
add_subdirectory(Storage)
add_subdirectory(Models)
add_subdirectory(Utility)
add_subdirectory(Screen)
add_subdirectory(ConsoleMenu)
add_subdirectory(App)

add_executable(${TARGET} main.cpp)

target_link_libraries(${TARGET} App) # Screen Storage Global Utility CMenu Models)
target_compile_options(${TARGET} PUBLIC -Wall -pedantic)
