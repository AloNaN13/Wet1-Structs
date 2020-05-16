cmake_minimum_required(VERSION 3.15)
project(Wet1_Structs)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Wet1_Structs
        Artist.cpp
        Artist.h
        #AVL_tests.h
        AVL_tests.h
        AvlTree.h
        library1.cpp
        library1.h
        List.cpp
        List.h
        #main.cpp
        main1.cpp
        #main_alon.cpp
        MusicManager.cpp
        MusicManager.h
        MusicManger_sari_tests.h
        )
