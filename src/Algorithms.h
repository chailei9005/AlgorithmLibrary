#pragma once

namespace sl {

/*
Contains some useful algorithms.

For usage, see function test().
*/
class Algorithms {
public:
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
    Binary search
    1. Standard
    2. Find first appear position
    3. Find last appear position
    
    Precondition: array must be ordered.

    @param a the array to find
    @param n the size of the array
    @param x the element to find
    @return the position of x in array a.
            If x doesn't exist, return -1
    */
    static int binarySearch(const int a[], const int n, const int x);
    static void testBinarySearch();

    /*
    Test the function of the class.
    */
    static void test();

private:

};

}
