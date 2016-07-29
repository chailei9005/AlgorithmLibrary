#include "Graph.h"

#include <iostream>
#include <stdexcept>

using sl::Graph;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

Graph::Graph(const num_type &n, const StorageType &type_)
    : type(type_), size_(n) {
    switch (type) {
        case ADJ_LIST:
            for (num_type i = 0; i < n; ++i) {
                adjList.push_back(HeadNode());
            }
            break;
        case ADJ_MATRIX:
            for (num_type i = 0; i < n; ++i) {
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

void Graph::getNeighbours(const num_type &n,
                            std::vector<num_type> &nodes) const {
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
            for (num_type i = 0; i < size_; ++i) {
                if (adjMatrix[n][i]) {
                    nodes.push_back(i);
                }
            }
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
        << "]\nAdjacent nodes:\n";
    vector<num_type> adjs;
    for (num_type i = 0; i < size_; ++i) {
        getNeighbours(i, adjs);
        cout << "Node[" << i << "]: ";
        if (adjs.empty()) {
            cout << "none";
        } else {
            for (const auto &n : adjs) {
                cout << n << " ";
            }
        }
        cout << endl;
    }
}

void Graph::test() {
    Graph g1(5), g2(10, Graph::StorageType::ADJ_MATRIX);
    g1.print();
    cout << endl;
    g2.print();
}
