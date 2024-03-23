#ifndef DAP1_FLOWNETWORK_H
#define DAP1_FLOWNETWORK_H

#include "project/Graph/Graph.h"


Graph CreateSuperSourceSink(const Graph& original);
void FlowNetworkEvaluation(Graph& graph);


#endif //DAP1_FLOWNETWORK_H
