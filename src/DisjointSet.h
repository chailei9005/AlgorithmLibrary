#pragma once

#include <vector>

namespace sl {

class DisjointSet {
public:
    DisjointSet(const unsigned &size);
    ~DisjointSet();

    /*
    Union two numbers

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

    /*
    Test program.

    Sample #1 (size = 9):
    5 6
    7 8
    6 8
    5 7
    2 3
    3 7
    8 4
    -1 -1
    */
    static void test();

private:
    std::vector<int> arr;
};

}
