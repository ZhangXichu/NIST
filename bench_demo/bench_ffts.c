#include "ffts.h"

void ffts(int n)
{
	int i, count;
	float *in, *out; 
	double *m;

	in = (float *)calloc(2 * n, sizeof(float));
    out = (float *)calloc(2 * n, sizeof(float));
	m = (double*)calloc(n / 2 + 1, sizeof(double));

	/* here loads data into input array */

	ffts_plan_t *p;

	p = ffts_init_1d(n, FFTS_FORWARD); 

	ffts_execute(p, in, out);

	ffts_free(p);

	// retrieve amplitudes from results of DFT
	for (i = 0; i < n / 2 + 1; i++){
		m[i] = sqrt(pow(out[2*i], 2) + pow(out[2*i+1], 2));
	}

	free(in);
	free(out);
	free(m);
}