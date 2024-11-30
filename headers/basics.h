#ifndef BASICS_H
#define BASICS_H

int add(double a, double b, int precision, double *retval);

int subs(double a, double b, int precision, double *retval);

int times(double a, double b, int presicion, double *retval);

int divide(double n, double d, int precision, double *retval);

int power(double base, double n, int precision, double *retval);

int root(double base, int index, int precision, double *retval); 

#define DEFAULT_PRECISION   20


#endif