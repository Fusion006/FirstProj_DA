#ifndef DAP1_OPTIMALFLOW_H
#define DAP1_OPTIMALFLOW_H

#include "project/Graph/Graph.h"
#include "maxflow.h"
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

void CreateSuperSourceSink1(Graph& original);
void DestroySuperSourceSink1(Graph& graph);
void Opt_Flow(Graph& graph);
void Opt_printResult(vector<pair<City*, double>>& vec);

#endif //DAP1_OPTIMALFLOW_H
