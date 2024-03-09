cmake_minimum_required(VERSION 3.26)
project(DAP1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DAP1 main.cpp
        project/Graph/Vertexes/Vertex.h
        project/Graph/Vertexes/Reservoir.h
        project/Graph/Vertexes/City.h
        project/Graph/Vertexes/Station.h
        project/Graph/Vertexes/Vertex.cpp
        project/Graph/Pipe.h
        project/Graph/Graph.h
        project/Graph/Vertexes/Reservoir.cpp
        project/Graph/Vertexes/City.cpp
        project/Graph/Vertexes/Station.cpp
        project/Graph/Graph.cpp
        project/Graph/Pipe.cpp)
