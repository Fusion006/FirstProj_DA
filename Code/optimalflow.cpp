#include "optimalflow.h"
#include <utility>
using namespace std;

void CreateSuperSourceSink1(Graph& original) {
    original.addVertex(0, "SuperR");
    original.addVertex(0, "SuperC");

    for (Reservoir * reservoir : original.getReservoirs()) {
        if(original.addPipe("SuperR", reservoir->getCode(), reservoir->getCapacity())) continue;
    }

    for (City * city : original.getCities()) {
        if(original.addPipe(city->get_code(), "SuperC", city->get_demand())) continue;
    }
}

void DestroySuperSourceSink1(Graph& graph) {
    graph.removeVertex("SuperR");
    graph.removeVertex("SuperC");
}

void Opt_Flow(Graph& graph) {
    cout << "Please insert:" << endl <<
         "'1' to see the maximum amount of water that can reach a specific city;" << endl <<
         "'2' to see the maximum amount of water that can reach each city;" << endl;
    char order;
    cin >> order;
    if (order == '1') {
        vector<pair<City *, double>> v;
        cout << "Insert the code of the city that you want to reach:";
        string c;
        cin >> c;
        CreateSuperSourceSink1(graph);

        string source = "SuperR", sink = "SuperC";
        edmondsKarp(graph, source, sink);
        for (auto city: graph.getCities()) {
            if(city->get_code() == c){
                for(auto e : city->getAdj()) {
                    if (e->getDest()->get_code() == "SuperC") {
                        double flow = e->getFlow();
                        pair<City *, double> pair1 = make_pair(city, flow);
                        v.push_back(pair1);
                    }
                }
            }
        }
        DestroySuperSourceSink1(graph);
        cout << "The maximum flow for the city you selected is:" << endl;
        Opt_printResult(v);

    } else if (order == '2') {
        vector<pair<City *, double>> v;
        double maxflow = 0.0;
        CreateSuperSourceSink1(graph);
        string source = "SuperR";
        string sink = "SuperC";
        edmondsKarp(graph, source, sink);
        for (auto city: graph.getCities()) {
            for(auto e : city->getAdj()) {
                if (e->getDest()->get_code() == "SuperC") {
                    maxflow += e->getFlow();
                    double flow = e->getFlow();
                    pair<City *, double> pair1 = make_pair(city, flow);
                    v.push_back(pair1);
                }
            }
        }
        DestroySuperSourceSink1(graph);
        Opt_printResult(v);
        cout << "The maximum amount of water that can reach the cities: " << maxflow << endl;

    } else {
        cout << "Insert a valid number!" << endl;
        return;
    }
}
void Opt_printResult(vector<pair<City*, double>>& vec){
    for(auto& i : vec){
        cout << "Name: " <<  i.first->get_name() << " Max Flow: " << i.second << endl;
    }
}