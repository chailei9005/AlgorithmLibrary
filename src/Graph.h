#pragma once

#include <list>
#include <vector>

namespace sl {

/*
A graph data structure.

For usage, see function test().
*/
class Graph {
public:
    // Type for node number value
    typedef unsigned num_type;

    // Type for edge weight
    typedef long weight_type;

    /*
    Definition of the storage type of the graph.
    */
    enum StorageType {
        ADJ_LIST,
        ADJ_MATRIX
    };

    /*
    Initialize the graph.

    @param n the number of nodes in the graph
    @param type_ the storage type of the graph
    */
    Graph(const num_type &n, const StorageType &type_ = ADJ_LIST);

    /*
    Release the space.
    */
    ~Graph();

    /*
    Check if the number of the node is valid in the graph

    @param n the node number to check
    */
    bool isValid(const num_type &n) const;

    /*
    Print the information of the graph
    */
    void print() const;

    /*
    Get the adjacent nodes of one node.

    @param n the node to find
    @param nodes the result will be stored in this field
    */
    void getNeighbours(const num_type &n,
                         std::vector<num_type> &nodes) const;

private:
    /*
    Definition for an adjacent in an adjacent list.
    */
    struct AdjNode {
        num_type num;
        weight_type weight;

        AdjNode(const num_type num_, const weight_type w = 0)
            : num(num_), weight(w) {
        }
    };

    /*
    Definition for a head node in an adjacent list.
    */
    struct HeadNode {
        std::list<AdjNode> *adjNodes;

        HeadNode() : adjNodes(new std::list<AdjNode>()) {
        }
    };

    std::vector<HeadNode> adjList;

    std::vector<std::vector<weight_type>> adjMatrix;

    StorageType type;

    num_type size_;

    /*
    Check if the number of the node is valid in the graph.

    @param n the node number to check
    @throw std::range_error if the node is not valid
    */
    void checkValid(const num_type &n) const;

public:
    /*
    Test the function of the class.

    Sample #1:
    */
    static void test();
};

}
