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

void DiscreteFourierTransformKFR(int n){
    int i;
    uint8_t temp_size; 
    kfr_c64 *in, *out; /* double precision */
    double *m;
    double p_value;

    /* allocate memory for input, output */
    in = (kfr_c64 *)calloc(n, sizeof(kfr_c64));
    out = (kfr_c64 *)calloc(n, sizeof(kfr_c64) * 2);
    m = (double *)calloc(n, sizeof(double));

    for (i = 0; i < n; i++){
        in[i] = 2 * epsilon[i] - 1;
    }
    /* create plan */
    KFR_DFT_PLAN_F64* p64 = kfr_dft_create_plan_f64(n);

    temp_size = kfr_dft_get_temp_size_f64(p64);

    kfr_dft_execute_f64(p64, out, in, &temp_size);

    /* check the transformed result */
	// for (i = 0; i < n; i++){
	// 	printf("%0.2f %0.2fi", creal(out[i]), cimag(out[i]));
	// }
	// printf("\n");

    /* free */
    kfr_dft_delete_plan_f64(p64);

    for (i = 0; i < n; i++){
        m[i] = sqrt(pow(creal(out[i]), 2) + pow(cimag(out[i]), 2));
    }

    /* statistics */
    p_value = get_pvalue(n, m);
    // printf("KFR: p_value: %lf \n",p_value); /* use p-value to verify the result */

    free(m);
    free(in);
    free(out);
}

void DiscreteFourierTransformKFR2(int n){ /* real transformation */
    printf("KFR real.\n");

    int i;
    uint8_t temp_size; 
    kfr_c64 *in, *out; /* double precision */

    /* allocate memory for input, output */
    in = (kfr_c64 *)calloc(n, sizeof(kfr_c64));
    out = (kfr_c64 *)calloc(n, sizeof(kfr_c64));
    for (i = 0; i < n; i++){
        in[i] = 2 * epsilon[i] - 1;
    }
    /* create plan */
    KFR_DFT_REAL_PLAN_F64* p64 = kfr_dft_real_create_plan_f64(n * 2, Perm);

    // kfr_dft_real_dump_f64(p64); 

    temp_size = kfr_dft_real_get_temp_size_f64(p64);

    kfr_dft_real_execute_f64(p64, out, in, &temp_size);

    /* check the transformed result */
	for (i = 0; i < n; i++){
		printf("%0.2f %0.2fi ", creal(out[i]), cimag(out[i]));
	}
	printf("\n");

    /* free */
    kfr_dft_real_delete_plan_f64(p64);

    free(in);
    free(out);
}