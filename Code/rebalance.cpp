#include "rebalance.h"

using namespace std;




double getVertexMedian(const string& code, Graph& graph) {
    Vertex* vertex = graph.findVertex(code);
    vector<double> diferences;
    for (Pipe* pipe : vertex->getAdj()) {
        diferences.push_back(pipe->getCapacity() - pipe->getFlow());
    }

    if (diferences.empty()) return 0;

    std::sort(diferences.begin(), diferences.end());
    if (diferences.size() % 2 != 0) {
        return diferences.at(diferences.size()/2);
    }
    else {
        return (diferences.at(diferences.size()/2) + diferences.at(diferences.size()/2 -1)) / 2;
    }
}

int getNumberOfUnusedPipes(Graph& graph) {
    int res = 0;
    for (Vertex* v : graph.getVertexSet()) {
        for (Pipe* pipe : v->getAdj()) {
            if (pipe->getFlow() == 0) res++;
        }
    }
    return res;
}

vector<pair<string, pair<string, double>>> getOriginalCapacities(Graph& graph) {
    vector<pair<string, pair<string, double>>> res;
    for (Vertex* v : graph.getVertexSet()) {
        for (Pipe* pipe : v->getAdj()) {
            res.emplace_back(pipe->getOrig()->get_code(), make_pair(pipe->getDest()->get_code(), pipe->getCapacity()));
        }
    }
    return res;
}

void FlowBalance(Graph& graph) {
    FlowNetworkEvaluation(graph);
    int numberOfUnusedPipes = getNumberOfUnusedPipes(graph);
    int oldNumber;
    double median;
    vector<pair<string, pair<string, double>>> origin = getOriginalCapacities(graph);

    while (true) {
        for (Vertex* v : graph.getVertexSet()) {
            median = getVertexMedian(v->get_code(), graph);
            if (median == 0) continue;
            for (Pipe* pipe : v->getAdj()) {
                if (pipe->getCapacity() == pipe->getFlow() && pipe->getCapacity() > median) {
                    pipe->setCapacity(pipe->getCapacity()-median);
                }
            }
            FlowNetworkEvaluation(graph);
        }
        oldNumber = numberOfUnusedPipes;
        numberOfUnusedPipes = getNumberOfUnusedPipes(graph);
        if (numberOfUnusedPipes == 0 || numberOfUnusedPipes >= oldNumber) {
            cout << "It is no longer possible to balance the water flow!" << endl;
            break;
        }
        cout << "It was possible to balance the water flow from " << oldNumber << " unused pipelines (i.e. with flow 0), to " << numberOfUnusedPipes << " pipelines!" << endl;
    }

    for (const auto& pair : origin) {
        Pipe* pipe = graph.findPipe(pair.first, pair.second.first);
        pipe->setCapacity(pair.second.second);
    }
}
