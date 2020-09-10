#include "pocketfft.h"

void pocketfft(int n){ 
    int i;
    int status;
    double *data;
    double *m;
    
    cfft_plan p;

    data = (double *)calloc(2 * n, sizeof(double));
    m = (double *)calloc(n/2, sizeof(double));

    p = make_cfft_plan(n);

    /* here loads data into input */

    status = cfft_forward(p, data, 1); 

    // retrieve amplitudes from results of DFT
    for (i = 0; i < n/2; i++){
        m[i] = sqrt(pow(data[2*i], 2) + pow(data[2*i+1], 2));
    }

    destroy_cfft_plan(p);
    free(data);
    free(m);
}
