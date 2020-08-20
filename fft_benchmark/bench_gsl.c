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

    // check output
    // for (i = 0; i < n; i++)
    // {
    //   printf("%0.2f %0.2f ", REAL(in,i), IMAG(in,i));
    // }

    gsl_fft_complex_wavetable_free(wavetable);
    gsl_fft_complex_workspace_free(workspace);

    for (i = 0; i < n/2; i++){
        m[i] = sqrt(pow(REAL(in,i), 2) + pow(IMAG(in,i), 2));
    }
    p_value = get_pvalue(n, m);
    printf("GSL p_value: %lf\n", p_value);

    free(m);
    free(in);
}