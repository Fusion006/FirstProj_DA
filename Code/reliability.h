#ifndef DAP1_RELIABILITY_H
#define DAP1_RELIABILITY_H

#include "project/Graph/Graph.h"
#include <iostream>
#include <set>
#include <string>
#include <map>
double getCityDeficit(const string& cityName, const vector<pair<City*, double>>& cityToDeficit);
map<string,double> getReservoirMap(Graph &g);

void remReservoir(Graph& g);
Reservoir* getReservoirInput(Graph &g);
bool checkRelevantVertex(Graph &g, Vertex* v);
void restoreReservoir(Graph &g, const map<string,double>& capacities);
void printDiferences(const map<string,double>& start,map<string,double> end);

void remStation(Graph& g);
void restoreStations(Graph& g, const map<string,vector<Pipe*>>& stationsPipes);
Station* getStationInput(Graph &g);


void findIrrelevantStations(Graph& g);
bool isStationIrrelevant(Graph& g, Station* station);
bool deficitIncrised(const vector<pair<City*, double>>& start, const vector<pair<City*, double>>& end);
void printIrrelevantStations(const set<string>& stations);

void remPipe(Graph& g);
Pipe* getPipeInput(Graph& g);
void restorePipes(Graph &g, const map<pair<string,string>,double>& capacities);



#endif