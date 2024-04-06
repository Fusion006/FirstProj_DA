#ifndef DAP1_MAXFLOW_H
#define DAP1_MAXFLOW_H

#include "project/Graph/Graph.h"
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

/** Computes the maxflow that can go from a source node and reach a sink node.
 *  Applies the Edmonds-Karp algorithm to compute the flow of each edge alon the way.
 *  Time Complexity: O(V * E^2).
 * @param g graph to be traversed.
 * @param source source node.
 * @param target sink node.
 */
void edmondsKarp(Graph &g, string &source, string &target);
/** Uses the BFS algorithm to find the shortest path, if any, from source node and target node.
 *  Goes trough graph g using a bfs strategy.
 *  It uses some vertex and Pipe parameters, being the most relevant the path attribute of Vertex, witch is used to get the actual shortest path.
 *  If the path of the target node is not null, it means there is a path from source to target.
 *  Time complexity: O(V + E + V).
 * @param g graph to be traversed.
 * @param source source node code.
 * @param target target node code.
 * @param v pointer to the vertex that will contain the path from source to target, in strings of vertex code.
 * @return true if the function finds a path from source to target.
 */
bool shortestPath(Graph &g, string &source, string &target, vector<string> *v); //this function uses BFS algorithm


#endif //DAP1_MAXFLOW_H
