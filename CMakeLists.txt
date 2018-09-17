cmake_minimum_required(VERSION 3.12)
project(SLList)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SLList
        Cursor.cpp
        Cursor.h
        main.cpp)
