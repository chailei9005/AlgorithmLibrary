#include "Timer.h"

using sl::Timer;

Timer::Timer() {
    start = clock();
}

void Timer::reset() {
    start = clock();
}

double Timer::elapse() {
    clock_t endTime = clock();
    return 1000.0 * ((double)(endTime - start)) / ((double)CLOCKS_PER_SEC);
}
