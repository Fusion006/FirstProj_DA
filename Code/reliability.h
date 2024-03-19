#ifndef DAP1_RELIABILITY_H
#define DAP1_RELIABILITY_H

#include "project/Graph/Graph.h"
#include <iostream>
#include <set>
#include <string>
#include <map>

void remReservoirController(Graph& g);
std::string getReservoirInput(Graph &g);
map<string,int> removeReservoirs(Graph &g, set<string>);
void restoreReservoir(Graph &g, map<int,string>);
#endif