#ifndef DAP1_FLOWNETWORK_H
#define DAP1_FLOWNETWORK_H


/** @defgroup FlowNetwork FlowNetwork
 * @{
 *
 * Functions used to check the capacity to distribute water to the cities
 */
#include "project/Graph/Graph.h"
#include "maxflow.h"
#include <utility>
#include <algorithm>

/** Creates a super source connected to all sources of original and a super sink connected to all the sinks od original.
 *  Adds two Vertexes, one with code "SuperC" (the super sink) and other with code "SuperR" (the super source).
 *  The super source is connected to all sources (reservoirs), creating a pipe that originates at the super source and ends at the respective source (reservoir), and with a capacity equal to the capacity of the respective source (reservoir) of the destination.
 *  The super sink is connected to all the sinks (cities), creating a pipe that originates in the respective sink (city) and ends in the super sink, and with a capacity equal to the demand of the respective sink (city) of the destination.
 * Time complexity: O(V).
 * @param original Graph that contains the original network information given by the user.
 */
void CreateSuperSourceSink(Graph& original);
/** Safely deletes the super source and super sink from the Graph.
 *  Removes the super vertexes without touching the original Pipes and Vertexes from the Graph.
 *  Time complexity: O(V).
 * @param graph Graph that contains the network information given by the user.
 */
void DestroySuperSourceSink(Graph& graph);
/** Calculates the value of the maximum flow that can reach all the cities, and shows the cities where the demand is greater than the flow, i.e. where it has not been possible to deliver the necessary amount of water.
 *  Uses the Edmonds-Karp algorithm with Super source ("SuperR") as source and Super sink ("SuperC") as sink to find out the maximum flow.
 *  Time complexity: O((V * E^2) + V).
 * @param graph Graph that contains the network information given by the user.
 */
void FlowNetworkEvaluation(Graph& graph);
/** Determines which cities' flow does not correspond to demand.
 *  Finds out the deficit (demand - flow) of water for each city not satisfied, and returns the City alongside the deficit.
 *  Time complexity: O(V + E).
 * @param graph graph that contains the cities to be analysed.
 * @return Vector of pairs with a pointer to a City, and the value of the deficit.
 */
vector<pair<City*, double>> getCitiesInDeficit(Graph& graph);
/** Shows the user all the cities that have deficit of flow (demand is not satisfied), if any.
 *  Prints the cities by the city name, code and deficit value, by descending order of water deficit, or, in some cases, by ascending order of the code.
 *  Time complexity: O(Vlog(V) + V).
 * @param citiesInDeficit Vector of pairs with a pointer to a City, and the value of the deficit.
 */
void PrintResults(vector<pair<City*, double>>& citiesInDeficit);
/** Auxiliary function to allow the sort of two City vertexes, by descending order of their water deficit, or, in some cases, by ascending their code.
 *  A City comes first then the other City if it has more water deficit, or in case it is the same, if its code comes first then the code of the other City.
 *  Time complexity: O(1).
 * @param p1 The first pair to be compared, that contains a pointer to a City vertex as the first value, and the value of the water capacity that does not reach the city (deficit).
 * @param p2 The second pair to be compared, that contains a pointer to a City vertex as the first value, and the value of the water capacity that does not reach the city (deficit).
 * @return true if pair p1 comes first then p2.
 */
bool sortCitiesByDeficit(const pair<City*, double>& p1, const pair<City*, double>& p2);

#endif //DAP1_FLOWNETWORK_H
