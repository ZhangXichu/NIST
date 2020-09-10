#include "gsl/gsl_errno.h"
#include "gsl/gsl_fft_complex.h"
#include "gsl/gsl_fft_real.h"
#include "gsl/gsl_fft_halfcomplex.h"

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

void gsl(int n){
    int i;
    double *in, *m;
    double p_value;
    gsl_fft_complex_wavetable * wavetable;
    gsl_fft_complex_workspace * workspace;

    in = (double *)calloc(2*n, sizeof(double));
    m = (double *)calloc(n/2, sizeof(double));

    /* here loads data into input */

    wavetable = gsl_fft_complex_wavetable_alloc(n);
    workspace = gsl_fft_complex_workspace_alloc(n);

    gsl_fft_complex_forward (in, 1, n, wavetable, workspace);

    // retrieve amplitudes from results of DFT
    for (i = 0; i < n/2; i++){
        m[i] = sqrt(pow(REAL(in,i), 2) + pow(IMAG(in,i), 2));
    }

    gsl_fft_complex_wavetable_free(wavetable);
    gsl_fft_complex_workspace_free(workspace);

    free(m);
    free(in);
}