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

void DiscreteFourierTransformPocket(int n){ /* in-place transformation */
    int i;
    int status;
    double p_value;
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

    /* check the transformed result */
    // for (i = 0; i < 2 * n; i++){
    //     printf("%0.2f ", data[i]);
    // }
    // printf("\n");

    for (i = 0; i < n/2; i++){
        m[i] = sqrt(pow(data[2*i], 2) + pow(data[2*i+1], 2));
    }

    destroy_cfft_plan(p);

    p_value = get_pvalue(n, m);
    printf("PocketFFT: p_value: %lf \n", p_value);

    free(data);
    free(m);
}