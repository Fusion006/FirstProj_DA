#ifndef DAP1_RELIABILITY_H
#define DAP1_RELIABILITY_H

/** @defgroup reliability reliability
 * @{
 *
 * Function used to evaluate systems resilience to vertex/edge failure
 */
#include "project/Graph/Graph.h"
#include <iostream>
#include <set>
#include <string>
#include <map>

/**
 * @brief Finds the deficit associated with a city
 *
 *
 * @param CityName The name of the city who's deficit we want to find
 * @param cityToDeficit A map of city names to their associated map
 * @return The CityName previous deficit or 0 if none was found
 * Complexity O(n)
 */
double getCityDeficit(const string& cityName, const vector<pair<City*, double>>& cityToDeficit);

/**
 * @brief Maps every reservoir code to its capacity, used to restore the reservoirs original capacity
 * @param g Graph that represents the pumping system
 * @return Map of every reservoir code to its capacity
 * Complexity O(n)
 */
map<string,double> getReservoirMap(Graph &g);

/**
 * @brief Removes the desired reservoirs one by one and shows the deficits, if any that it creates
 * @param g Graph that represents the pumping system
 * Complexity O(V * E^2) do to max flow algorithm
 */
void remReservoir(Graph& g);

/**
 * @brief Gets a Reservoir code to be removed from the system
 * @param g Graph that represents the pumping system
 * @return A pointer to the desired Reservoir
 * Complexity O(n) being n the number of Reservoirs
 */
Reservoir* getReservoirInput(Graph &g);

/**
 * @brief Checks using BFS if a Vertex has any water going out of itself i.e. if its removal affects the reservoirs delivery
 * @param g Graph that represents the pumping system
 * @param v Vertex to be evaluated
 * @return true if the Vertex is relevant to the reservoirs delivery and false otherwise
 * Complexity O(V + E) do to BFS
 */
bool checkRelevantVertex(Graph &g, Vertex* v);

/**
 * @brief Restores the system reservoirs to their original capacities
 * @param g Graph that represents the pumping system
 * @param capacities A map of the systems reservoir codes to their capacities
 * Complexity O(n^2) being n the number of Reservoirs
 */
void restoreReservoir(Graph &g, const map<string,double>& capacities);

/**
 * @brief Prints the differences of each city delivery after some vertex/edge failure
 * @param start map of the pre-removal city in deficit to their water deficit
 * @param end map of the post-removal city in deficit to their water deficit
 * Complexity O(n^2) being n the number of Reservoirs
 */
void printDifferences( const vector<pair<City*, double>>& start, const vector<pair<City*, double>>& end);

/**
 * @brief Removes the desired Pumping Stations one by one and shows the deficits, if any, that it creates
 * @param g Graph that represents the pumping system
 * Complexity O(V * E^2) do to max flow algorithm
 */
void remStation(Graph& g);

/**
 * @brief Gets a Pumping Station to be removed from the system
 * @param g Graph that represents the pumping system
 * @return A pointer to the desired Pumping Station
 * Complexity O(n) being n the number of Pumping Stations
 */
Station* getStationInput(Graph &g);

/**
 * @brief Finds the Pumping Stations that can be removed without affecting the city delivery
 * @param g Graph that represents the pumping system
 * Complexity O(V * E^2) * S) do to max flow algorithm, being S the number of Pumping Stations
 */
void findIrrelevantStations(Graph& g);

/**
 * @brief Checks if a station can be removed without affecting performance
 * @param g Graph that represents the pumping system
 * @param station the Pumping Station to be removed
 * @return true if station can be removed without affecting performance and false otherwise
 * Complexity O(V * E^2) do to max flow algorithm
 */
bool isStationIrrelevant(Graph& g, Station* station);

/**
 * @brief Checks if the city deficit increased after a vertex/edge removal
 * @param start vector of pairs of the pre-removal city and their water deficit
 * @param end vector of pairs of the post-removal city and their water deficit
 * @return true if deficit increased and false otherwise
 * Complexity O(S * N) being S and N the size of start and end respectively
 */
bool deficitIncreased(const vector<pair<City*, double>>& start, const vector<pair<City*, double>>& end);

/**
 * @brief Prints the Stations that can be removed without affecting performance
 * @param stations set of Pumping Station codes that can be removed without affecting performance
 * @Complexity O(n)
 */
void printIrrelevantStations(const set<string>& stations);

/**
 * @brief Removes the desired Pipes one by one and shows the deficits, if any, that it creates
 * @param g Graph that represents the pumping system
 * Complexity O(V * E^2) do to max flow algorithm
 */
void remPipe(Graph& g);

/**
 * @brief Gets a Pipe to be removed from the system
 * @param g Graph that represents the pumping system
 * @return A pointer to the desired Pipe
 * Complexity O(n) being n the number of Pumping Stations
 */
Pipe* getPipeInput(Graph& g);

/**
 * @brief Restores the system Pipes to their original capacities
 * @param g Graph that represents the pumping system
 * @param capacities A map of the systems source and destinations vertex codes to their capacities
 * Complexity O(V * lon(V))
 */
void restorePipes(Graph &g, const map<pair<string,string>,double>& capacities);

#endif