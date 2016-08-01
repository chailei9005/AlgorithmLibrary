#pragma once

#include <ctime>

/*
A class used for compute running time.
*/
class Timer {
public:
    Timer();

    /*
    Reset the start time to current.
    */
    void reset();

    /*
    Get elapsed time in milliseconds.
    */
    double elapse();

private:
    clock_t start;
};

