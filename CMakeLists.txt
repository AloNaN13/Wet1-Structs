cmake_minimum_required(VERSION 3.15)
project(Wet1-Structs)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        main.cpp
        AvlTree.h
        MusicManager.h
        MusicManager.cpp
        Artist.h
        Artist.cpp
        List.h
        List.cpp
        libary1.cpp)