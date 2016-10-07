#pragma once

#include "Base.h"
#include <vector>
#include <string>

NS_BEGIN

/*
N-Queen node definition.

The value of the node must be like this(8 queens):
{0, 2, 2, 3, 4, 5, 6, -1}
array[1] = 2 means that a queen is at (row 1, column 2)
array[7] = -1 means that no queen has been placed at row 7
*/
class NQueenNode {
public:
    ~NQueenNode();

    /*
    Initialize the node.

    @param val_ the node value
    */
    NQueenNode();
    NQueenNode(const std::vector<int> &val_);

    /*
    Return the amount of conflict queens.
    */
    unsigned conflictCount() const;

    /*
    Test if the queens in two rows collide with each other.
    */
    bool hasConflict(const int row1, const int row2) const;

    /*
    Return a neightbor of current node having minimnum conflict amount.
    */
    NQueenNode getMinConflictNeighbor() const;

    /*
    Return the string presentation of the node value.
    */
    std::string toString() const;

    /*
    Return a pretty presentation of the node.
    */
    std::string toPrettyString() const;

    /*
    Operator [] to visit node value.
    */
    int& operator[](const int i);
    const int& operator[](const int i) const;

    /*
    Return the size.
    */
    int getSize() const;

private:
    std::vector<int> val;
    int size;

    /*
    Check if the node value is valid

    @param val_ the node value to be checked
    @throw std::range_error if the node value is invalid
    */
    void checkValid(const std::vector<int> &val_) const;
};

/*
N-Queen algorithm class.

For usage, see function test().
*/
class NQueen {
public:
    /*
    Solve the N-Queen problem using enumeration alogrithm.

    @param n the amount of queens
    @param res the solutions will be stored in this field
    */
    static void solveWithEnumeration(const int n, std::vector<NQueenNode> &res);

    /*
    Solve the N-Queen problem using hill climbing algorithm.

    @param n the amount of queens
    @return the solution node
    */
    static NQueenNode solveWithHillClimb(const int n);

private:

    /*
    Enumerate all possibilities and find solution.

    @param node the current processing node
    @param row the current processing row
    @param res the solutions will be stored in this field
    */
    static void enumerate(NQueenNode &node, const int row, std::vector<NQueenNode> &res);

public:
    /*
    Test the function of the class.
    */
    static void test();
};

NS_END
