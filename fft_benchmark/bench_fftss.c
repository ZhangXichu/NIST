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

#include "../include/fftss/fftss.h"

#include "statistics.h"

#ifdef P_VALUE
	double pv1, pv2;
#endif

void DiscreteFourierTransformFFTSS(int n){ 
    int i;
    double *in, *out;
    double *m;
    fftss_plan p;

    in = fftss_malloc(2*n * sizeof(double));
    out = fftss_malloc(2*n * sizeof(double));
    m = (double *)calloc(n+2, sizeof(double));

    for (i = 0; i < n; i++) {
        in[2*i] = 2*((double)(get_nth_block4(array,i) & 1))-1;
        in[2*i+1] = 0.0;
    }

    p = fftss_plan_dft_1d(n, in, out, FFTSS_FORWARD, FFTSS_ESTIMATE);
    fftss_execute(p);

#ifdef DEBUG
    printf("FFTSS output of DFT: \n");
    for (i = 0; i < n + 1; i++){
        printf("%0.2f ", out[i]);
    }
#endif
    for (i = 0; i < n; i++){
        m[i] = sqrt(pow(out[2*i], 2) + pow(out[2*i+1], 2));
    }

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("PocketFFTr: p_value: %lf \n", p_value);
    pv2 = p_value;
#endif

    fftss_destroy_plan(p);
    fftss_free(in);
    fftss_free(out);
    free(m);
}