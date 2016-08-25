#pragma once

#include "Base.h"
#include <ctime>

NS_BEGIN

/*
A class used for compute running time.
*/
class Timer {
public:
    Timer();

    /*
    Reset the beginning time to current time.
    */
    void reset();

    /*
    Return elapsed time from the beiginning time in milliseconds.
    */
    double elapse();

private:
    clock_t begin;
};

NS_END
