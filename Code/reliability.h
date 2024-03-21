#ifndef DAP1_RELIABILITY_H
#define DAP1_RELIABILITY_H

#include "project/Graph/Graph.h"
#include <iostream>
#include <set>
#include <string>
#include <map>

void remReservoirController(Graph& g);
Reservoir* getReservoirInput(Graph &g);
bool checkRelevantVertex(Graph &g, Vertex* v);
void restoreReservoir(Graph &g, const map<string,int>& capacities);
void printDiferences(Graph& g, const map<string,int>& start,map<string,int> end);
#endif