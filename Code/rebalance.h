#ifndef DAP1_REBALANCE_H
#define DAP1_REBALANCE_H

#include "project/Graph/Graph.h"
#include "FlowNetwork.h"
#include <algorithm>

/**
 *
 * @param graph
 */
void FlowBalance(Graph& graph);
/**
 *
 * @param code
 * @param graph
 * @return
 */
double getVertexMedian(const string& code, Graph& graph);
/**
 *
 * @param graph
 * @return
 */
int getNumberOfUnusedPipes(Graph& graph);
/**
 *
 * @param graph
 * @return
 */
vector<pair<string, pair<string, double>>> getOriginalCapacities(Graph& graph);


#endif //DAP1_REBALANCE_H
