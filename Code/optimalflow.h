#ifndef DAP1_OPTIMALFLOW_H
#define DAP1_OPTIMALFLOW_H

#include "project/Graph/Graph.h"
#include "maxflow.h"
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

/** Creates a super source connected to all sources of original and a super sink connected to all the sinks od original.
 *  Adds two Vertexes, one with code "SuperC" (the super sink) and other with code "SuperR" (the super source).
 *  The super source is connected to all sources (reservoirs), creating a pipe that originates at the super source and ends at the respective source (reservoir), and with a capacity equal to the capacity of the respective source (reservoir) of the destination.
 *  The super sink is connected to all the sinks (cities), creating a pipe that originates in the respective sink (city) and ends in the super sink, and with a capacity equal to the demand of the respective sink (city) of the destination.
 * Time complexity: O(V).
 * @param original Graph that contains the original network information given by the user.
 */
void CreateSuperSourceSink1(Graph& original);

/** Safely deletes the super source and super sink from the Graph.
 *  Removes the super vertexes without touching the original Pipes and Vertexes from the Graph.
 *  Time complexity: O(V).
 * @param graph Graph that contains the network information given by the user.
 */
void DestroySuperSourceSink1(Graph& graph);

/** Calculates the sum of all the flows of the original network or calculates the flow from a city given by the user, depending on the selected option.
 *  Time complexity: O(V^2 + E).
 * @param graph Graph that contains the network information given by the user.
 */
void Opt_Flow(Graph& graph);

/** Prints the result of the optimal flow calculation.
 *  Time complexity: O(V).
 * @param vec Vector that contains the result of the optimal flow calculation.
 */
void Opt_printResult(vector<pair<City*, double>>& vec);

#endif //DAP1_OPTIMALFLOW_H
