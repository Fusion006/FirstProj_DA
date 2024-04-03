#ifndef DAP1_REBALANCE_H
#define DAP1_REBALANCE_H

#include "project/Graph/Graph.h"
#include "FlowNetwork.h"
#include <algorithm>


void FlowBalance(Graph& graph);
vector<vector<string>> bfsRebalance(const string & source, Graph& graph);
double getMedian(Graph& graph);
double getVertexMedian(const string& code, Graph& graph);
int getNumberOfUnusedPipes(Graph& graph);
vector<pair<string, pair<string, double>>> getOriginalCapacities(Graph& graph);


#endif //DAP1_REBALANCE_H
