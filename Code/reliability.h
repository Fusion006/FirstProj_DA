#ifndef DAP1_RELIABILITY_H
#define DAP1_RELIABILITY_H

#include "project/Graph/Graph.h"
#include <iostream>
#include <set>
#include <string>
#include <map>
double getCityDeficit(string cityName, const vector<pair<City*, double>>& cityToDeficit);
map<string,double> getReservoirMap(Graph &g);

void remReservoir(Graph& g);
Reservoir* getReservoirInput(Graph &g);
bool checkRelevantVertex(Graph &g, Vertex* v);
void restoreReservoir(Graph &g, const map<string,int>& capacities);
void printDiferences(Graph& g, const map<string,int>& start,map<string,int> end);

void remStation(Graph& g);
void restoreStations(Graph& g, const map<string,vector<Pipe*>>& stationsPipes);
Station* getStationInput(Graph &g);
#endif