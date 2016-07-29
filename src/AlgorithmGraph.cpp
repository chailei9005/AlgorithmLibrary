#include "AlgorithmGraph.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::queue;
using std::priority_queue;
using sl::AlgorithmGraph;
using sl::Graph;

vector<AlgorithmGraph::num_type> AlgorithmGraph::indegree;

void AlgorithmGraph::test() {
    cout << "Test AlgorithmGraph:\n\nCreate graph:\n";
    cin.clear();
    auto g = createGraphFromCommand();
    testTopoSort(g);
    delete g;
}

Graph* AlgorithmGraph::createGraphFromCommand() {
    num_type size, a, b;
    weight_type w;
    int typeInt;
    cout << "Input max node number: ";
    cin >> size;
    indegree = std::vector<num_type>(size, 0);
    cout << "Choose storage type (0->list, 1->matrix): ";
    cin >> typeInt;
    Graph *g = new Graph(size, static_cast<Graph::StorageType>(typeInt));
    cout << "Input edges to add to graph: (EOF to end)\n";
    while (cin >> a >> b >> w) {
        g->addEdge(a, b, w);
        ++indegree[b];
    }
    cout << endl;
    return g;
}

bool AlgorithmGraph::topoSort(Graph *g, vector<num_type> &res) {
    res.clear();
    num_type n = g->size(), nodeCnt = 0;
    queue<size_t> q;
    for (num_type i = 0; i < n; ++i) {
        res.push_back(0);  // Initialize result
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        num_type v = q.front();
        q.pop();
        res[nodeCnt++] = v;  // Record result
        vector<num_type> adjNodes;
        g->getNeighbours(v, adjNodes);
        for (const auto &adjN : adjNodes) {
            if (--indegree[adjN] == 0) {
                q.push(adjN);
            }
        }
    }
    return nodeCnt == n;
}

void AlgorithmGraph::testTopoSort(Graph *g) {
    cout << "Test topological sort:\n\n";
    cin.clear();
    vector<num_type> res;
    if (topoSort(g, res)) {
        cout << "Graph contains no cycle\n"
            << "Sort result: ";
        for (size_t i = 0; i < res.size(); ++i) {
            cout << res[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Graph contains cycle\n"
            << "Sort failed" << endl;
    }
}
