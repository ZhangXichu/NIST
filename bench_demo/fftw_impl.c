#include "fftw3.h"

void fftw3(int n)
{
	double *m = NULL;
	fftw_complex *in, *out;
	fftw_plan p;
	int		i;

	in = (fftw_complex*)fftw_malloc(n * 
	                    sizeof(fftw_complex));
	out = (fftw_complex*)fftw_malloc(n *
	                    sizeof(fftw_complex));
	m = (double*)calloc(n / 2 + 1, sizeof(double));

	p = fftw_plan_dft_1d(n, in, out, 
	                     FFTW_FORWARD, FFTW_ESTIMATE);   

	/* here loads data into input array */

	fftw_execute(p);

	// retrieve amplitudes from results of DFT
	m[0] = sqrt(out[0][0] * out[0][0]);	  
	for (i = 0; i<n / 2; i++)
		m[i + 1] = sqrt(pow(out[i + 1][0], 2) 
		           + pow(out[i + 1][1], 2));

	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
	free(m);
}
