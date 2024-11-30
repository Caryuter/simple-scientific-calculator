#include "../headers/basics_int.h"
#include "../headers/basics.h"
#include "../headers/misc_op.h"
#include "../headers/errors.h"

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>


//Calculates de maximum common divisor between two integers
//Result is set to retval pointer
int mcd(long a, long b, long *retval){
    if(retval == NULL) return ERR_NULL_PTR;
    int err;
    if((err = absolute_int(&a)) != ERR_OK) return err;
    if((err = absolute_int(&b)) != ERR_OK) return err;

    //Use Euclides Algorithm

    while (b != 0) {
        long temp = b;
        b = a % b;    
        a = temp;
    }
    *retval = a;
    return ERR_OK;

}

//Calculates de minimun common multiple between two integers
//Result is set to retval pointer
int mcm(long a, long b, long *retval){
    if(retval == NULL) return ERR_NULL_PTR;
    long gcd;
    int err;
    if ((err = mcd(a, b, &gcd)) != ERR_OK) return err;

    long prod;
    if((err = absolute_int(&a)) != ERR_OK) return err;
    if((err = absolute_int(&b)) != ERR_OK) return err;
    if ((err = times_int(a, b, &prod)) != ERR_OK) return err;

    double retval_f;
    err = divide_int(prod, gcd, &retval_f); 

    *retval = retval_f;
    return err;
}


//Calculates the absolute of an integer (i.e |-2| = 2)
//Result is set to retval pointer
int absolute_int(long *x){
    if(x == NULL) return ERR_NULL_PTR;
	int y = (*x >> 31);
    *x = (*x ^ y) - y;
    return ERR_OK;
}

//Calculates the absolute of a decimal number (i.e |-2.3| = 2.3)
//Result is set to retval pointer
int absolute(double *x){
    if(x == NULL) return ERR_NULL_PTR;
	*x = (*x < 0) ? -(*x) : *x;
    return ERR_OK;
}

//Calculates the inverse of an integer.
//Has same effect as dividing 1/number. (i.e inverse(9) = 1/9)
//Result is set to retval pointer
int inverse_int(long x, double *retval) {
    if (retval == NULL) return ERR_NULL_PTR; 
    *retval = 1.0;
    return divide_int(1, x, retval);                   
}

//Calculates the inverse of a decimal number.
//Has same effect as dividing 1/number. (i.e inverse(9.1) = 1/9.1)
//Result is set to retval pointer
int inverse(double x, int precision, double *retval){
    if(retval == NULL) return ERR_NULL_PTR;
    if (x == 0) return ERR_DIV_BY_ZERO;
    *retval = 1.0;
    return divide(1, x, 0, retval);
}