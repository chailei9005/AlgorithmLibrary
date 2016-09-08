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

vector<AlgorithmGraph::num_type> AlgorithmGraph::indegree;
vector<AlgorithmGraph::weight_type> AlgorithmGraph::dist;
vector<AlgorithmGraph::num_type> AlgorithmGraph::prev;
vector<bool> AlgorithmGraph::visit;

void AlgorithmGraph::test() {
    cout << "Test AlgorithmGraph:\n\nCreate graph:\n";
    cin.clear();
    auto g = createGraphFromInput();

    // Test once algorithm at each time
    //testTopoSort(g);
    //testDijkstra(g);
    //testPrim(g);
    //testHungarian(g);
    testKM(g);
    //testEdmondKarp(g);

    delete g;
}

void AlgorithmGraph::initGlobals(const num_type &nodeNum) {
    indegree = vector<num_type>(nodeNum, 0);
    dist = vector<AlgorithmGraph::weight_type>(nodeNum, INF);
    prev = vector<AlgorithmGraph::num_type>(nodeNum, NOT_NODE);
    visit = vector<bool>(nodeNum, false);
}

Graph* AlgorithmGraph::createGraphFromInput() {
    cout << "Input max node number: ";
    num_type n;
    cin >> n;
    initGlobals(n);
    cout << "Choose storage type (0->list, 1->matrix): ";
    int typeInt;
    cin >> typeInt;
    Graph *g = new Graph(n, static_cast<Graph::StorageType>(typeInt));
    cout << "Input graph matrix:\n";
    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < n; ++j) {
            weight_type w;
            cin >> w;
            g->addEdge(i, j, w);
            if (!isZero(w)) {
                ++indegree[j];
            }
        }
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
    for (auto i = 0; i < g->size(); ++i) {
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
    for (auto i = 0; i < size; ++i) {
        res.push_back(0);  // Initialize result
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        auto n = q.front();
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
        for (unsigned i = 0; i < res.size(); ++i) {
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
        auto n = getMinNotVisit(g);
        visit[n] = true;
        vector<num_type> adjNodes;
        g->getNeighbours(n, adjNodes);
        for (const auto &adjN : adjNodes) {
            auto w = g->getWeight(n, adjN);
            if (!visit[adjN] && dist[n] + w < dist[adjN]) {
                dist[adjN] = dist[n] + w;
                prev[adjN] = n;
            }
        }
    }
}

void AlgorithmGraph::printPathTo(const num_type &des, const vector<num_type> &prev_) {
    auto tmp = des;
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
    for (auto i = 0; i < g->size(); ++i) {
        cout << "From node " << src << " to " << i
            << " (length: " << dist[i] << "): ";
        printPathTo(i, prev);
        cout << endl;
    }
}

void AlgorithmGraph::prim(Graph *g) {
    dist[0] = 0;
    while (!isAllVisit()) {
        auto n = getMinNotVisit(g);
        visit[n] = true;
        vector<num_type> adjNodes;
        g->getNeighbours(n, adjNodes);
        for (const auto &adjN : adjNodes) {
            auto w = g->getWeight(n, adjN);
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
    for (auto i = 0; i < g->size(); ++i) {
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
    for (auto i = 0; i < leftN; ++i) {
        // Start with an unmatch node and find augmented path
        if (match[i] == NOT_NODE) {
            for (auto j = 0; j < n; ++j) {
                visit[j] = false;
            }
            if (findPath1(i, match, g)) {
                ++maxMatch;
            }
        }
    }
    return maxMatch;
}

bool AlgorithmGraph::findPath1(const num_type src,
                               vector<num_type> &match,
                               Graph *g) {
    // DFS version
    //vector<num_type> adjNodes;
    //g->getNeighbours(src, adjNodes);
    //for (const auto &adjN : adjNodes) {
    //    if (!visit[adjN]) {
    //        visit[adjN] = true;
    //        // DFS in alternative path, stop at unmatching point
    //        if (match[adjN] == NOT_NODE || findPath1(match[adjN], match, g)) {
    //            // Add matching edge
    //            match[src] = adjN;
    //            match[adjN] = src;
    //            return true;  // Find an augmented path
    //        }
    //    }
    //}
    //return false;  // No augmented path

    // BFS version
    queue<num_type> q;
    q.push(src);
    for (auto i = 0; i < g->size(); ++i) {
        prev[i] = NOT_NODE;
    }
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        vector<num_type> adjNodes;
        g->getNeighbours(v, adjNodes);
        for (const auto &adjN : adjNodes) {
            if (!visit[adjN]) {
                visit[adjN] = true;
                if (match[adjN] != NOT_NODE) { 
                    prev[match[adjN]] = v;
                    q.push(match[adjN]);
                } else {
                    auto a = v, b = adjN;
                    // Reverse matching edge and unmatching edge
                    while (a != NOT_NODE) {
                        auto tmp = match[a];
                        match[a] = b;
                        match[b] = a;
                        b = tmp;
                        a = prev[a];
                    }
                    return true;  // Find an augmented path
                }
            }
        }
    }
    return false;  // No augmented path
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
    for (auto i = 0; i < leftN; ++i) {
        if (match[i] != NOT_NODE) {
            cout << "(" << i << ", " << match[i] << "), ";
        }
        if ((++cnt) % 5 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

AlgorithmGraph::weight_type AlgorithmGraph::km(const num_type leftN,
                                               vector<num_type> &match,
                                               Graph *g,
                                               const bool max) {
    auto n = g->size();
    vector<weight_type> val(n);  // Store the value of each node

    // Make weight opposite to compute minimum cost matching
    if (!max) {
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < n; ++j) {
                auto w = g->getWeight(i, j);
                g->setWeight(i, j, -w);
            }
        }
    }

    // Init node values
    for (auto i = 0; i < n; ++i) {
        if (i < leftN) {  // Left node
            val[i] = -INF;
            for (auto j = leftN; j < n; ++j) {
                auto w = g->getWeight(i, j);
                if (val[i] < w) {  // Find max weight
                    val[i] = w;
                }
            }
        } else {  // Right node
            val[i] = 0;
        }
    }

    // Run
    for (auto i = 0; i < leftN; ++i) {
        while (1) {
            for (auto j = 0; j < n; ++j) {
                visit[j] = false;
            }
            if (findPath2(i, val, match, g)) {
                break;
            }
            // No augment path, update node value
            weight_type d = INF;
            for (auto i = 0; i < leftN; ++i) {
                if (visit[i]) {
                    for (auto j = leftN; j < n; ++j) {
                        if (!visit[j]) {
                            d = std::min(d, val[i] + val[j] - g->getWeight(i, j));
                        }
                    }
                }
            }
            for (auto i = 0; i < n; ++i) {
                if (i < leftN && visit[i]) {  // Left node in the augmented path
                    val[i] -= d;
                } else if (i >= leftN && visit[i]) {  // Right node in the augmented path
                    val[i] += d;
                }
            }
        }
    }

    // Compute total weight in the matching
    weight_type costs = 0;
    for (auto i = leftN; i < n; ++i) {
        if (match[i] != NOT_NODE) {
            costs += g->getWeight(match[i], i);
        }
    }
    if (!max) {
        // Make costs opposite to get minimum costs
        costs = -costs;
    }
    return costs;
}

bool AlgorithmGraph::findPath2(const num_type src,
                               vector<weight_type> &val,
                               vector<num_type> &match,
                               Graph *g) {
    visit[src] = true;
    vector<num_type> adjNodes;
    g->getNeighbours(src, adjNodes);
    for (const auto &adjN : adjNodes) {
        if (!visit[adjN] && val[src] + val[adjN] == g->getWeight(src, adjN)) {
            visit[adjN] = true;
            if (match[adjN] == NOT_NODE || findPath2(match[adjN], val, match, g)) {
                match[adjN] = src;
                return true;  // Find an augmented path
            }
        }
    }
    return false;  // No augmented path
}

void AlgorithmGraph::testKM(Graph *g) {
    cout << "Test KM algorithm:\n\n";
    cin.clear();
    cout << "Input left nodes number in the bipartite graph: ";
    num_type leftN;
    cin >> leftN;
    // Comute maximum matching
    vector<num_type> match1(g->size(), NOT_NODE);
    cout << "Max matching costs: " << km(leftN, match1, g) << endl;
    cout << "Max matching edges: ";
    int cnt = 0;
    for (auto i = leftN; i < g->size(); ++i) {
        if (match1[i] != NOT_NODE) {
            cout << "(" << match1[i] << ", " << i << "), ";
        }
    }
    cout << endl;
    // Compute minimum matching
    vector<num_type> match2(g->size(), NOT_NODE);
    cout << "Min matching costs: " << km(leftN, match2, g, false) << endl;
    cout << "Min matching edges: ";
    cnt = 0;
    for (auto i = leftN; i < g->size(); ++i) {
        if (match2[i] != NOT_NODE) {
            cout << "(" << match2[i] << ", " << i << "), ";
        }
    }
    cout << endl;
}

AlgorithmGraph::weight_type AlgorithmGraph::EdmondKarp(const num_type &src,
                                                       const num_type &des,
                                                       Graph *g) {
    auto n = g->size();
    weight_type maxflow = 0;
    while (1) {
        // Find an augmented path and return its flow increase
        auto increase = getIncreaseFromPath(src, des, g);
        if (increase == 0) {  // No augmenting path
            break;
        } else {
            auto last = des;
            while (last != src) {  // Update capacity
                auto pre = prev[last];
                g->increaseWeight(pre, last, -increase);  // Forward edge minus increase
                g->increaseWeight(last, pre, increase);  // Reverse edge add increase
                last = pre;
            }
            maxflow += increase;  // Update max flow
        }
    }
    return maxflow;
}

AlgorithmGraph::weight_type AlgorithmGraph::getIncreaseFromPath(const num_type &src,
                                                                const num_type &des,
                                                                Graph *g) {
    auto n = g->size();
    vector<weight_type> flow(n, 0);  // Store the maximum flow at each node in the augmented path
    flow[src] = INF;
    for (auto i = 0; i < n; ++i) {
        prev[i] = NOT_NODE;
    }
    // BFS
    queue<num_type> q;
    q.push(src);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        if (v == des) {  // Found an augmented path
            break;
        }
        for (auto i = 0; i < n; ++i) {
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
