#ifndef STATISTICS_H
#define STSTISTICS_H

/**
 * @brief  function calculates p-value 
 * @note   
 * @param  n: input length
 * @param  *m: array of amplitudes after transformation
 * @retval double p-value
 */
double get_pvalue(int n, double *m);

#endif