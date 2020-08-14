#include "../include/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "../include/externs.h"
#include "../include/cephes.h"
#include "../include/utilities.h"
#include "../include/tools.h"
#include "../include/stat_fncs.h"

#include "benchmark.h"
#include "timer.h"


void benchmark(int n, FILE *out_file){
	/* the original fft */
	// DiscreteFourierTransform_v1(n);

	benchmark_ffts(n, out_file);
}

void benchmark_ffts(int n, FILE *out_file){ /* total time of fft transformation */
	clock_t time;

	time = work(&DiscreteFourierTransform_v2, n);
	fprintf(out_file, "%d %jd\n", n, time);  /*format: [index] [speed]*/
	printf("Time elepsed: %jd\n", time);
}


// TODO: repeat and take average. refactor 
// TODO: test initialization and execution timer separately