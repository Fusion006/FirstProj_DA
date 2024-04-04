#ifndef DAP1_FLOWNETWORK_H
#define DAP1_FLOWNETWORK_H

#include "project/Graph/Graph.h"
#include "maxflow.h"
#include "utility"

/**
 *
 * @param original
 */
void CreateSuperSourceSink(Graph& original);
/**
 *
 * @param graph
 */
void DestroySuperSourceSink(Graph& graph);
/**
 *
 * @param graph
 */
void FlowNetworkEvaluation(Graph& graph);
/**
 *
 * @param graph
 * @return
 */
vector<pair<City*, double>> getCitiesInDeficit(Graph& graph);
/**
 *
 * @param citiesInDeficit
 */
void PrintResults(vector<pair<City*, double>>& citiesInDeficit);

#endif //DAP1_FLOWNETWORK_H
