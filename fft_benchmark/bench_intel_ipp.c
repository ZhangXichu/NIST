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

#include "../include/ipp/ipps.h"
#include "../include/ipp/ippcore.h"
#include "statistics.h"

void DiscreteFourierTransformIPP(int n){  /* out-of-place (no in-place impl for DFT) */

    int i;
    int sizeSpec, sizeInitBuf, sizeWorkBuf;
    IppStatus status;
    Ipp64fc *in;
    Ipp64fc *out;
    Ipp8u *initBuf, *workBuf;
    IppsDFTSpec_C_64fc *spec = 0; /* initialized by the init function */

    double* m;
    
    in = ippsMalloc_64fc(n);
    out = ippsMalloc_64fc(n); 

    /* set number of threads */
    // status = ippSetNumThreads(6);

    int algHint = ippAlgHintNone;

    // ippAlgHintNone, ippAlgHintFast, ippAlgHintAccurate
    status = ippsDFTGetSize_C_64fc(n, IPP_FFT_DIV_INV_BY_N, algHint, &sizeSpec, &sizeInitBuf, &sizeWorkBuf);

    /* check size */
    // printf("sizeSpec: %d\n", sizeSpec);
    // printf("sizeInitBuf: %d\n", sizeInitBuf);
    // printf("sizeWorkBuf: %d\n", sizeWorkBuf);

    spec = (IppsDFTSpec_C_64fc*)ippsMalloc_8u(sizeSpec);
    initBuf = ippsMalloc_8u(sizeInitBuf);
    workBuf = ippsMalloc_8u(sizeWorkBuf);

    m = (double *)calloc(n/2, sizeof(double));

    for (i = 0; i < n; i++){
        in[i].re = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1; // what's the difference of this to the original implementation of X[]?
        in[i].im = 0.0;
    }

    /* the DFT functions are alternative of the legacy ippGEN functions */
    /* initialization */
    // ippAlgHintNone, ippAlgHintFast, ippAlgHintAccurate
    status = ippsDFTInit_C_64fc(n, IPP_FFT_DIV_INV_BY_N, algHint, spec, initBuf); /* temp work buffer not used */

    /* transformation */
    status = ippsDFTFwd_CToC_64fc(in, out, spec, workBuf);

    for (i = 0; i < n/2; i++){
        m[i] = sqrt(pow(out[i].re,2)+pow(out[i].im,2));
    }
#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("intel IPP: p-value: %lf \n ",p_value);
    pv2 = p_value;
#endif

    if (initBuf) ippsFree(initBuf);
    if (workBuf) ippsFree(workBuf);
    if (spec) ippsFree(spec);

    ippsFree(in);
    ippsFree(out);

    free(m);
}


void DiscreteFourierTransformIPPr(int n){  /* out-of-place */

    int i;
    int sizeSpec=0, sizeInitBuf=0, sizeWorkBuf=0;
    IppStatus status;
    Ipp64f *in;
    Ipp64f *out;
    Ipp8u *initBuf, *workBuf;
    IppsDFTSpec_R_64f* spec = NULL; /* initialized by the init function */

    double* m;

    in = ippsMalloc_64f(n);
    out = ippsMalloc_64f(n + 2);  

    status = ippsDFTGetSize_R_64f(n, IPP_FFT_DIV_INV_BY_N, ippAlgHintAccurate, &sizeSpec, &sizeInitBuf, &sizeWorkBuf);

    spec = (IppsDFTSpec_R_64f *)ippsMalloc_8u(sizeSpec);
    initBuf = ippsMalloc_8u(sizeInitBuf);
    workBuf = ippsMalloc_8u(sizeWorkBuf);

    m = (double *)calloc(n/2 + 1, sizeof(double));

    for (i = 0; i < n; i++){
        in[i] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1; 
    }

    /* initialization */
    status = ippsDFTInit_R_64f(n, IPP_FFT_DIV_INV_BY_N, ippAlgHintAccurate, spec, initBuf); /* temp work buffer not used */

    /* set number of threads */
    // int numThreads;
    // status = ippSetNumThreads(6);
    // status = ippGetNumThreads(&numThreads);

    /* transformation */
    status = ippsDFTFwd_RToPerm_64f(in, out, spec, workBuf);

    m[0] = out[0];
    if (n % 2 == 0) {
        for ( i=0; i < n/2 - 1; i++ ) {
            m[i+1] = sqrt(pow(out[2*i+2], 2) + pow(out[2*i+3], 2));
#ifdef DEBUG
		printf("%0.2f + %0.2fi \n", out[2*i+2], out[2*i+3]);
#endif
        }
        m[n/2] = out[1];  /* Im X[0] and Im X[N/2] are 0 */
    } else {
        for ( i=0; i < n/2; i++ ) {
            m[i+1] = sqrt(pow(out[2*i+1], 2) + pow(out[2*i+2], 2));
#ifdef DEBUG
		printf("%0.2f + %0.2fi \n", out[2*i+1], out[2*i+2]);
#endif
        }
	}

#ifdef DEBUG
    printf("IPP: The transformed results \n");
    for (i = 0; i < n + 1; i++){
        printf("%0.2f ", out[i]);
    }
    printf("\n");
#endif

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("intel IPP real: p-value: %lf \n ",p_value);
    pv2 = p_value;
#endif

    /* free */
    if (initBuf) ippsFree(initBuf);
    if (workBuf) ippsFree(workBuf);
    if (spec) ippsFree(spec);

    ippsFree(in);
    ippsFree(out);

    free(m);
}