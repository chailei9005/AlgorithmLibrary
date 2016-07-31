#pragma once

#include "Base.h"
#include <vector>
#include <string>

NS_BEGIN

/*
Puzzle node definition.
*/
class NPuzzleNode {
public:
    typedef std::vector<unsigned> value_type;

    /*
    The definition of the move direction.
    */
    enum Direction {
        LEFT,
        UP,
        RIGHT,
        DOWN
    };

    /*
    Initialize the node.

    @param val_ the node value
    @param row_ the row number
    @param col_ the column number
    */
    NPuzzleNode();
    NPuzzleNode(const value_type &val_,
                const unsigned row_,
                const unsigned col_);

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
    Get all adjacent nodes.

    @param adjNodes the result will be stored in this field
    */
    void getAllAdjNodes(std::vector<NPuzzleNode> &adjNodes) const;

    /*
    Get the adjacent node at the direction.

    @param direc the direction
    @return the adjacent node at the direction
    */
    NPuzzleNode getAdjNode(const Direction &direc) const;

    /*
    Check whether there is an adjacent node at the direction

    @param direc the direction
    */
    bool hasAdjNode(const Direction &direc) const;

    /*
    Move the value 0 at the given direction.

    @param direc the direction
    */
    void move(const Direction &direc);

    /*
    Get the row number of the index

    @param index the index
    @return the row number
    */
    unsigned getRow(const unsigned &index) const;

    /*
    Get the column number of the index

    @param index the index
    @return the column number
    */
    unsigned getCol(const unsigned &index) const;

    /*
    Get the string description of the node value.

    @return the string description
    */
    std::string toString() const;

private:
    value_type val;
    unsigned row;
    unsigned col;

    /*
    Check if the content of the node value
    is valid in the given dimension.

    @param val_ the node value
    @param row_ the row number
    @param col_ the column number
    @throw range_error if not valid
    */
    void checkValid(const value_type &val_,
                    const unsigned row_,
                    const unsigned col_) const;

    /*
    Get the index of value 0 after
    moving toward the direction.

    @param direc the direction
    @return the index value. If move failed, return -1
    */
    int getIndex(const Direction &direc) const;
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
