#pragma once

#include "Base.h"
#include <vector>

NS_BEGIN

/*
Contain algorithms for generating random numbers.
This is a singleton.

Randomize equation: X(i+1) = A*X(i) mod M
A = 48271
M = 2147483647 (2^31-1)

To avoid overflow in multiplication, use X(i+1) = A*(X(i) mod Q) - R*FLOOR(X(i)/Q) + M*e(X(i))
Q = FLOOR(M/A) = 44488
R = M mod A = 3399
e(X(i)) =
0, when A*(X(i) mod Q) - R*FLOOR(X(i)/Q) >= 0
1, when A*(X(i) mod Q) - R*FLOOR(X(i)/Q) < 0

Note: INT_MAX >= 2^31 - 1 is necessary to ensure the program to run correctly
*/
class Random {
public:
    typedef long long value_type;

    ~Random();

    /*
    Forbid copy
    */
    Random(const Random &m) = delete;
    Random& operator=(const Random &m) = delete;

    /*
    Return the only instance
    */
    static Random* getInstance();

    /*
    Return a random number between 0 and 1 (exclude 0 and 1)
    */
    double rand();

    /*
    Return a random double number in (min, max)
    */
    double randDouble(const double min, const double max);

    /*
    Return a random integer number in [min, max]
    */
    unsigned long long randInt(const unsigned long long min,
                                      const unsigned long long max);

    /*
    Return a random integer number in [min, max] using library methods.
    */
    unsigned randLib(const unsigned min, const unsigned max);
    
    /*
    Set the seed value.
    */
    void setSeed(value_type seed_);

    /*
    Randomly rearrange the elements in an array.

    @param arr the array to rearrange
    */
    template <typename T>
    void randomChange(std::vector<T> &arr) {
        for (unsigned i = 1; i < arr.size(); ++i) {
            unsigned pos = randLib(0, i);
            T tmp = arr[i];
            arr[i] = arr[pos];
            arr[pos] = tmp;
        }
    }

private:
    value_type seed;
    const value_type A;
    const value_type M;
    const value_type Q;
    const value_type R;

    /*
    Private constructor for singleton.
    */
    Random();

public:
    /*
    Test the function of the class.
    */
    static void test();
};

NS_END
