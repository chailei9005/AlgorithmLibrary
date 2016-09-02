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
    //testDijkstra(g);
    //testPrim(g);
    testHungarian(g);
    //testEdmondKarp(g);

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

bool AlgorithmGraph::isAllVisit() {
    bool res = true;
    for (const auto &v : visit) {
        if (!v) {
            res = false;
        }
    }
    return res;
}

AlgorithmGraph::num_type AlgorithmGraph::getMinNotVisit(const Graph *g) {
    num_type n;
    weight_type min = INF;
    for (num_type i = 0; i < g->size(); ++i) {
        if (!visit[i] && dist[i] < min) {
            min = dist[i];
            n = i;
        }
    }
    return n;
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
    dist[src] = 0;
    while (!isAllVisit()) {
        num_type n = getMinNotVisit(g);
        visit[n] = true;
        vector<num_type> adjNodes;
        g->getNeighbours(n, adjNodes);
        for (const auto &adjN : adjNodes) {
            weight_type w = g->getWeight(n, adjN);
            if (!visit[adjN] && dist[n] + w < dist[adjN]) {
                dist[adjN] = dist[n] + w;
                prev[adjN] = n;
            }
        }
    }
}

void AlgorithmGraph::printPathTo(const num_type &des, const vector<num_type> &prev_) {
    num_type tmp = des;
    if (prev_[tmp] != NOT_NODE) {
        printPathTo(prev_[tmp], prev_);
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
        printPathTo(i, prev);
        cout << endl;
    }
}

void AlgorithmGraph::prim(Graph *g) {
    dist[0] = 0;
    while (!isAllVisit()) {
        num_type n = getMinNotVisit(g);
        visit[n] = true;
        vector<num_type> adjNodes;
        g->getNeighbours(n, adjNodes);
        for (const auto &adjN : adjNodes) {
            weight_type w = g->getWeight(n, adjN);
            if (!visit[adjN] && w < dist[adjN]) {
                dist[adjN] = w;
                prev[adjN] = n;
            }
        }
    }
}

void AlgorithmGraph::testPrim(Graph *g) {
    cout << "Test prim:\n\n";
    cin.clear();
    prim(g);
    cout << "The edges of the minimum spanning tree:" << endl;
    for (num_type i = 0; i < g->size(); ++i) {
        if (prev[i] != NOT_NODE) {
            cout << "(" << prev[i] << ", " << i << "), ";
        }
    }
    cout << endl;
}

AlgorithmGraph::num_type AlgorithmGraph::hungarian(const num_type leftN, 
                                                   vector<num_type> &match,
                                                   Graph *g) {
    num_type n = g->size(), maxMatch = 0;
    for (num_type i = 0; i < leftN; ++i) {
        // Start with an unmatch node and find augmenting path
        if (match[i] == NOT_NODE) {
            for (num_type j = 0; j < n; ++j) {
                visit[j] = false;
            }
            if (buildAugmentPath(i, match, g)) {
                ++maxMatch;
            }
        }
    }
    return maxMatch;
}

bool AlgorithmGraph::buildAugmentPath(const num_type src, vector<num_type> &match, Graph *g) {
    // DFS version
    vector<num_type> adjNodes;
    g->getNeighbours(src, adjNodes);
    for (const auto &adjN : adjNodes) {
        if (!visit[adjN]) {
            visit[adjN] = true;
            // DFS in alternative path, stop at unmatching point
            if (match[adjN] == NOT_NODE || buildAugmentPath(match[adjN], match, g)) {
                // Add matching edge
                match[src] = adjN;
                match[adjN] = src;
                return true;  // Find an augmenting path
            }
        }
    }
    return false;  // No augmenting path

    // BFS version
    //queue<num_type> q;
    //q.push(src);
    //for (num_type i = 0; i < g->size(); ++i) {
    //    prev[i] = NOT_NODE;
    //}
    //while (!q.empty()) {
    //    num_type v = q.front();
    //    q.pop();
    //    vector<num_type> adjNodes;
    //    g->getNeighbours(v, adjNodes);
    //    for (const auto &adjN : adjNodes) {
    //        if (!visit[adjN]) {
    //            visit[adjN] = true;
    //            if (match[adjN] != NOT_NODE) { 
    //                prev[match[adjN]] = v;
    //                q.push(match[adjN]);
    //            } else {
    //                num_type a = v, b = adjN;
    //                // Reverse matching edge and unmatching edge
    //                while (a != NOT_NODE) {
    //                    num_type tmp = match[a];
    //                    match[a] = b;
    //                    match[b] = a;
    //                    b = tmp;
    //                    a = prev[a];
    //                }
    //                return true;  // Find an augmenting path
    //            }
    //        }
    //    }
    //}
    //return false;  // No augmenting path
}

void AlgorithmGraph::testHungarian(Graph *g) {
    cout << "Test hungarian:\n\n";
    cin.clear();
    cout << "Input left nodes number in the bipartite graph: ";
    num_type leftN;
    cin >> leftN;
    vector<num_type> match(g->size(), NOT_NODE);
    cout << "Max matching number: " << hungarian(leftN, match, g) << endl;
    cout << "Match edges:" << endl;
    int cnt = 0;
    for (num_type i = 0; i < leftN; ++i) {
        if (match[i] != NOT_NODE) {
            cout << "(" << i << ", " << match[i] << "), ";
        }
        if ((++cnt) % 5 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

AlgorithmGraph::weight_type AlgorithmGraph::EdmondKarp(const num_type &src,
                                                       const num_type &des,
                                                       Graph *g) {
    num_type n = g->size();
    weight_type maxflow = 0;
    while (1) {
        // Find an augment path and return its flow increase
        int increase = getIncreaseFromAugmentPath(src, des, g);
        if (increase == 0) {  // No augmenting path
            break;
        } else {
            weight_type last = des;
            while (last != src) {  // Update capacity
                num_type pre = prev[last];
                g->increaseWeight(pre, last, -increase);  // Forward edge minus increase
                g->increaseWeight(last, pre, increase);  // Reverse edge add increase
                last = pre;
            }
            maxflow += increase;  // Update max flow
        }
    }
    return maxflow;
}

AlgorithmGraph::weight_type AlgorithmGraph::getIncreaseFromAugmentPath(const num_type &src,
                                                                       const num_type &des,
                                                                       Graph *g) {
    num_type n = g->size();
    vector<weight_type> flow(n, 0);  // Store the maximum flow at each node in the augment path
    flow[src] = INF;
    for (num_type i = 0; i < n; ++i) {
        prev[i] = NOT_NODE;
    }
    // BFS
    queue<num_type> q;
    q.push(src);
    while (!q.empty()) {
        num_type v = q.front();
        q.pop();
        if (v == des) {  // Found an augmenting path
            break;
        }
        for (num_type i = 0; i < n; ++i) {
            if (i != src && g->getWeight(v, i) > 0 && prev[i] == NOT_NODE) {
                prev[i] = v;
                flow[i] = std::min(flow[v], g->getWeight(v, i));
                q.push(i);
            }
        }
    }
    return prev[des] == NOT_NODE ? 0 : flow[des];  // Return the flow increase in the path
}

void AlgorithmGraph::testEdmondKarp(Graph *g) {
    cout << "Test Edmond-Karp:\n\n";
    cin.clear();
    cout << "Max flow: " << EdmondKarp(0, g->size() - 1, g) << endl;
}
