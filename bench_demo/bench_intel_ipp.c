#include "ipp/ipps.h"
#include "ipp/ippcore.h"

void ipp(int n){

    int i;
    double* m;
    int sizeSpec, sizeInitBuf, sizeWorkBuf;
    IppStatus status;
    Ipp64fc *in;
    Ipp64fc *out;
    Ipp8u *initBuf, *workBuf;
    IppsDFTSpec_C_64fc *spec = 0; 

    in = ippsMalloc_64fc(n);
    out = ippsMalloc_64fc(n); 

    status = ippsDFTGetSize_C_64fc(n, 
                                   IPP_FFT_DIV_INV_BY_N, 
                                   ippAlgHintAccurate, 
                                   &sizeSpec, &sizeInitBuf,
                                   &sizeWorkBuf);

    spec = (IppsDFTSpec_C_64fc*)ippsMalloc_8u(sizeSpec);
    initBuf = ippsMalloc_8u(sizeInitBuf);
    workBuf = ippsMalloc_8u(sizeWorkBuf);

    m = (double *)calloc(n/2, sizeof(double));

    /* here loads data into input array */

    status = ippsDFTInit_C_64fc(n, 
                                IPP_FFT_DIV_INV_BY_N, 
                                ippAlgHintAccurate, 
                                spec, 
                                initBuf); 

    status = ippsDFTFwd_CToC_64fc(in, out, spec, workBuf);

    for (i = 0; i < n/2; i++){
        m[i] = sqrt(pow(out[i].re,2)+pow(out[i].im,2));
    }

    // retrieve amplitudes from results of DFT
    if (initBuf) ippsFree(initBuf);
    if (workBuf) ippsFree(workBuf);
    if (spec) ippsFree(spec);

    ippsFree(in);
    ippsFree(out);

    free(m);
}