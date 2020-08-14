#ifndef TIMER_H
#define TIMER_H

#include <time.h>

typedef void dft(int);

void flushcache();
clock_t GetTickCount();
clock_t work(dft* f, int n);

#endif