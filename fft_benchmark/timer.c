#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#include "timer.h"

// On Linux use asm
// uint64_t
// GetCpuClocks()
// {
// 	unsigned int low, high;
// 	__asm__ __volatile__("rdtsc":"=a" (low), "=d" (high));
// 	return ((uint64_t)high << 32) | low;
// }

clock_t GetTickCount() /* Btime */
{
	return clock();
}

clock_t work(dft* f, int n){
    clock_t start, end, time;

	// flushcache();
	start = GetTickCount();
	(*f)(n);
	end = GetTickCount();

	time = end - start;

    return time;
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

