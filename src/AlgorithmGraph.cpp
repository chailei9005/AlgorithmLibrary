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

const AlgorithmGraph::num_type AlgorithmGraph::NOT_NODE = -1;
const AlgorithmGraph::weight_type AlgorithmGraph::INF = 2147483647;

vector<unsigned long> AlgorithmGraph::indegree;
vector<bool> AlgorithmGraph::visit;
vector<AlgorithmGraph::weight_type> AlgorithmGraph::dist;
vector<AlgorithmGraph::num_type> AlgorithmGraph::prev;

void AlgorithmGraph::test() {
    cout << "Test AlgorithmGraph:\n\nCreate graph:\n";
    cin.clear();
    auto g = createGraphFromCommand();

    // Test once algorithm at each time
    //testTopoSort(g);
    testDijkstra(g);

    delete g;
}

void AlgorithmGraph::initGlobals(const num_type &nodeNum) {
    indegree = vector<unsigned long>(nodeNum, 0);
    visit = vector<bool>(nodeNum, false);
    dist = vector<AlgorithmGraph::weight_type>(nodeNum, INF);
    prev = vector<AlgorithmGraph::num_type>(nodeNum, NOT_NODE);
}

Graph* AlgorithmGraph::createGraphFromCommand() {
    num_type size, a, b;
    weight_type w;
    int typeInt;
    cout << "Input max node number: ";
    cin >> size;
    initGlobals(size);
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
    num_type size = g->size(), nodeCnt = 0;
    queue<size_t> q;
    for (num_type i = 0; i < size; ++i) {
        res.push_back(0);  // Initialize result
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        num_type n = q.front();
        q.pop();
        res[nodeCnt++] = n;  // Record result
        vector<num_type> adjNodes;
        g->getNeighbours(n, adjNodes);
        for (const auto &adjN : adjNodes) {
            if (--indegree[adjN] == 0) {
                q.push(adjN);
            }
        }
    }
    return nodeCnt == size;
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

void AlgorithmGraph::dijkstra(Graph *g, const num_type &src) {
    // Priority queue to find the vertex with the minimum dist
    priority_queue<num_type, vector<num_type>, cmpMinRoot> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        num_type n = q.top();
        q.pop();

        // Get a vertex which hasn't been visited
        while (!q.empty() && visit[n]) {
            n = q.top();
            q.pop();
        }
        // If all vertexes have been visited, exit
        if (q.empty() && visit[n]) {
            break;
        }

        visit[n] = true;
        vector<num_type> adjNodes;
        g->getNeighbours(n, adjNodes);
        for (const auto &adjN : adjNodes) {
            // Calculate weight may be time-consuming
            // when using adjacent list to store the graph.
            // For code readability, ignore optimization.
            weight_type w = g->getWeight(n, adjN);
            if (!visit[adjN] && (dist[n] + w < dist[adjN])) {
                dist[adjN] = dist[n] + w;
                prev[adjN] = n;
                q.push(adjN);
            }
        }
    }
}

void AlgorithmGraph::printPathTo(const vector<num_type> &prev_,
                                 const num_type &des) {
    num_type tmp = des;
    if (prev_[tmp] != NOT_NODE) {
        printPathTo(prev_, prev_[tmp]);
        cout << " -> ";
    }
    cout << tmp;
}

void AlgorithmGraph::testDijkstra(Graph *g) {
    cout << "Test dijkstra:\n\n";
    cin.clear();
    num_type src;
    cout << "Input start vertex: ";
    cin >> src;
    dijkstra(g, src);
    cout << "The shortest path:" << endl;
    for (num_type i = 0; i < g->size(); ++i) {
        cout << "From node " << src << " to " << i
            << " (length: " << dist[i] << "): ";
        printPathTo(prev, i);
        cout << endl;
    }
}
