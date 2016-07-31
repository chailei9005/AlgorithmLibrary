#pragma once

#include "Base.h"
#include <vector>

NS_BEGIN

/*
A disjoint set data structure.

For usage, see function test().
*/
class DisjointSet {
public:
    DisjointSet(const unsigned &size);
    ~DisjointSet();

    /*
    Union two numbers to the same set.
    (union by size)

    @param a the first number
    @param b the second number
    */
    void union_(const unsigned &a, const unsigned &b);

    /*
    Find the set that contains the number x.

    @return the set index
    */
    unsigned find(const unsigned &x);

    /*
    Overloading operator []
    */
    int& operator[](const unsigned &i);
    const int& operator[](const unsigned &i) const;

    /*
    Return the size of the content array.
    */
    unsigned size() const;

private:
    std::vector<int> arr;

public:
    /*
    Test the function of the class.

    Sample #1 (size = 10):
    2 0
    2 4
    3 5
    3 6
    5 9
    7 4
    4 6
    -1 -1
    */
    static void test();
};

NS_END
