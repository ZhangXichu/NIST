#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <math.h>

#include "../include/config.h"

#ifdef P_VALUE
    #define K 1  /* repetation */
#else
    #define K 10
#endif
#define M (int)pow(10, 3)
#define NANO (int)pow(10, 9) /* convert from second to nano second */

typedef void dft(int);

void flushcache();
clock_t GetTickCount();
uint64_t GetCpuClocks();
uint64_t work(dft* f, int n);

#endif