#include "FlowNetwork.h"

using namespace std;

void CreateSuperSourceSink(Graph& original) {
    original.addVertex(0, "SuperR");
    original.addVertex(0, "SuperC");

    for (Reservoir * reservoir : original.getReservoirs()) {
        original.addPipe("SuperR", reservoir->getCode(), reservoir->getCapacity());
    }

    for (City * city : original.getCities()) {
        original.addPipe(city->get_code(), "SuperC", city->get_demand());
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

vector<pair<City*, double>> getCitiesInDeficit(Graph& graph) {
    vector<pair<City*, double>> res;
    double totalFlow = 0;
    for (City* city : graph.getCities()) {
        double totalDelivered = 0;
        for (Pipe* pipe : city->getIncoming()) {
            totalDelivered += pipe->getFlow();
            totalFlow += pipe->getFlow();
        }
        if (totalDelivered < city->get_demand()) {
            pair<City*, double> pair1 = make_pair(city, city->get_demand() - totalDelivered);
            res.push_back(pair1);
        }
    }
    return res;
}

void PrintResults(vector<pair<City*, double>>& citiesInDeficit) {
    for (auto pair : citiesInDeficit) {
        cout << pair.first->get_name() << "   " << pair.first->get_code() << "   " << pair.second << endl;
    }
}