#include "FlowNetwork.h"

using namespace std;

void CreateSuperSourceSink(Graph& original) {
    original.addVertex(0, "SuperR");
    original.addVertex(0, "SuperC");

    for (Reservoir * reservoir : original.getReservoirs()) {
        if(original.addPipe("SuperR", reservoir->getCode(), reservoir->getCapacity())) continue;
    }

    for (City * city : original.getCities()) {
        if(original.addPipe(city->get_code(), "SuperC", city->get_demand())) continue;
    }
}

void DestroySuperSourceSink(Graph& graph) {
    graph.removeVertex("SuperR");
    graph.removeVertex("SuperC");
}

void FlowNetworkEvaluation(Graph& graph) {
    CreateSuperSourceSink(graph);

    string source = "SuperR", target = "SuperC";
    edmondsKarp(graph, source, target);

    DestroySuperSourceSink(graph);
}

bool sortCitiesByDeficit(const pair<City*, double>& p1, const pair<City*, double>& p2) {
    return p1.second > p2.second || (p1.second == p2.second && p1.first->get_code() > p2.first->get_code());
}

vector<pair<City*, double>> getCitiesInDeficit(Graph& graph) {
    vector<pair<City*, double>> res;
    for (City* city : graph.getCities()) {
        double totalDelivered = 0;
        for (Pipe* pipe : city->getIncoming()) {
            totalDelivered += pipe->getFlow();
        }
        if (totalDelivered < city->get_demand()) {
            pair<City*, double> pair1 = make_pair(city, city->get_demand() - totalDelivered);
            res.push_back(pair1);
        }
    }
    return res;
}

void PrintResults(vector<pair<City*, double>>& citiesInDeficit) {
    if (citiesInDeficit.empty()) {
        cout << "All the cities are satisfied!!" << endl;
        return;
    }

    cout << "The following cities (city name, city code, deficit value) are not satisfied:" << endl << endl;

    std::sort(citiesInDeficit.begin(), citiesInDeficit.end(), sortCitiesByDeficit);
    for (auto pair : citiesInDeficit) {
        cout << "Name: " << pair.first->get_name() << " Code: " << pair.first->get_code() << " Water deficit: " << pair.second << endl;
    }
}