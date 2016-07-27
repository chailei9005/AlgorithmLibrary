#pragma once

#include <ctime>
#include <cstdlib>

namespace sl {

/*
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
class RandomEngine {
public:
    typedef long long value_type;

    /*
    Return a random number between 0 and 1 (exclude 0 and 1)
    */
    static double random();

    /*
    Return a random double number
    between min and max (exclude min and max)
    */
    static double randDouble(const double min, const double max);

    /*
    Return a random integer number
    between min and max (include min and max)
    */
    static int randInt(const int min, const int max);

    /*
    Return a random integer number
    between min and max (include min and max) using library methods.
    */
    static unsigned randLib(const unsigned min, const unsigned max);
    
    /*
    Set the seed value.
    */
    static void setSeed(value_type seed_);

private:
    static value_type seed;
    static const value_type A;
    static const value_type M;
    static const value_type Q;
    static const value_type R;

public:
    /*
    Test the function of the class.
    */
    static void test();
};

}
