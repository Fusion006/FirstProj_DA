#ifndef DAP1_OPTIMALFLOW_H
#define DAP1_OPTIMALFLOW_H

#include "project/Graph/Graph.h"
#include "maxflow.h"
#include "FlowNetwork.h"
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>


/** Calculates the the maximum flow that can reach a specific city or all of the cities, according to the user order.
 *  Time complexity: O((V * E^2) + V + E).
 * @param graph Graph that contains the network information given by the user.
 */
void Opt_Flow(Graph& graph);
/** Shows the user the maximum flow that can reach each city.
 *  Prints the cities by the city name, code and flow value, by descending order of water flow, or, in some cases, by ascending order of the code.
 *  Time complexity: O(Vlog(V) + V).
 * @param vec Vector of pairs with a pointer to a City, and the value of max flow.
 */
void Opt_printResult(vector<pair<City*, double>>& vec);
/** Gets the value of the maximum flow that can reach a specific city.
 * Time complexity: O(E).
 * @param city City pointer to get the max flow from.
 * @return the value of the maximum flow.
 */
double getTotalFlow(City* city);

#endif //DAP1_OPTIMALFLOW_H
