#ifndef DAP1_REBALANCE_H
#define DAP1_REBALANCE_H

#include "project/Graph/Graph.h"
#include "FlowNetwork.h"
#include <algorithm>

/** Heuristic function that tries to balance the flow across the network.
 *  The balance is based on the number of unused pipelines, i.e. with flow 0.
 *  The less unused pipes, the more balanced is the flow.
 *  Time Complexity: O(V * (V + E) + E).
 * @param graph graph to be balanced.
 */
void FlowBalance(Graph& graph);
/** This function calculates the median value of the differences between flow and capacity (capacity - flow) of all the pipes coming out of a specific Vertex.
 *  Time Complexity: O(E + E*log(E)).
 * @param code Code of the specific vertex to be analyzed.
 * @param graph graph that contains the vertex with Code @param code.
 * @return the value of the median.
 */
double getVertexMedian(const string& code, Graph& graph);
/** Traverses the graph to find out the number of unused pipes (flow 0).
 *  Time Complexity: O(V + E).
 * @param graph graph that contains the network.
 * @return the total number of unused pipelines.
 */
int getNumberOfUnusedPipes(Graph& graph);
/** Function that stores all the original pipeline information from the graph.
 *  Saves the origin and destiny nodes, as well the capacity of the pipe.
 *  Time Complexity: O(V + E).
 * @param graph graph with the original information.
 * @return a vertex of pairs that contain the origin node code as the first member, and, as the second element, a pair that contains the code of the destiny and the capacity of the pipeline.
 */
vector<pair<string, pair<string, double>>> getOriginalCapacities(Graph& graph);


#endif //DAP1_REBALANCE_H
