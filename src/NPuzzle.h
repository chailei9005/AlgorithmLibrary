#pragma once

#include "Base.h"
#include <vector>
#include <string>

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

The value of the node must like this:
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
    Get the row number of the index

    @param index the index
    @return the row number (range: 0 to (row - 1))
    */
    int getRow(const int &index) const;

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
    Check if two nodes equal.
    */
    friend bool operator==(const NPuzzleNode &a, const NPuzzleNode &b);

    /*
    Getters and setters for fields
    used in searching algorithms.
    */
    void setG(const dist_type g_);
    void setH(const dist_type h_);
    void setParent(const Direction &d);
    dist_type getG() const;
    dist_type getH() const;
    dist_type getF() const;
    Direction getParent() const;

private:
    value_type val;
    int row;
    int col;

    /*
    Fields used in searching alogrithm
    */
    dist_type g;       // The distance from beginning node to current node
    dist_type h;       // The distance from current node to goal node (heuristic)
    Direction parent;  // Parent node direction toward current node

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
    NPuzzle();
    ~NPuzzle();

    
private:

public:
    /*
    Test the function of the class.
    */
    static void test();
};

NS_END
