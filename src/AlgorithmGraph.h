#pragma once

#include "Base.h"
#include "Graph.h"

NS_BEGIN

/*
Contains algorithms for graph.
This is a singleton.

For usage, see function test().
*/
class AlgorithmGraph {
public:
    typedef Graph::num_type num_type;
    typedef Graph::weight_type weight_type;

    ~AlgorithmGraph();
    
    /*
    Forbid copy
    */
    AlgorithmGraph(const AlgorithmGraph &m) = delete;
    AlgorithmGraph& operator=(const AlgorithmGraph &m) = delete;

    /*
    Return the only instance
    */
    static AlgorithmGraph* getInstance();

    /*
    Topological sorting.

    @param g the graph object
    @param res the result will be stored in this field
    @return true if the graph contains no cycle and thus
            sort succeed, false otherwise

    Sample #1: (ans: 0 1 2 5 4 3 7 6(not unique), no cycle)
    8 0
    0 1 0 0 0 0 0 0
    0 0 1 1 1 0 0 0
    0 0 0 0 1 1 0 0
    0 0 0 0 0 0 1 0
    0 0 0 1 0 0 1 1
    0 0 0 0 1 0 0 1
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 1 0

    Sample #2: (has cycle)
    4 1
    0 1 0 0
    0 0 1 0
    0 0 0 1
    0 1 0 0
    */
    bool topoSort(Graph *g, std::vector<num_type> &res);
    void testTopoSort(Graph *g);

    /*
    Dijkstra algorithm

    If negative edges exist, avoid checking visited condition
    when traversing the adjacent nodes. Unfortuantely, this
    will increase the time complexity.
    
    @param g the graph object
    @param src the start node number

    Sample #1:
    8 0
    0 0 0 0 0 0 0 0
    1 0 2 0 1 0 0 0
    0 0 0 0 3 10 0 0
    0 4 0 0 0 0 5 0
    0 0 0 2 0 2 8 4
    0 0 0 0 0 0 0 6
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 1 0
    {1|2}

    Answer #1:
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
    void dijkstra(Graph *g, const num_type &src);
    void printPathTo(const num_type &des, const std::vector<num_type> &prev_);
    void testDijkstra(Graph *g);

    /*
    Prim algorithm to find minimum spanning tree (undirected graph).
    A minimun spanning tree exists iff the undirected graph is connected.

    @param g the graph object

    Sample #1: (each edge is added twice to construct an undirected graph):
    8 0
    0 3 0 0 0 0 0 0
    3 0 2 4 1 10 0 0
    0 2 0 0 3 0 0 0
    0 4 0 0 2 0 5 0
    0 1 3 2 0 7 8 4
    0 10 0 0 7 0 0 6
    0 0 0 5 8 0 0 1
    0 0 0 0 4 6 1 0

    Answer #1:
    The edges of the minimum spanning tree:
    (0, 1), (1, 2), (4, 3), (1, 4), (7, 5), (7, 6), (4, 7),
    */
    void prim(Graph *g);
    void testPrim(Graph *g);

    /*
    Hungarian algorithm to find the maximum matching number
    in an unweighted bipartite graph.

    Precondition: the graph must be a bipartitle graph.

    @param leftN the left node number of the bipartite graph
    @param match if match[a] = b, then edge(a, b) is one of the
                 matching edge after running this algorithm.
                 if match[a] = -1, then node a is not matched.
    @param g the graph object
    @return the maximum matching number of the graph

    Sample #1: (ans: 4; edges: (0, 6), (1, 4), (2, 5), (3, 7))
    8 0
    0 0 0 0 1 0 1 0
    0 0 0 0 1 0 0 0
    0 0 0 0 1 1 0 0
    0 0 0 0 0 0 1 1
    1 1 1 0 0 0 0 0
    0 0 1 0 0 0 0 0
    1 0 0 1 0 0 0 0
    0 0 0 1 0 0 0 0
    4

    Sample #2: (ans: 3; edges: (0, 4), (1, 3), (2, 5))
    7 0
    0 0 0 0 1 0 0
    0 0 0 1 1 0 0
    0 0 0 0 1 1 1
    0 1 0 0 0 0 0
    1 1 1 0 0 0 0
    0 0 1 0 0 0 0
    0 0 1 0 0 0 0
    3

    Sample #3: (ans: 3; edges: (0, 6), (1, 4), (2, 5))
    8 0
    0 0 0 0 1 0 1 0
    0 0 0 0 1 0 0 0
    0 0 0 0 1 1 0 1
    0 0 0 0 0 0 1 0
    1 1 1 0 0 0 0 0
    0 0 1 0 0 0 0 0
    1 0 0 1 0 0 0 0
    0 0 1 0 0 0 0 0
    4
    */
    num_type hungarian(const num_type leftN, std::vector<num_type> &match, Graph *g);
    bool findPath1(const num_type src, std::vector<num_type> &match, Graph *g);
    void testHungarian(Graph *g);

    /*
    Kuhn¨CMunkres algorithm to find optimum(maximum sum of weight)
    matching in a weighted bipartite graph. (time complexity: O(n^4))
    Graph stored in an adjacent matrix.

    Precondition:
    1. the graph must be a bipartite graph.
    2. left nodes number <= right nodes number.

    @param leftN the left node number of the bipartite graph
    @param match if match[right] = left, then edge(left, right) is one of the
                 matching edge after running this algorithm. If match[right] = -1,
                 then right node is not matched.
    @param g the graph object 
    @param max if max is true, the result matching has maximum sum of weight
               else it has minimum sum of weight.
    @return the sum of weight in the optimum matching

    Sample #1:
    5 1
    0 0 9 5 7
    0 0 0 2 3
    9 0 0 0 0
    5 2 0 0 0
    7 3 0 0 0
    2

    Answer #1:
    Max matching costs: 12
    Max matching edges: (0, 2), (1, 4),
    Min matching costs: 8
    Min matching edges: (0, 3), (1, 4),

    Sample #2:
    10 1
    0 0 0 0 0 3 4 6 4 9
    0 0 0 0 0 6 4 5 3 8
    0 0 0 0 0 7 5 3 4 2
    0 0 0 0 0 6 3 2 2 5
    0 0 0 0 0 8 4 5 4 7
    3 6 7 6 8 0 0 0 0 0
    4 4 5 3 4 0 0 0 0 0
    6 5 3 2 5 0 0 0 0 0
    4 3 4 2 4 0 0 0 0 0
    9 8 2 5 7 0 0 0 0 0
    5

    Answer #2:
    Max matching costs: 29
    Max matching edges: (4, 5), (3, 6), (1, 7), (2, 8), (0, 9),
    Min matching costs: 14
    Min matching edges: (0, 5), (4, 6), (3, 7), (1, 8), (2, 9),

    Sample #3:
    10 1
    0 0 0 0 0 7 6 4 6 1
    0 0 0 0 0 4 6 5 7 2
    0 0 0 0 0 3 5 7 6 8
    0 0 0 0 0 4 7 8 8 5
    0 0 0 0 0 2 6 5 6 3
    7 4 3 4 2 0 0 0 0 0
    6 6 5 7 6 0 0 0 0 0
    4 5 7 8 5 0 0 0 0 0
    6 7 6 8 6 0 0 0 0 0
    1 2 8 5 3 0 0 0 0 0
    5

    Answer #3:
    Max matching costs: 36
    Max matching edges: (0, 5), (4, 6), (3, 7), (1, 8), (2, 9),
    Min matching costs: 21
    Min matching edges: (4, 5), (3, 6), (1, 7), (2, 8), (0, 9),
    */
    weight_type km(const num_type leftN, std::vector<num_type> &match,
                   Graph *g, const bool max = true);
    bool findPath2(const num_type src, std::vector<weight_type> &val,
                   std::vector<num_type> &match, Graph *g);
    void testKM(Graph *g);

    /*
    Edmond-Karp's algorithm to solve maximum flow problem.

    Default:
    src: node[0];
    des: node[node_num - 1];

    @param src the start node
    @param des the destination node
    @param g the graph object (need to use adjacent matrix)
    @return the maximum flow value

    Sample #1: (ans: 5)
    6 1
    0 3 2 0 0 0
    0 0 1 3 4 0
    0 0 0 0 2 0
    0 0 0 0 0 2
    0 0 0 0 0 3
    0 0 0 0 0 0

    Sample #2: (ans: 14)
    6 1
    0 15 4 0 0 0
    0 0 0 0 12 0
    0 0 0 10 0 0
    0 5 0 0 0 10
    0 0 3 0 0 7
    0 0 0 0 0 0
    */
    weight_type EdmondKarp(const num_type &src, const num_type &des, Graph *g);
    weight_type getIncreaseFromPath(const num_type &src, const num_type &des, Graph *g);
    void testEdmondKarp(Graph *g);

private:
    const num_type NOT_NODE;
    const weight_type INF;

    std::vector<num_type> indegree;
    std::vector<weight_type> dist;
    std::vector<num_type> prev;
    std::vector<bool> visit;

    /*
    Private constructor for singleton.
    */
    AlgorithmGraph();

    /*
    Create a graph object from command input.

    @return a pointer to the graph created
    */
    sl::Graph* createGraphFromInput();

    /*
    Initialize global arrays.
    */
    void initGlobals(const num_type &nodeNum);

    /*
    Check if all the nodes have been visited.
    */
    bool isAllVisit();

    /*
    Get an un-visited node that has the smallest dist value.
    */
    num_type getMinNotVisit(const Graph *g);

public:
    /*
    Test the function of the class.
    */
    static void test();
};

NS_END
