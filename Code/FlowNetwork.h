#ifndef DAP1_FLOWNETWORK_H
#define DAP1_FLOWNETWORK_H

#include "project/Graph/Graph.h"
#include "maxflow.h"
#include <utility>
#include <algorithm>

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
/**
 *
 * @param p1
 * @param p2
 * @return
 */
bool sortCitiesByDeficit(const pair<City*, double>& p1, const pair<City*, double>& p2);

#endif //DAP1_FLOWNETWORK_H
