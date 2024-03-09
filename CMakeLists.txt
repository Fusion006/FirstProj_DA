cmake_minimum_required(VERSION 3.26)
project(DAP1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DAP1 main.cpp
        project/Graph/Graph.h
        project/Graph/Graph.cpp
)
