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

    /*
    Dijkstra's algorithm

    If negative edges exist, avoid checking visited condition
    when traversing the adjacent nodes. Unfortuantely, this
    will increase the time complexity.
    
    @param g the graph object
    @param src the start node number

    Sample #1 (start at node 1):
    8 0
    1 0 1
    1 2 2
    1 4 1
    2 4 3
    2 5 10
    3 1 4
    3 6 5
    4 3 2
    4 6 8
    4 7 4
    4 5 2
    5 7 6
    7 6 1
    1

    Ans:
    The shortest path:
    From node 1 to 0 (length: 1): 1 -> 0
    From node 1 to 1 (length: 0): 1
    From node 1 to 2 (length: 2): 1 -> 2
    From node 1 to 3 (length: 3): 1 -> 4 -> 3
    From node 1 to 4 (length: 1): 1 -> 4
    From node 1 to 5 (length: 3): 1 -> 4 -> 5
    From node 1 to 6 (length: 6): 1 -> 4 -> 7 -> 6
    From node 1 to 7 (length: 5): 1 -> 4 -> 7
    */
    static void dijkstra(Graph *g, const num_type &src);
    static void printPathTo(const std::vector<num_type> &prev_, const num_type &des);
    static void testDijkstra(Graph *g);

private:
    /*
    Constants.
    */
    static const num_type NOT_NODE;
    static const weight_type INF;

    /*
    Fields for searching algorithms.
    */
    static std::vector<unsigned long> indegree;
    static std::vector<bool> visit;
    static std::vector<weight_type> dist;
    static std::vector<num_type> prev;

    /*
    A comparator used in a min-root priority queue.
    */
    struct cmpMinRoot {
        bool operator()(const num_type &a,
                        const num_type &b) const {
            return dist[a] > dist[b];
        }
    };

    /*
    Create a graph object from command input.

    @return a pointer to the graph created
    */
    static sl::Graph* createGraphFromCommand();

    /*
    Initialize global arrays.
    */
    static void initGlobals(const num_type &nodeNum);

};

}
