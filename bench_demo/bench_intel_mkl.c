#include "mkl_dfti.h" 

// type define for readability
typedef double _Complex mkl_cpx64; 
typedef double mkl_r64;

void mkl(int n){
    int i;
    mkl_cpx64 *in;
    mkl_cpx64 *out;
    MKL_LONG status;
    double *m;

    in = (mkl_cpx64 *)calloc(n, sizeof(mkl_cpx64));
	out = (mkl_cpx64 *)calloc(n, sizeof(mkl_cpx64));
    m = (double*)calloc(n, sizeof(double));

    /* here loads data into input array */

    DFTI_DESCRIPTOR_HANDLE desc_handle = NULL;

    status = DftiCreateDescriptor(&desc_handle, 
                                  DFTI_DOUBLE, 
                                  DFTI_COMPLEX, 
                                  1, n);
    status = DftiSetValue(desc_handle, 
                          DFTI_PLACEMENT, 
                          DFTI_NOT_INPLACE);
    status = DftiCommitDescriptor(desc_handle);
    status = DftiComputeForward(desc_handle, in, out);
    status = DftiFreeDescriptor(&desc_handle);

    // retrieve amplitudes from results of DFT
    for (i = 0; i < n; i++){
        m[i] = sqrt(pow(creal(out[i]), 2) 
               + pow(cimag(out[i]), 2));
    }

    free(in);
    free(out);
}