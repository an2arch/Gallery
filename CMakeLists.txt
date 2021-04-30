cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 20)

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
        # Screen/Auth
        # Screen/Main
        # Screen/AccountList
        # Screen/AlbumList
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

add_executable(project main.cpp)

target_link_libraries(project App) # Screen Storage Global Utility CMenu Models)
