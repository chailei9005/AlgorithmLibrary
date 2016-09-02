#pragma once

#include "Base.h"
#include "Graph.h"

NS_BEGIN

/*
Contains algorithms for graph.

For usage, see function test().
*/
class AlgorithmGraph {
public:
    typedef Graph::num_type num_type;
    typedef Graph::weight_type weight_type;

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

    Sample #1:
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
    {1|2}

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

    The shortest path:
    From node 2 to 0 (length: 10): 2 -> 4 -> 3 -> 1 -> 0
    From node 2 to 1 (length: 9): 2 -> 4 -> 3 -> 1
    From node 2 to 2 (length: 0): 2
    From node 2 to 3 (length: 5): 2 -> 4 -> 3
    From node 2 to 4 (length: 3): 2 -> 4
    From node 2 to 5 (length: 5): 2 -> 4 -> 5
    From node 2 to 6 (length: 8): 2 -> 4 -> 7 -> 6
    From node 2 to 7 (length: 7): 2 -> 4 -> 7
    */
    static void dijkstra(Graph *g, const num_type &src);
    static void printPathTo(const num_type &des, const std::vector<num_type> &prev_);
    static void testDijkstra(Graph *g);

    /*
    Prim's algorithm to find minimum spanning tree (undirected graph).
    A minimun spanning tree exists iff the undirected graph is connected.

    @param g the graph object

    Sample #1: (each edge is added twice to construct an undirected graph):
    8 0
    0 1 3
    1 0 3
    1 2 2
    2 1 2
    1 4 1
    4 1 1
    1 3 4
    3 1 4
    2 4 3
    4 2 3
    2 5 10
    5 2 10
    3 4 2
    4 3 2
    4 5 7
    5 4 7
    3 6 5
    6 3 5
    4 6 8
    6 4 8
    4 7 4
    7 4 4
    5 7 6
    7 5 6
    6 7 1
    7 6 1

    Ans:
    The edges of the minimum spanning tree:
    (0, 1), (1, 2), (4, 3), (1, 4), (7, 5), (7, 6), (4, 7),
    */
    static void prim(Graph *g);
    static void testPrim(Graph *g);

    /*
    Hungarian's algorithm to find the maximum matching number
    in an unweighted bipartite graph.

    Reference: http://blog.csdn.net/pi9nc/article/details/11848327

    Precondition: the graph must be a bipartitle graph.

    @param leftN the left node number of the bipartite graph
    @param match if match[a] = b, then edge(a, b) is one of the
                 matching edge after running this algorithm.
                 if match[a] = -1, then node a is not matched.
    @param g the graph object
    @return the maximum matching number of the graph

    Sample #1: (ans: 4; edges: (0, 6), (1, 4), (2, 5), (3, 7))
    8 0
    0 4 1
    4 0 1
    0 6 1
    6 0 1
    1 4 1
    4 1 1
    2 4 1
    4 2 1
    2 5 1
    5 2 1
    3 6 1
    6 3 1
    3 7 1
    7 3 1
    4

    Sample #2: (ans: 3; edges: (0, 4), (1, 3), (2, 5))
    7 0
    0 4 1
    4 0 1
    1 3 1
    3 1 1
    1 4 1
    4 1 1
    4 2 1
    2 4 1
    2 5 1
    5 2 1
    2 6 1
    6 2 1
    3

    Sample #3: (ans: 3; edges: (0, 6), (1, 4), (2, 5))
    8 0
    0 4 1
    4 0 1
    0 6 1
    6 0 1
    1 4 1
    4 1 1
    2 4 1
    4 2 1
    2 5 1
    5 2 1
    2 7 1
    7 2 1
    3 6 1
    6 3 1
    4
    */
    static num_type hungarian(const num_type leftN, std::vector<num_type> &match, Graph *g);
    static bool buildAugmentPath(const num_type src, std::vector<num_type> &match, Graph *g);
    static void testHungarian(Graph *g);

    /*
    Edmond-Karp's algorithm to solve maximum flow problem.

    Reference: http://www.cnblogs.com/zsboy/archive/2013/01/27/2878810.html

    Default:
    src: node[0];
    des: node[node_num - 1];

    @param src the start node
    @param des the destination node
    @param g the graph object (need to use adjacent matrix)
    @return the maximum flow value

    Sample #1: (ans: 5)
    6 1
    0 1 3
    0 2 2
    1 2 1
    1 4 4
    1 3 3
    2 4 2
    3 5 2
    4 5 3

    Sample #2: (ans: 14)
    6 1
    0 1 15
    0 2 4
    1 4 12
    2 3 10
    3 1 5
    4 2 3
    4 5 7
    3 5 10
    */
    static weight_type EdmondKarp(const num_type &src, const num_type &des, Graph *g);
    static weight_type getIncreaseFromAugmentPath(const num_type &src, const num_type &des, Graph *g);
    static void testEdmondKarp(Graph *g);

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
    Create a graph object from command input.

    @return a pointer to the graph created
    */
    static sl::Graph* createGraphFromCommand();

    /*
    Initialize global arrays.
    */
    static void initGlobals(const num_type &nodeNum);

    /*
    Check if all the nodes have been visited.
    */
    static bool isAllVisit();

    /*
    Get an un-visited node that has the smallest dist value.
    */
    static num_type getMinNotVisit(const Graph *g);

public:
    /*
    Test the function of the class.
    */
    static void test();
};

NS_END
