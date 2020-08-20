#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/config.h"

#include "timer.h"

// On Linux use asm
uint64_t GetCpuClocks()
{
	unsigned int low, high;
	__asm__ __volatile__("rdtsc":"=a" (low), "=d" (high));
	return ((uint64_t)high << 32) | low;
}

clock_t GetTickCount() /* Btime */
{
	return clock();
}

uint64_t work(dft* f, int n){
    long time_e;
    struct timespec start, stop;
    int i;

#ifndef P_VALUE
    flushcache();
#endif

	if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      return EXIT_FAILURE;
    }

    for (i = 0; i < K; i++){
	    (*f)(n);
    }

	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      return EXIT_FAILURE;
    }

#ifndef P_VALUE
    printf("start: %lu seconds %lu nanoseconds \n", start.tv_sec, start.tv_nsec);
    printf("end: %lu seconds %lu nanoseconds \n", stop.tv_sec, stop.tv_nsec);
#endif

	time_e = (stop.tv_sec - start.tv_sec) * NANO + (stop.tv_nsec - start.tv_nsec);
	time_e = round(time_e / K); /* take the average */

    return time_e / M;  /*convert to microseconds*/
}

void flushcache()
{
	int i, j;
	const int size = 20 * 1024 * 1024;	// Allocate 20M. 
	char *c = (char *)malloc(size);
	if (c == NULL)
		exit(100);
	for (i = 0; i < 0xff; i++)
		for (j = 0; j < size; j++)
			c[j] = i * j;
	free(c);
}

