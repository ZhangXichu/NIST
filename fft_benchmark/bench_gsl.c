#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <complex.h>
#include "../include/externs.h"
#include "../include/utilities.h"
#include "../include/cephes.h"
#include "../include/erf.h"
#include "../include/tools.h"
#include "../include/stat_fncs.h"

#include "../include/gsl/gsl_errno.h"
#include "../include/gsl/gsl_fft_complex.h"
#include "../include/gsl/gsl_fft_real.h"
#include "../include/gsl/gsl_fft_halfcomplex.h"
#include "statistics.h"

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

void DiscreteFourierTransformGSL(int n){
    int i;
    double *in, *m;
    double p_value;
    gsl_fft_complex_wavetable * wavetable;
    gsl_fft_complex_workspace * workspace;

    in = (double *)calloc(2*n, sizeof(double));
    m = (double *)calloc(n/2, sizeof(double));

    for (i = 0; i < n; i++)
    {
      REAL(in,i) = 2 * epsilon[i] - 1;
      IMAG(in,i) = 0.0;
    }

    wavetable = gsl_fft_complex_wavetable_alloc(n);
    workspace = gsl_fft_complex_workspace_alloc(n);

    gsl_fft_complex_forward (in, 1, n, wavetable, workspace);

    #ifdef DEBUG
    printf("Check output of DFT: \n");
    for (i = 0; i < n; i++)
    {
      printf("%0.2f %0.2f ", REAL(in,i), IMAG(in,i));
    }
    #endif

    for (i = 0; i < n/2; i++){
        m[i] = sqrt(pow(REAL(in,i), 2) + pow(IMAG(in,i), 2));
    }

    #ifdef P_VALUE
      p_value = get_pvalue(n, m);
      printf("GSL p_value: %lf\n", p_value);
      pv2 = p_value;
    #endif

    gsl_fft_complex_wavetable_free(wavetable);
    gsl_fft_complex_workspace_free(workspace);

    free(m);
    free(in);
}

void DiscreteFourierTransformGSLr(int n){
    int i;
    double *in, *m;
    gsl_fft_real_wavetable * real;
    gsl_fft_real_workspace * work;

    in = (double *)calloc(n+1, sizeof(double));
    m = (double *)calloc(n/2+1, sizeof(double));
    work = gsl_fft_real_workspace_alloc (n);
    real = gsl_fft_real_wavetable_alloc (n);

    for (i = 0; i < n; i++)
    {
      in[i] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1;
    }

    gsl_fft_real_transform(in, 1, n, real, work);

#ifdef DEBUG
    for (i = 0; i < n; i++){
      printf("%0.2f ", in[i]);
    }
    printf("\n");
#endif
    m[0] = in[0];
    for ( i=0; i<n/2; i++ ) {
      m[i+1] = sqrt(pow(in[2*i+1], 2) + pow(in[2*i+2], 2)); 
#ifdef DEBUG
		printf("%0.2f + %0.2fi \n", in[2*i+1], in[2*i+2]);
#endif
	}

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("GSLr p_value: %lf\n", p_value);
#endif

    gsl_fft_real_wavetable_free (real);
    gsl_fft_real_workspace_free (work);

    free(in);
    free(m);
}