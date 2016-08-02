#pragma once

#include "Base.h"
#include <vector>

NS_BEGIN

/*
Contains some useful algorithms.

For usage, see function test().
*/
class Algorithm {
public:
    /*
    Test the function of the class.
    */
    static void test();

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
    Calculate factorial.
    
    @param n the n value
    @return the factorial value
    */
    static unsigned long long factorial(unsigned n);
    static void testFactorial();

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
    Calculate the next permutation of the current sequence.

    @param a the array stores the sequence
    @param n the size of the array
    @return whether next permutation exists
    */
    static bool nextPermutation(int a[], const int n);
    static void testPermutation();

    /*
    Print the combinations(C(n, k)) of and array.

    @param a the array stores the sequecne
    @param n the size of the array
    @param k the k numbers to select
    */
    static void printCombinations(const int a[], const int n, const int k);
    static void testCombination();

    /*
    Cantor expansion.
    Mapping a permutation to an integer.

    @param n the size of the permutation
    @param arr the permutation array (element range: 0 to n - 1)
    @return the expansion value

    The inverse of cantor expansion.
    Mapping an integer to a permutation.

    @param n the size of the permutation
    @param val the expansion value
    @return the permutation array (element range: 0 to n - 1)
    */
    static unsigned long long cantorExpand(const int n, const std::vector<int> &p);
    static std::vector<int> cantorExpandInverse(const int n, const unsigned long long val);
    static void testCantorExpand();

private:
};

NS_END
