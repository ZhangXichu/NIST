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

#include "../include/fftw3.h"
#include "statistics.h"

/* multi-thread version */
void DiscreteFourierTransformFFTWm(int n){
    int i;
    int num_thread = 6; // 2, 4, 6
    double *m;
    fftw_complex *in, *out;    
    fftw_plan p;

    fftw_init_threads();

    in = (fftw_complex*)fftw_malloc(n * sizeof(fftw_complex));
    out = (fftw_complex*)fftw_malloc(n * sizeof(fftw_complex));
    m = (double*)calloc(n / 2 + 1, sizeof(double));

    fftw_plan_with_nthreads(num_thread);

    p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    
    for (i = 0; i<n; i++)
	{
		in[i][0] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1;
		in[i][1] = 0.0;
	}

    fftw_execute(p);

    fftw_cleanup_threads();

    m[0] = sqrt(out[0][0] * out[0][0]);	  

	for (i = 0; i<n / 2; i++)
		m[i + 1] = sqrt(pow(out[i + 1][0], 2) + pow(out[i + 1][1], 2));

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("Multithread FFTW p-value: %lf \n", p_value);
    pv2 = p_value;
#endif

#ifdef DEBUG
    printf("Check output of DFT \n");
    for (i = 0; i < n; i++){
        printf("%0.2f %0.2f ", out[i][0], out[i][1]);
    }
#endif

    fftw_destroy_plan(p);
    free(in);
    free(out);
    free(m);
}

void DiscreteFourierTransformFFTWmr(int n){
    int i;
    int num_thread = 6;
    double *m;
    double *in;
    fftw_complex *out;    
    fftw_plan p;

    fftw_init_threads();

    in = (double*)fftw_malloc(n * sizeof(double));
    out = (fftw_complex*)fftw_malloc((n / 2 + 1) * sizeof(fftw_complex));
    m = (double*)calloc(n / 2 + 1, sizeof(double));

    fftw_plan_with_nthreads(num_thread);

    p = fftw_plan_dft_r2c_1d(n, in, out, FFTW_ESTIMATE );
    
    for (i = 0; i<n; i++)
	{
		in[i] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1;
	}

    fftw_execute(p);

    fftw_cleanup_threads();

    m[0] = sqrt(out[0][0] * out[0][0]);	  

	for (i = 0; i<n / 2; i++)
		m[i + 1] = sqrt(pow(out[i + 1][0], 2) + pow(out[i + 1][1], 2));

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("Multithread FFTW real p-value: %lf \n", p_value);
    pv2 = p_value;
#endif

#ifdef DEBUG
    printf("Check output of DFT \n");
    for (i = 0; i < n; i++){
        printf("%0.2f %0.2f ", out[i][0], out[i][1]);
    }
#endif

    fftw_destroy_plan(p);
    free(in);
    free(out);
    free(m);
}

/* multi-thread version */
void DiscreteFourierTransformFFTW_i(int n){
    int i;
    double *m;
    fftw_complex *inOut;    
    fftw_plan p;


    inOut = (fftw_complex*)fftw_malloc(n * sizeof(fftw_complex));
    m = (double*)calloc(n / 2 + 1, sizeof(double));


    p = fftw_plan_dft_1d(n, inOut, inOut, FFTW_FORWARD, FFTW_ESTIMATE);
    
    for (i = 0; i<n; i++)
	{
		inOut[i][0] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1;
		inOut[i][1] = 0.0;
	}

    fftw_execute(p);

    m[0] = sqrt(inOut[0][0] * inOut[0][0]);	  

	for (i = 0; i<n / 2; i++)
		m[i + 1] = sqrt(pow(inOut[i + 1][0], 2) + pow(inOut[i + 1][1], 2));

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("FFTW in-place p-value: %lf \n", p_value);
    pv2 = p_value;
#endif

#ifdef DEBUG
    printf("Check output of DFT \n");
    for (i = 0; i < n; i++){
        printf("%0.2f %0.2f ", inOut[i][0], inOut[i][1]);
    }
#endif

    fftw_destroy_plan(p);
    free(inOut);
    free(m);
}

void DiscreteFourierTransformFFTWr_i(int n){ /* in-plece transform */
    int i;
    double *m;
    double *in;  
    fftw_plan p;

    in = (double*)fftw_malloc((2*n+4) * sizeof(double));
    m = (double*)calloc(n / 2 + 1, sizeof(double));

    fftw_complex *out = (fftw_complex *)in;  

    p = fftw_plan_dft_r2c_1d(n, in, out, FFTW_ESTIMATE );
    
    for (i = 0; i<n; i++)
	{
		in[i] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1;
	}

    fftw_execute(p);

    m[0] = sqrt(out[0][0] * out[0][0]);	  

	for (i = 0; i<n / 2; i++)
		m[i + 1] = sqrt(pow(out[i + 1][0], 2) + pow(out[i + 1][1], 2));

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("FFTW real in-place p-value: %lf \n", p_value);
    pv2 = p_value;
#endif

#ifdef DEBUG
    printf("Check output of DFT \n");
    for (i = 0; i < n; i++){
        printf("%0.2f %0.2f ", out[i][0], out[i][1]);
    }
#endif

    fftw_destroy_plan(p);
    free(in);
    free(m);
}