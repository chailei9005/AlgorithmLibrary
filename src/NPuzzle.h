#pragma once

#include "Base.h"
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <unordered_set>
#include <functional>
#include <memory>

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
Puzzle node definition.

The value of the node must be like this:
{9, 1, 2, 3, 4, 5, 6, 7, 8, 0} (row = 3, col = 3)
value 0 indicates the empty grid in the
puzzle the the first element stores the
index of the value 0. Other elements
indicate the actual puzzle grid.
*/
class NPuzzleNode {
public:
    typedef std::vector<int> value_type;
    typedef long long dist_type;
    typedef std::shared_ptr<NPuzzleNode> node_ptr;

    /*
    Initialize the node.

    @param val_ the node value
    @param row_ the row number
    @param col_ the column number
    */
    NPuzzleNode();
    NPuzzleNode(const value_type &val_,
                const int row_,
                const int col_);

    ~NPuzzleNode();

    /*
    Set the node value.
    */
    void setVal(const value_type &val_);

    /*
    Get the node value.
    */
    const value_type& getVal() const;

    /*
    Get the adjacent node at the direction

    @param direc the direction
    @return the adjacent node pointer. If no
            adjacent node at the direction,
            return nullptr.
    */
    node_ptr getAdjNode(const Direction &direc) const;

    /*
    Move the empty grid toward the direction
    Precondition: can move toward the direcion

    @param direc the direction
    */
    void move(const Direction &direc);

    /*
    Check whether the empty grid can move toward the direction

    @param direc the direction
    @return whether can move
    */
    bool canMove(const Direction &direc) const;

    /*
    Randomly rearrange the node value.
    (Make sure a solution exists)
    */
    void shuffle();

    /*
    Get the total row number of the node

    @return the total row number
    */
    int getRow() const;

    /*
    Get the row number of the index

    @param index the index
    @return the row number (range: 0 to (row - 1))
    */
    int getRow(const int &index) const;

    /*
    Get the total col number of the node

    @return the total col number
    */
    int getCol() const;

    /*
    Get the column number of the index

    @param index the index
    @return the column number (range: 0 to (col - 1))
    */
    int getCol(const int &index) const;

    /*
    Get the string description of the node value.

    @return the string description
    */
    std::string toString() const;

    /*
    Hash function for a node

    @param p the node to hash
    @return the hash value of the node
    */
    static unsigned hash(const node_ptr p);

    /*
    Check if two nodes equal.
    */
    bool operator==(const NPuzzleNode &a) const;

    /*
    Operators compared by f value.
    */
    bool operator<(const NPuzzleNode &a) const;
    bool operator>(const NPuzzleNode &a) const;
    bool operator<=(const NPuzzleNode &a) const;
    bool operator>=(const NPuzzleNode &a) const;

    /*
    Getters and setters for fields
    used in searching algorithms.
    */
    void setG(const dist_type g_);
    void setH(const dist_type h_);
    void setParent(const node_ptr p);
    void setDirection(const Direction &d);
    dist_type getG() const;
    dist_type getH() const;
    dist_type getF() const;
    node_ptr getParent() const;
    Direction getDirection() const;

private:
    value_type val;
    int row;
    int col;

    /*
    Fields used in searching alogrithm
    */
    dist_type g;       // The distance from beginning node to current node
    dist_type h;       // The distance from current node to goal node (heuristic)
    node_ptr parent;   // Parent node
    Direction direc;   // Direction from parent node to this node

    /*
    Check if the content of the node value
    is valid in the given dimension.

    @param val_ the node value
    @param row_ the row number
    @param col_ the column number
    @throw range_error if not valid
    */
    void checkValid(const value_type &val_,
                    const int row_,
                    const int col_) const;

    /*
    Get the index displacement at the direction

    @param direc the direction
    @return the index displacement
    */
    int getDisplacement(const Direction &direc) const;
};

/*
Contains algorithm to compute N-Puzzle problem.

For usage, see function test().
*/
class NPuzzle {
public:
    typedef NPuzzleNode::node_ptr node_ptr;

    /*
    A comparator used in min-root heap.
    */
    struct cmpMinHeap {
        bool operator()(const node_ptr a, const node_ptr b) const {
            return (*a) > (*b);
        }
    };

    /*
    A comparator used in set.
    */
    struct cmpSet {
        bool operator()(const node_ptr a, const node_ptr b) const {
            return (*a) == (*b);
        }
    };

    /*
    Hash table declaration.
    Constructor:
    The first param is the number of buckets in the hash table
    The second param is the hash function
    */
    typedef std::unordered_set<node_ptr, decltype(NPuzzleNode::hash)*, cmpSet> hash_table;

    /*
    Min-root heap declaration
    */
    typedef std::priority_queue<node_ptr, std::vector<node_ptr>, cmpMinHeap> min_heap;

    /*
    Initialize.

    @param src_ the start node
    @param des_ the goal node
    */
    NPuzzle(const node_ptr src_, const node_ptr des_);

    ~NPuzzle();

    /*
    Begin searching.
    */
    void run();

    /*
    Get the solution path.
    */
    const std::list<Direction>& getPath() const;

    /*
    Get the total searched number
    */
    int getSearchCount() const;

private:
    node_ptr src;
    node_ptr des;
    min_heap openList;
    hash_table closeList;
    std::list<Direction> path;

    /*
    Estimate the heuristic value
    from the node to the goal.

    @param n the current node
    @return heuristic value from node n to the goal.
    */
    NPuzzleNode::dist_type estimateH(const node_ptr n) const;

    /*
    Print the information of the current searching node.
    */
    void printSearchInfo(const node_ptr cur) const;

    /*
    Construct the path from src to des.
    */
    void constructPath();

    /*
    Calculate the manhatten distance
    from the curernt node to des node.

    @param n the current node
    @return the manhatten distance between two nodes
    */
    int getManhattenDist(const node_ptr n) const;

    /*
    Calculate the geometric distance
    from the curernt node to des node.

    @param n the current node
    @return the geometric distance between two nodes
    */
    int getGeometricDist(const node_ptr n) const;

public:
    /*
    Test the function of the class.
    */
    static void test();
};

NS_END
