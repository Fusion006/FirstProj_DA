#ifndef DAP1_GRAPH_H
#define DAP1_GRAPH_H


#include <map>
#include "Vertexes/Vertex.h"
#include "Pipe.h"
#include "Vertexes/City.h"
#include "Vertexes/Reservoir.h"
#include "Vertexes/Station.h"
#include "fstream"
#include "sstream"

class Graph {
private:
    std::map<int,City> cities;
    std::map<int,Reservoir> reservoirs;
    std::map<int,Station> stations;
    std::map<std::string,int> nameToId;

public:
    Graph();

};


#endif
