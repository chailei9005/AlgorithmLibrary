#pragma once

#include "Base.h"
#include <list>
#include <vector>

NS_BEGIN

/*
A graph data structure.

For usage, see function test().
*/
class Graph {
public:
    // Type for node number value
    typedef long num_type;

    // Type for edge getWeight
    typedef long weight_type;

    // Weight value for adjacent matrix
    // if there is not edge between two nodes
    static const weight_type NONE_EDGE_WEIGHT;

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
    Return the max node number of the graph.
    */
    num_type size() const;

    /*
    Get the adjacent nodes of one node.

    @param n the node to find
    @param nodes the result will be stored in this field
    */
    void getNeighbours(const num_type &n, std::vector<num_type> &nodes) const;

    /*
    Get the weight of the edge between two nodes.

    @param from the start node
    @param to the end node
    @return the weight value. If no edge exists,
            return NONE_EDGE_WEIGHT
    */
    weight_type getWeight(const num_type &from, const num_type &to) const;

    /*
    Set the weight of the edge between two nodes.

    @param from the start node
    @param to the end node
    @param w the new weight value
    */
    void setWeight(const num_type &from, const num_type &to, const weight_type &w);

    /*
    Increase the weight of the edge between two nodes.

    @param from the start node
    @param to the end node
    @param increase the increase value
    */
    void increaseWeight(const num_type &from, const num_type &to, const weight_type &increase);

    /*
    Add an edge between two nodes.

    @param from the start node
    @param to the end node
    @param w the getWeight of the edge
    */
    void addEdge(const num_type &from, const num_type &to, const weight_type &w = 0);

    /*
    Remove an edge between two nodes.

    @param from the start node
    @param to the end node
    */
    void removeEdge(const num_type &from, const num_type &to);

private:
    /*
    Definition for an adjacent in an adjacent list.
    */
    struct AdjNode {
        num_type num;
        weight_type weight;

        AdjNode(const num_type num_, const weight_type w = NONE_EDGE_WEIGHT)
            : num(num_), weight(w) {}
    };

    /*
    Definition for a head node in an adjacent list.
    */
    struct HeadNode {
        std::list<AdjNode> *adjNodes;

        HeadNode() : adjNodes(nullptr) {}
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
    8
    add 1 0 1
    add 1 2 2
    add 1 4 1
    add 2 4 3
    add 2 5 10
    add 3 1 4
    add 3 6 5
    add 4 3 2
    add 4 6 8
    add 4 7 4
    add 4 5 2
    add 5 7 6
    add 7 6 1
    */
    static void test();
};

NS_END
