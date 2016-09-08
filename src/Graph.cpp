#include "Graph.h"

#include <iostream>
#include <stdexcept>
#include <string>

using sl::Graph;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::string;

Graph::Graph(const num_type &n, const StorageType &type_)
    : type(type_), size_(n) {
    switch (type) {
        case ADJ_LIST:
            for (auto i = 0; i < n; ++i) {
                adjList.push_back(HeadNode());
            }
            break;
        case ADJ_MATRIX:
            for (auto i = 0; i < n; ++i) {
                adjMatrix.push_back(vector<weight_type>(n, 0));
            }
            break;
        default:
            break;
    }
}

Graph::~Graph() {
    switch (type) {
        case ADJ_LIST:
            for (HeadNode &node : adjList) {
                delete node.adjNodes;
                node.adjNodes = nullptr;
            }
            break;
        case ADJ_MATRIX:
            break;
        default:
            break;
    }
}

bool Graph::isValid(const num_type &n) const {
    return n >= 0 && n < size_;
}

void Graph::checkValid(const num_type &n) const {
    if (!isValid(n)) {
        throw std::range_error("Graph.checkValid(): node number is not valid");
    }
}

Graph::num_type Graph::size() const {
    return size_;
}

void Graph::getNeighbours(const num_type &n,
                          vector<num_type> &nodes) const {
    checkValid(n);
    nodes.clear();
    switch (type) {
        case ADJ_LIST: {
            auto adjNodes = adjList[n].adjNodes;
            if (adjNodes) {
                for (const auto &adjNode : (*adjNodes)) {
                    nodes.push_back(adjNode.num);
                }
            }
            break;
        }     
        case ADJ_MATRIX:
            for (auto i = 0; i < size_; ++i) {
                if (!isZero(adjMatrix[n][i])) {
                    nodes.push_back(i);
                }
            }
            break;
        default:
            break;
    }
}

Graph::weight_type Graph::getWeight(const num_type &from,
                                    const num_type &to) const {
    checkValid(from);
    checkValid(to);
    weight_type res = 0;
    switch (type) {
        case ADJ_LIST: {
            auto adjNodes = adjList[from].adjNodes;
            if (adjNodes) {
                for (const auto &adjNode : (*adjNodes)) {
                    if (adjNode.num == to) {
                        res = adjNode.weight;
                        break;
                    }
                }
            }
            break;
        }
        case ADJ_MATRIX:
            res = adjMatrix[from][to];
            break;
        default:
            break;
    }
    return res;
}

void Graph::setWeight(const num_type &from, const num_type &to, const weight_type &w) {
    checkValid(from);
    checkValid(to);
    if (isZero(w)) {
        removeEdge(from, to);
    }
    switch (type) {
        case ADJ_LIST: {
            auto adjNodes = adjList[from].adjNodes;
            if (adjNodes) {
                for (auto &adjNode : (*adjNodes)) {
                    if (adjNode.num == to) {
                        adjNode.weight = w;
                        break;
                    }
                }
            }
            break;
        }
        case ADJ_MATRIX:
            adjMatrix[from][to] = w;
            break;
        default:
            break;
    }
}

void Graph::increaseWeight(const num_type &from, const num_type &to, const weight_type &increase) {
    checkValid(from);
    checkValid(to);
    auto cur = getWeight(from, to);
    if (isZero(cur + increase)) {
        removeEdge(from, to);
    } else {
        setWeight(from, to, cur + increase);
    }
}

void Graph::addEdge(const num_type &from, const num_type &to, const weight_type &w) {
    checkValid(from);
    checkValid(to);
    switch (type) {
        case ADJ_LIST: {
            if (!isZero(w)) {
                auto &headNode = adjList[from];
                if (!headNode.adjNodes) {
                    headNode.adjNodes = new std::list<AdjNode>();
                }
                headNode.adjNodes->push_back(AdjNode(to, w));
            }
            break;
        }
        case ADJ_MATRIX:
            adjMatrix[from][to] = w;
            break;
        default:
            break;
    }
}

void Graph::removeEdge(const num_type &from, const num_type &to) {
    checkValid(from);
    checkValid(to);
    switch (type) {
        case ADJ_LIST: {
            auto &headNode = adjList[from];
            if (headNode.adjNodes) {
                auto it = headNode.adjNodes->begin();
                while (it != headNode.adjNodes->end()) {
                    if (it->num == to) {
                        headNode.adjNodes->erase(it);
                        break;
                    }
                    ++it;
                }
            }
            break;
        }
        case ADJ_MATRIX:
            adjMatrix[from][to] = 0;
            break;
        default:
            break;
    }
}

void Graph::print() const {
    cout << "This graph is stored in an ";
    switch (type) {
        case ADJ_LIST:
            cout << "adjacent list.\n";
            break;
        case ADJ_MATRIX:
            cout << "adjacent matrix.\n";
            break;
        default:
            break;
    }
    cout << "Range of node number: [0, " << (size_ - 1)
        << "]\nAdjacent nodes and edge weight:\n";
    vector<num_type> adjs;
    for (auto i = 0; i < size_; ++i) {
        getNeighbours(i, adjs);
        cout << "Node[" << i << "]: ";
        if (adjs.empty()) {
            cout << "none";
        } else {
            for (const auto &n : adjs) {
                cout << n << "(" << getWeight(i, n) << "), ";
            }
        }
        cout << endl;
    }
}

void Graph::test() {
    cout << "Test Graph:\n\n";
    cin.clear();
    cout << "Input max node number: ";
    num_type size;
    cin >> size;
    cout << endl;
    Graph g1(size), g2(size, Graph::StorageType::ADJ_MATRIX);
    num_type a, b;
    weight_type w;
    string oper;
    cout << "Operations available:\n"
        << "1. add a b w (add edge (a, b) with weight w)\n"
        << "2. r a b     (remove edge (a, b))\n"
        << "3. p         (print graph info)\n"
        << "4. sw a b w  (set the weight of edge(a, b) to w)\n"
        << endl;
    while (1) {
        cout << "Input operation: ";
        cin >> oper;
        if (oper == "add") {
            cin >> a >> b >> w;
            g1.addEdge(a, b, w);
            g2.addEdge(a, b, w);
        } else if (oper == "r") {
            cin >> a >> b;
            g1.removeEdge(a, b);
            g2.removeEdge(a, b);
        } else if (oper == "p") {
            cout << "Type1:" << endl;
            g1.print();
            cout << "\nType2:" << endl;
            g2.print();
        } else if (oper == "sw") {
            cin >> a >> b >> w;
            g1.setWeight(a, b, w);
            g2.setWeight(a, b, w);
        } else {
            cout << "Invalid operation." << endl;
        }
    }
}
