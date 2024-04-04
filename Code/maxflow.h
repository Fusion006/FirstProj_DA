#ifndef DAP1_MAXFLOW_H
#define DAP1_MAXFLOW_H

#include "project/Graph/Graph.h"
#include <iostream>
#include <string>

/**
 *
 * @param g
 * @param source
 * @param target
 */
void edmondsKarp(Graph &g, string &source, string &target);
/**
 *
 * @param g
 * @param source
 * @param target
 * @param v
 * @return
 */
bool shortestPath(Graph &g, string &source, string &target, vector<string> *v); //this function uses BFS algorithm

#endif //DAP1_MAXFLOW_H
