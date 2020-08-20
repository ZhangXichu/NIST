#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../include/externs.h"
#include "../include/utilities.h"
#include "../include/cephes.h"
#include "../include/erf.h"
#include "../include/tools.h"
#include "../include/stat_fncs.h"

#include "../include/ffts.h"
#include "statistics.h"

void DiscreteFourierTransformFFTS(int n)
{
	int i, count;
	float *in, *out;  /* single precision */
	double *m;
	double p_value;

	if (((in = (float *)calloc(2 * n, sizeof(float))) == NULL) ||
		((out = (float *)calloc(2 * n, sizeof(float))) == NULL) ||
		((m = (double*)calloc(n / 2 + 1, sizeof(double))) == NULL)) {
		printf("\t\tUnable to allocate working arrays for the DFT.\n");
		if (in != NULL)
			free(in);
		if (out != NULL)
			free(out);
		if (m != NULL)
			free(m);
		return;
	}

	/* convert bit sequence to sequence of 1 and -1, and prepare the complex input data */
	for (i = 0; i < n; i++){
		in[2 * i] = 2*((double)(get_nth_block4(array,i) & 1))-1;; // Re
		in[2 * i + 1] = 0; // Im
	}

	ffts_plan_t *p;

	p = ffts_init_1d(n, FFTS_FORWARD); // complex transformation

	ffts_execute(p, in, out);

	/* check the transformed result */
	// for (i = 0; i < n * 2; i++){
	// 	printf("%0.2f ", out[i]);
	// }
	// printf("\n");

	ffts_free(p);

	/* calculate amplitude */
	for (i = 0; i < n / 2 + 1; i++){
		m[i] = sqrt(pow(out[2*i], 2) + pow(out[2*i+1], 2));
	}

	/* statistical data */
	p_value = get_pvalue(n, m);
	printf("DFT FFTS: p_value: %lf \n",p_value); /* use p-value to verify the result */

	free(in);
	free(out);
	free(m);
}

void DiscreteFourierTransformFFTSr(int n) /* real transformation */
{
	int i, count;
	float *in, *out;  /* single precision */
	double *m;
	double p_value;

	if (((in = (float *)calloc(n, sizeof(float))) == NULL) ||
		((out = (float *)calloc(n + 2, sizeof(float))) == NULL) ||
		((m = (double*)calloc(n / 2 + 1, sizeof(double))) == NULL)) {
		printf("\t\tUnable to allocate working arrays for the DFT.\n");
		if (in != NULL)
			free(in);
		if (out != NULL)
			free(out);
		if (m != NULL)
			free(m);
		return;
	}

	for (i = 0; i < n; i++){
		// in[2 * i] = 2 * epsilon[i] - 1; // Re
		// in[2 * i + 1] = 0; // Im
		in[i] = 2*epsilon[i] - 1;
	}

	ffts_plan_t *p;

	p = ffts_init_1d_real(n, FFTS_FORWARD); 

	ffts_execute(p, in, out);

	ffts_free(p);

	// for (i = 0; i < n + 2; i++){
	// 	printf("%0.2f ", out[i]);
	// }
	// printf("\n");

	/* calculate amplitude */
	for (i = 0; i < n / 2 + 1; i++){
		m[i] = sqrt(pow(out[2*i], 2) + pow(out[2*i+1], 2));
	}

	/* statistical data */
	p_value = get_pvalue(n, m);
	printf("DFT FFTS: p_value: %lf \n",p_value); /* use p-value to verify the result */

	free(in);
	free(out);
	free(m);
}
