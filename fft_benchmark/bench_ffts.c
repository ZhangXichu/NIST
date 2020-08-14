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

void
DiscreteFourierTransformFFTS(int n)
{
	printf("DFT FFTS.\n");

	int i, count;
	double upperBound, p_value, percentile, N_l, N_o, d;
	float *in, *out;  /* single precision */
	double *m;

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
		in[2 * i] = 2 * epsilon[i] - 1; // Re
		in[2 * i + 1] = 0; // Im
	}

	/* input */
	// for (i = 0; i < 2 * n; i++){ // print out input
	// 	printf("%0.2f ", in[i]);
	// }
	// printf("\n");

	ffts_plan_t *p;

	p = ffts_init_1d(n, FFTS_FORWARD); // complex transformation

	ffts_execute(p, in, out);

	/* check the transformed result */
	// for (i = 0; i < n * 2; i++){
	// 	printf("%0.2f ", out[i]);
	// }
	// printf("\n");

	ffts_free(p);

	/* statistical data */
	// m[0] = sqrt(pow(out[0], 2));
	for (i = 0; i < n / 2 + 1; i++){
		m[i] = sqrt(pow(out[2*i], 2) + pow(out[2*i+1], 2));
	}
	upperBound = sqrt(2.995732274*n);
	count = 0;
	for (i = 0; i < n/2; i++){
		if (m[i] < upperBound)
			count++;
	}
	percentile = (double)count/(n/2)*100;
	N_l = (double) count;       /* number of peaks less than h = sqrt(3*n) */
	N_o = (double) 0.95*n/2.0;
	d = (N_l - N_o)/sqrt(n/4.0*0.95*0.05);
	p_value = erfc(fabs(d)/sqrt(2.0));

	// printf("p_value: %lf \n",p_value); /* use p-value to verify the result */

#ifdef VERIFY_RESULTS /* need to modify the testing code, since ffts supports only N = 2^k */
	R_.dft.p_value=p_value;
	R_.dft.percentile=percentile;
	R_.dft.N_l=N_l;
	R_.dft.N_o=N_o;
	R_.dft.d=d;
	if(DiscreteFourierTransform_v1 == DiscreteFourierTransformFFTS) R1 = R_;
	else R2 = R_;
#endif

}