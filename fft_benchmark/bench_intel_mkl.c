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

#include "../include/mkl_dfti.h" /* the dynamic libraries need to be preloaded by setting the environment variable LD_PRELOAD */
#include "statistics.h"

typedef double _Complex mkl_cpx64; /* use double precision */
typedef double mkl_r64;

void DiscreteFourierTransformMKL(int n){ /* out-of-place */
    int i;
    mkl_cpx64 *in;
    mkl_cpx64 *out;
    MKL_LONG status;
    double *m;

    if (((in = (mkl_cpx64 *)calloc(n, sizeof(mkl_cpx64))) == NULL) ||
		((out = (mkl_cpx64 *)calloc(n, sizeof(mkl_cpx64))) == NULL) ||
		((m = (double*)calloc(n, sizeof(double))) == NULL)) {
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
        in[i] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1;
    }

    DFTI_DESCRIPTOR_HANDLE desc_handle = NULL;

    status = DftiCreateDescriptor(&desc_handle, DFTI_DOUBLE, DFTI_COMPLEX, 1, n);
    status = DftiSetValue(desc_handle, DFTI_PLACEMENT, DFTI_NOT_INPLACE);
#ifdef AVOID
    status = DftiSetValue(desc_handle, DFTI_WORKSPACE, DFTI_AVOID);
#endif
    status = DftiCommitDescriptor(desc_handle);
    status = DftiComputeForward(desc_handle, in, out);
    status = DftiFreeDescriptor(&desc_handle);

#ifdef DEBUG
    printf("Output of DFT \n");
    for (i = 0; i < n; i++){
        printf("%0.2f %0.2fi", creal(out[i]), cimag(out[i]));
    }
    printf("\n");
#endif

    for (i = 0; i < n; i++){
        m[i] = sqrt(pow(creal(out[i]), 2) + pow(cimag(out[i]), 2));
    }

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("MKL: n: %d, p_value: %lf \n", n, p_value); /* use p-value to verify the result */
    pv1 = p_value;
#endif

    free(in);
    free(out);
}


void DiscreteFourierTransformMKL_i(int n){ /* in-place */
    int i;
    mkl_cpx64 *inOut;
    MKL_LONG status;
    double *m;

    if (((inOut = (mkl_cpx64 *)calloc(n, sizeof(mkl_cpx64))) == NULL) ||
		((m = (double*)calloc(n, sizeof(double))) == NULL)) {
		printf("\t\tUnable to allocate working arrays for the DFT.\n");
		if (inOut != NULL)
			free(inOut);
		if (m != NULL)
			free(m);
		return;
	}

    for (i = 0; i < n; i++){
        inOut[i] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1;
    }

    DFTI_DESCRIPTOR_HANDLE desc_handle = NULL;

    status = DftiCreateDescriptor(&desc_handle, DFTI_DOUBLE, DFTI_COMPLEX, 1, n);
    status = DftiSetValue(desc_handle, DFTI_PLACEMENT, DFTI_INPLACE);
    status = DftiCommitDescriptor(desc_handle);
    status = DftiComputeForward(desc_handle, inOut);
    status = DftiFreeDescriptor(&desc_handle);

#ifdef DEBUG
    printf("Output of DFT \n");
    for (i = 0; i < n; i++){
        printf("%0.2f %0.2fi", creal(inOut[i]), cimag(inOut[i]));
    }
    printf("\n");
#endif

    for (i = 0; i < n; i++){
        m[i] = sqrt(pow(creal(inOut[i]), 2) + pow(cimag(inOut[i]), 2));
    }

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("MKL in-place: p_value: %lf \n",p_value); /* use p-value to verify the result */
    pv2 = p_value;
#endif

    free(inOut);
}


void DiscreteFourierTransformMKLr(int n){
    int i;
    // mkl_cpx64 *in;
    mkl_r64 *in;
    mkl_cpx64 *out;
    MKL_LONG status;
    double *m;

    if (((in = (double *)calloc(n, sizeof(double))) == NULL) ||
		((out = (mkl_cpx64 *)calloc(n/2+1, sizeof(mkl_cpx64))) == NULL) ||
		((m = (double*)calloc(n/2+1, sizeof(double))) == NULL)) {
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
        in[i] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1; 
    }

    DFTI_DESCRIPTOR_HANDLE desc_handle = NULL;

    status = DftiCreateDescriptor(&desc_handle, DFTI_DOUBLE, DFTI_REAL, 1, n);
    status = DftiSetValue(desc_handle, DFTI_PLACEMENT, DFTI_NOT_INPLACE);
#ifdef AVOID
    status = DftiSetValue(desc_handle, DFTI_WORKSPACE, DFTI_AVOID);
#endif
    status = DftiCommitDescriptor(desc_handle);
    status = DftiComputeForward(desc_handle, in, out);
    status = DftiFreeDescriptor(&desc_handle);

#ifdef DEBUG
    printf("Output of DFT \n");
    for (i = 0; i < n; i++){
        printf("%0.2f %0.2fi", creal(out[i]), cimag(out[i]));
    }
    printf("\n");
#endif

    for (i = 0; i < n/2+1; i++){
        m[i] = sqrt(pow(creal(out[i]), 2) + pow(cimag(out[i]), 2));
    }

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("MKL real: p_value: %lf \n",p_value); /* use p-value to verify the result */
    pv2 = p_value;
#endif

    free(in);
    free(out);
}


void DiscreteFourierTransformMKLr_i(int n){ /* in-place, result stored in CCS format */
    int i;
    mkl_r64 *inOut;
    MKL_LONG status;
    double *m;

    if (((inOut = (double *)calloc(n+2, sizeof(double))) == NULL) ||
		((m = (double*)calloc(n/2+1, sizeof(double))) == NULL)) {
		printf("\t\tUnable to allocate working arrays for the DFT.\n");
		if (inOut != NULL)
			free(inOut);
		if (m != NULL)
			free(m);
		return;
	}

    for (i = 0; i < n; i++){
        inOut[i] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1; 
    }

    DFTI_DESCRIPTOR_HANDLE desc_handle = NULL;

    status = DftiCreateDescriptor(&desc_handle, DFTI_DOUBLE, DFTI_REAL, 1, n);
    status = DftiSetValue(desc_handle, DFTI_PLACEMENT, DFTI_INPLACE);
    status = DftiCommitDescriptor(desc_handle);
    status = DftiComputeForward(desc_handle, inOut);
    status = DftiFreeDescriptor(&desc_handle);

#ifdef DEBUG
    printf("Output of DFT \n");
    for (i = 0; i < n/2+1; i++){
        printf("%0.2f %0.2fi", inOut[2*i], inOut[2*i+1]);
    }
    printf("\n");
#endif

    for (i = 0; i < n/2+1; i++){
        m[i] = sqrt(pow(inOut[2*i], 2) + pow(inOut[2*i+1], 2));
    }

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("MKL real: p_value: %lf \n",p_value); /* use p-value to verify the result */
    pv2 = p_value;
#endif

    free(inOut);
    free(m);
}