#ifndef MISC_OP_H
#define MISC_OP_H


int mcd(long a, long b, long *retval);

int mcm(long a, long b, long *retval);

int absolute_int(long *x);

int absolute(double *x);

int inverse_int(long x, double *retval);

int inverse(double x, int precision, double *retval);



#endif