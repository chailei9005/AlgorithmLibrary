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
    @param a the permutation array
    @return the expansion value

    The inverse of cantor expansion.
    Mapping an integer to a permutation.

    @param n the size of the permutation
    @param a the result permutation array will
             be stored in this field.

    Precondition:
    1. permutation array element range: [0, n - 1].
    2. array a must has size n.

    Postcondition:
    1. the expansion value range: [0, n! - 1].

    Sample #1: (ans: 98884)
    9
    2 4 6 3 0 1 8 5 7

    Sample #2: (ans: 95)
    5
    3 4 2 1 0

    Sample #3: (ans: 7)
    4
    1 0 3 2
    */
    static unsigned long long cantorExpand(const int n, const int a[]);
    static void cantorExpandInverse(const int n, unsigned long long val, int a[]);
    static void testCantorExpand();

private:
};

NS_END
