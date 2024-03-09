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
    std::map<std::string ,City*> cities;
    std::map<std::string,Reservoir*> reservoirs;
    std::map<std::string,Station*> stations;
    std::map<std::string,std::string> nameToCode;

public:
    Graph();

};


#endif
