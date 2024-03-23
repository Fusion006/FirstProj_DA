#ifndef DAP1_MAXFLOW_H
#define DAP1_MAXFLOW_H

#include "project/Graph/Graph.h"
#include <iostream>
#include <string>

void edmondsKarp(Graph &g, string &source, string &target);
bool shortestPath(Graph &g, string &source, string &target, vector<string> *v); //this function uses BFS algorithm

#endif //DAP1_MAXFLOW_H
