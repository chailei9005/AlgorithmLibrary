#pragma once

#include "Base.h"
#include "BinaryHeap.h"
#include "HashTable.h"
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <unordered_set>
#include <memory>
#include <functional>

NS_BEGIN

/*
The definition of the move direction.
*/
enum Direction {
    NONE,
    LEFT,
    UP,
    RIGHT,
    DOWN
};

/*
N-Puzzle node definition.

The value of the node must be like this:
{1, 2, 3, 4, 5, 6, 7, 8, 0} (row = 3, col = 3)
Value 0 indicates the empty grid in the puzzle. 
*/
class NPuzzleNode {
public:
    ~NPuzzleNode();

    /*
    Initialize the node.

    @param val_ the node value
    @param row_ the row number
    @param col_ the column number
    */
    NPuzzleNode();
    NPuzzleNode(const std::vector<int> &val_, const int row_, const int col_);

    /*
    Get the node value.
    */
    const std::vector<int>& getVal() const;

    /*
    Get the adjacent node at the direction.
    Precondition: current node can move to the direction

    @param direc the direction
    @return the adjacent node pointer (make sure to delete
            because the pointer is allocated dynamically)
    */
    NPuzzleNode* getAdjNode(const Direction &direc) const;

    /*
    Move the empty grid toward the direction

    @param direc the direction
    */
    void move(const Direction &direc);

    /*
    Check whether the empty grid can move toward the direction

    @param direc the direction
    @return true if can move, false otherwise
    */
    bool canMove(const Direction &direc) const;

    /*
    Randomly rearrange the node value.
    (Make sure a solution exists)
    */
    void shuffle();

    /*
    Get the row number of the index

    @param i the index
    @return the row number (range: [0, row - 1])
    */
    int getRow(const int &i) const;

    /*
    Get the column number of the index

    @param i the index
    @return the column number (range: [0, col - 1])
    */
    int getCol(const int &i) const;

    /*
    Get the element numbers of the node value.
    */
    int getSize() const;

    /*
    Get the string description of the node value.

    @return the string description
    */
    std::string toString() const;

    /*
    Hash function for a node

    @return the hash value of the node
    */
    unsigned long long hash() const;

    /*
    Check if two nodes equal.
    */
    bool operator==(const NPuzzleNode &a) const;

    /*
    Compare two nodes by their f value.
    */
    bool operator<(const NPuzzleNode &a) const;
    bool operator>(const NPuzzleNode &a) const;
    bool operator<=(const NPuzzleNode &a) const;
    bool operator>=(const NPuzzleNode &a) const;

    /*
    Getters and setters for fields used in searching algorithm.
    */
    void setG(const int g_);
    void setH(const int h_);
    void setParent(NPuzzleNode* p);
    void setDirection(const Direction &d);
    int getG() const;
    int getH() const;
    int getF() const;
    NPuzzleNode* getParent() const;
    Direction getDirection() const;

private:
    std::vector<int> val;
    int emptyPos = -1;
    int row = 0;
    int col = 0;
    int g = 0;                      // The distance from the beginning node to the current node
    int h = 0;                      // The distance from the current node to the goal node (heuristic)
    NPuzzleNode* parent = nullptr;  // Parent node pointer
    Direction direc = NONE;         // Direction from parent node to this node

    /*
    Initialize the node value.

    @param val_ the node value
    @throw range_error if the node value is not valid
    */
    void init(const std::vector<int> &val_);
};

/*
N-Puzzle algorithm class.

For usage, see function test().
*/
class NPuzzle {
public:
    ~NPuzzle();

    /*
    Initialize.

    @param src_ the start node
    @param des_ the goal node
    */
    NPuzzle(const NPuzzleNode &src_, const NPuzzleNode &des_);

    /*
    Calculate solution from node src to node des.
    */
    void run();

    /*
    Get the solution path in direction form.
    */
    const std::list<Direction>& getDirectionPath() const;

    /*
    Get the solution path in node from.
    */
    const std::list<NPuzzleNode>& getNodePath() const;

    /*
    Get the total searched number.
    */
    int getSearchCount() const;

    /*
    Set the start node and end node
    */
    void setStartNode(const NPuzzleNode &n);
    void setEndNode(const NPuzzleNode &n);

private:
    /*
    Comparator for hash table
    */
    struct cmpHashTable {
        bool operator()(const NPuzzleNode *const &a,
                        const NPuzzleNode *const &b) const {
            return *a == *b;
        }
    };

    /*
    Hash table declaration.
    */
    typedef HashTable<NPuzzleNode*, cmpHashTable> hash_table;
    //typedef std::unordered_set<NPuzzleNode*,
    //                           std::function<unsigned long long(const NPuzzleNode *const &)>,
    //                           cmpHashTable> hash_table;  // STL version

    /*
    Comparator for binary heap
    */
    struct cmpBinaryHeap {
        bool operator()(const NPuzzleNode *const &a,
                        const NPuzzleNode *const &b) const {
            return *a <= *b;
            //return *a > *b;  // STD version
        }
    };

    /*
    Min-root binary heap declaration.
    */
    typedef BinaryHeap<NPuzzleNode*, cmpBinaryHeap> min_heap;
    //typedef std::priority_queue<NPuzzleNode*, std::vector<NPuzzleNode*>, cmpBinaryHeap> min_heap;  // STL version

    // Start node and end node
    NPuzzleNode src;
    NPuzzleNode des;

    min_heap openList;
    hash_table closeList;

    std::list<Direction> pathDirec;
    std::list<NPuzzleNode> pathNode;

    // Record dynamically allocated nodes
    std::list<NPuzzleNode*> alloc;

    unsigned searchedCnt = 0;

    /*
    Estimate the heuristic value
    from the node to the goal.

    @param n the current node
    @return heuristic value from node n to the goal.
    */
    int getEstimate(const NPuzzleNode *const n) const;

    /*
    Print the information of the current searching node.
    */
    void printSearchInfo(const NPuzzleNode *const cur) const;

    /*
    Construct the path from src to the node n.
    */
    void constructPath(const NPuzzleNode *n);

    /*
    Check if the node is visited.
    */
    bool isVisit(NPuzzleNode *const n) const;

    /*
    Free the resources using in searching.
    */
    void freeResources();

public:
    /*
    Test the function of the class.
    */
    static void test();
};

NS_END
