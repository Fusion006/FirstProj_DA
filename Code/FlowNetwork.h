#ifndef DAP1_FLOWNETWORK_H
#define DAP1_FLOWNETWORK_H

#include "project/Graph/Graph.h"
#include "maxflow.h"
#include "utility"


void CreateSuperSourceSink(Graph& original);
void DestroySuperSourceSink(Graph& graph);
void FlowNetworkEvaluation(Graph& graph);
vector<pair<City*, double>> getCitiesInDeficit(Graph& graph);
void PrintResults(vector<pair<City*, double>>& citiesInDeficit);

#endif //DAP1_FLOWNETWORK_H
