#ifndef DAP1_RELIABILITY_H
#define DAP1_RELIABILITY_H

#include "project/Graph/Graph.h"
#include <iostream>
#include <set>
#include <string>
#include <map>

void remReservoirController(Graph& g);
std::string getReservoirInput(Graph &g);
map<string,int> removeReservoir(Graph &g, set<string>);

#endif