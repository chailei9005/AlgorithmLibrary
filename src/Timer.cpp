#include "Timer.h"

using sl::Timer;

Timer::Timer() {
    reset();
}

void Timer::reset() {
    begin = clock();
}

double Timer::elapse() {
    return 1000.0 * ((clock() - begin) / (double)CLOCKS_PER_SEC);
}
