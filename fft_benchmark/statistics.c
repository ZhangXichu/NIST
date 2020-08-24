#include <stdio.h>
#include <math.h>

double get_pvalue(int n, double *m) {
    int i, count;
	double upperBound, p_value, N_l, N_o, d;

    upperBound = sqrt(2.995732274*n);
	count = 0;
    for (i = 0; i < n/2; i++){
		if (m[i] < upperBound)
			count++;
	}
	N_l = (double) count;       /* number of peaks less than h = sqrt(3*n) */
	N_o = (double) 0.95*n/2.0;
	d = (N_l - N_o)/sqrt(n/4.0*0.95*0.05);
	p_value = erfc(fabs(d)/sqrt(2.0));

	return p_value;
}