#pragma once

#include "Graph.h"

namespace sl {

/*
Contains algorithms for graph.

For usage, see function test().
*/
class AlgorithmGraph {
public:
    typedef Graph::num_type num_type;
    typedef Graph::weight_type weight_type;

    /*
    Test the function of the class.
    */
    static void test();

    /*
    Swap the value of two elements.

    @param a the first element
    @param b the second element
    */
    template <typename T>
    static void swap(T &a, T &b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    /*
    Topological sorting.

    @param g the graph object
    @param res the result will be stored in this field
    @return true if the graph contains no cycle and thus
            sort succeed, false otherwise

    Sample #1: (ans: 0 1 2 5 4 3 7 6(not unique), no cycle)
    8 0
    0 1 1
    1 2 1
    1 4 1
    1 3 1
    2 4 1
    2 5 1
    3 6 1
    4 3 1
    4 6 1
    4 7 1
    5 7 1
    5 4 1
    7 6 1

    Sample #2: (has cycle)
    4 1
    0 1 1
    1 2 1
    2 3 1
    3 1 1
    */
    static bool topoSort(Graph *g, std::vector<num_type> &res);
    static void testTopoSort(Graph *g);

private:
    static std::vector<num_type> indegree;

    /*
    Create a graph object from command input.

    @return a pointer to the graph created
    */
    static sl::Graph* createGraphFromCommand();

};

}
