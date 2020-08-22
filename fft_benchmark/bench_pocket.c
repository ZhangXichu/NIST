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

#include "../include/pocketfft.h"
#include "statistics.h"

#ifdef P_VALUE
	double pv1, pv2;
#endif

void DiscreteFourierTransformPocket(int n){ /* in-place transformation */
    int i;
    int status;
    double *data;
    double *m;
    
    cfft_plan p;

    data = (double *)calloc(2 * n, sizeof(double));
    m = (double *)calloc(n/2, sizeof(double));

    p = make_cfft_plan(n);

    for (i = 0; i < n; i++){
        data[2*i] = 2 * epsilon[i] - 1;
        data[2*i+1] = 0;
    }
    status = cfft_forward(p, data, 1); 

    for (i = 0; i < n/2; i++){
        m[i] = sqrt(pow(data[2*i], 2) + pow(data[2*i+1], 2));
    }

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("PocketFFT: p_value: %lf \n", p_value);
    pv2 = p_value;
#endif

    destroy_cfft_plan(p);

    free(data);
    free(m);
}

void DiscreteFourierTransformPocketr(int n){ /* in-place transformation */
    int i;
    int status;
    double p_value;
    double *data;
    double *m;
    
    rfft_plan p;

    data = (double *)calloc(n+1, sizeof(double));
    m = (double *)calloc(n/2+1, sizeof(double));

    p = make_rfft_plan(n);

    for (i = 0; i < n; i++){
        data[i] = 2 * epsilon[i] - 1;
    }
    status = rfft_forward(p, data, 1); 

    /* check the transformed result */
#ifdef DEBUG
    printf("Output of DFT: 'n");
    for (i = 0; i < n; i++){
        printf("%0.2f ", data[i]);
    }
    printf("\n");
#endif
#ifdef DEBUG
		printf("PocketFFT complex numbers: \n");
#endif
    m[0] = sqrt(data[0] * data[0]);
    for (i = 0; i < n/2; i++){
        m[i+1] = sqrt(pow(data[2*i+1], 2) + pow(data[2*i+2], 2));
#ifdef DEBUG
		printf("%0.2f + %0.2fi   \n", data[2*i+1], data[2*i+2]);
#endif
    }
#ifdef P_VALUE
    p_value = get_pvalue(n, m);
    printf("PocketFFTr: p_value: %lf \n", p_value);
#endif

    destroy_rfft_plan(p);

    free(data);
    free(m);
}