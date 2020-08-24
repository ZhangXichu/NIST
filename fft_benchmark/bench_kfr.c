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

#include "../include/kfr_capi.h"
#include "statistics.h"

/* both complex and real transformation don't work for N with small factors */

void DiscreteFourierTransformKFR(int n){
    int i;
    uint8_t temp_size;
    size_t size; 
    kfr_c64 *in, *out; 
    double *m;

    /* allocate memory for input, output */
    in = (kfr_c64 *)kfr_allocate(n * sizeof(kfr_c64));
    out = (kfr_c64 *)kfr_allocate(n * sizeof(kfr_c64));
    m = (double *)calloc(n, sizeof(double));

    for (i = 0; i < n; i++){
        in[i] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1;
    }
    /* create plan */
    KFR_DFT_PLAN_F64* p64 = kfr_dft_create_plan_f64(n);

    temp_size = kfr_dft_get_temp_size_f64(p64);

    kfr_dft_execute_f64(p64, out, in, &temp_size);


#ifdef DEBUG
    printf("KFR Output of DFT: \n");
	for (i = 0; i < n; i++){
		printf("%0.2f %0.2f ", creal(out[i]), cimag(out[i]));
	}
	printf("\n");
#endif

    for (i = 0; i < n; i++){
        m[i] = sqrt(pow(creal(out[i]), 2) + pow(cimag(out[i]), 2));
    }

    /* statistics */
#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("KFR: p_value: %lf \n",p_value); /* use p-value to verify the result */
    pv2 = p_value;
#endif

    /* free */
    kfr_dft_delete_plan_f64(p64);
    free(m);
    kfr_deallocate(in);
    kfr_deallocate(out);
}

void DiscreteFourierTransformKFRr(int n){ /* real transformation */
    int i;
    uint8_t temp_size; 
    // kfr_c64 *in, *out; /* double precision */
    kfr_f64 *in;
    kfr_c64 *out;
    double *m;

    m = (double *)calloc(n/2 + 1, sizeof(double));
    /* allocate memory for input, output */
    in = (kfr_f64 *)kfr_allocate(n * sizeof(kfr_f64));
    out = (kfr_c64 *)kfr_allocate((n/2+1) * sizeof(kfr_c64));

    for (i = 0; i < n; i++){
        in[i] = 2 * ((double)(get_nth_block4(array, i) & 1)) - 1;
    }
    /* create plan */
    KFR_DFT_REAL_PLAN_F64* p64 = kfr_dft_real_create_plan_f64(n, Perm);

    // kfr_dft_real_dump_f64(p64); 

    temp_size = kfr_dft_real_get_temp_size_f64(p64);

    kfr_dft_real_execute_f64(p64, out, in, &temp_size);

#ifdef DEBUG
    printf("Output of DFT: \n");
	for (i = 0; i < n/2+1; i++){
		printf("%0.2f %0.2fi ", creal(out[i]), cimag(out[i]));
	}
	printf("\n");
#endif

    for (i = 0; i < n/2; i++){
        m[i] = sqrt(pow(creal(out[i]), 2) + pow(cimag(out[i]), 2));
    }
    m[0] = creal(out[0]);
    m[n/2] = cimag(out[0]);

#ifdef P_VALUE
    double p_value;
    p_value = get_pvalue(n, m);
    printf("KFR: p_value: %lf \n",p_value); /* use p-value to verify the result */
    pv2 = p_value;
#endif

    /* free */
    kfr_dft_real_delete_plan_f64(p64);
    free(m);
    kfr_deallocate(in);
    kfr_deallocate(out);
}