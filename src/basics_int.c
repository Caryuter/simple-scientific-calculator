#include "../headers/misc_op.h"
#include "../headers/basics.h"
#include"../headers/basics_int.h"
#include "../headers/errors.h"
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//Takes two integer numbers and sums them. 
//Result is set to 'retval' pointer
int add_int(long a, long b, long *retval){
	if(retval == NULL) return ERR_NULL_PTR;
    int err;

    //Sum nothing
    if((a == 0) != (b == 0)){
        *retval = a != 0 ? a : b;
        return ERR_OK;
    }

    //If a number is negative and the other positive, exec substraction rather than sum
    if((a ^ b) < 0){
        long substractor;
        if (a < b){
            substractor = a;
            err = absolute_int(&substractor);
            if(err != ERR_OK) return err;
            return subs_int(b, substractor, retval);
        } else {
            substractor = b;
            err = absolute_int(&substractor);
            if(err != ERR_OK) return err;
            return subs_int(a, substractor, retval);
        }
    }

    int neg = (a < 0 && b < 0);
    err = absolute_int(&a);
    if(err != ERR_OK) return err;
    err = absolute_int(&b);
    if(err != ERR_OK) return err;


    unsigned long carry;

	while (b != 0){
       
		carry = (unsigned long)(a & b); // This finds carry for sum 
		a ^= b;         // Sum raw without carry value
		b = carry << 1;    // Desplaza el acarreo a la izquierda
        if (a > LONG_MAX || a < LONG_MIN) {
            return ERR_OVERFLOW;
        }   
	}

	*retval = (neg) ? -a : a;
	return ERR_OK;
}

//Takes two integer numbers and ssubstract 'b' to 'a' 
//Result is set to 'retval' pointer
int subs_int(long a, long b, long *retval){
    if(retval == NULL) return ERR_NULL_PTR;
    int err;

    //subs nothing
    if((a == 0) != (b == 0)){
        *retval = a != 0 ? a : -b;
        return ERR_OK;
    }


    //If both signs are different execute sum in place of subs
    if((a ^ b) < 0){
        long x;
        if(a > b){
            x = b;
            absolute_int(&x);
            return add_int(a,x,retval);
        }else {
            x = a;
            absolute_int(&x);
            return add_int(-x,-b,retval);
        }
    }
    //Check if substraction should ret negative value
    int neg;
    if(a < 0 && b < 0){
        long new_a = a;
        long new_b = b;
        absolute_int(&new_a);
        absolute_int(&new_b);
        neg = new_a > new_b;
    } else {
        neg = a < b;
    }

    err = absolute_int(&a);
    if(err != ERR_OK) return err;
    err = absolute_int(&b);
    if(err != ERR_OK) return err;

    //Swap values for 'a' to always be higher than 'b'
    if(a < b){
        long tmp = a;
        a = b;
        b = tmp;
    }

    unsigned long carry;

	while (b != 0){

        long borrow = (~a) & b;
        a ^= b;
        b = borrow << 1;
        if (a > LONG_MAX || a < LONG_MIN) {
            return ERR_OVERFLOW;
        }  
    }
    *retval = (neg) ? -a : a;
    return ERR_OK;
}


//Takes two integer numbers and multiplies them. 
//Result is set to 'retval' pointer
int times_int(long a, long b, long *retval){
	if(retval == NULL) return ERR_NULL_PTR;
    *retval = 0;

	if (a == 0 || b == 0) {
        *retval = 0;
        return ERR_OK;
    }
	int err;
	int is_negative = (a < 0) ^ (b < 0);
	if((err = absolute_int(&a)) != ERR_OK) return err;
	if((err = absolute_int(&b)) != ERR_OK) return err;

	while (b != 0) {
		if (b & 1) {
			if((err = add_int(*retval, a, retval)) != ERR_OK) return err;
		}
        if (*retval > LONG_MAX || *retval < LONG_MIN) return ERR_OVERFLOW;

		b >>= 1;
		a <<= 1;
	}

	if(is_negative) *retval = -(*retval);

    if (*retval > LONG_MAX || *retval < LONG_MIN) return ERR_OVERFLOW;
	return ERR_OK;
}

//Takes two integer numbers and divides them.
//Result is set to 'retval' pointer
int divide_int(long n, long d, double *retval){
    int err;
	if (d == 0)  return ERR_DIV_BY_ZERO;

    int negative = ((n < 0) ^ (d < 0)) ? 1 : 0;

    if((err = absolute_int(&n)) != ERR_OK) return err;
	if((err = absolute_int(&d)) != ERR_OK) return err;
    unsigned long ua = (unsigned long) n;
    unsigned long ub = (unsigned long) d;

    unsigned long quotient = 0;
    unsigned long remainder = 0;

    for (int i = 31; i >= 0; --i) {
        remainder = (remainder << 1) | ((ua >> i) & 1);
        if (remainder >= ub) {
            remainder -= ub;
            quotient |= (1UL << i); 
        }
    }

    double fraction = 0.0;
    double fraction_bit = 0.5;
    remainder <<= 1;

    for (int i = 0; i < 52 && remainder != 0; ++i) { 
        if (remainder >= ub) {
            fraction += fraction_bit;
            remainder -= ub;
        }
        remainder <<= 1;
        fraction_bit /= 2.0;
    }

    double result = (double)quotient + fraction;

    *retval = negative ? -result : result;

    return ERR_OK;

}

//Takes two integer numbers and raise base to the powerer of n. 
//Result is set to 'retval' pointer
int power_int(long base, long n, double *retval){
	if (retval == NULL) return ERR_NULL_PTR;

    long sad = n;
    if (n == 0) {
        *retval = 1; 
        return ERR_OK;
    }
	if (base == 0) {
        *retval = 0.0;
        return ERR_OK;
    }

    int neg_exp = 0;
    int neg_val= 0;
    if((base < 0) && (base % 2 == 0)) {
        neg_val = 1;
        absolute_int(&base);
    }
    if (n < 0) {
        neg_exp = 1;   
        absolute_int(&n);
    }

    long result = 1;

    for(;n > 0; subs_int(n, 1, &n)){
        times_int(result, base, &result);
    }

    if(neg_val) result = -result;
    if (neg_exp) {
        return inverse_int(result, retval);
    }

    *retval = (double)result;
    return ERR_OK;

}

//Takes two integer numbers and applies 'n'-index sqroot of 'base' them. 
//Result is set to 'retval' pointer
int sqroot_int(long base, double *retval){
	if (retval == NULL) return ERR_NULL_PTR; 
    if(base < 0) return ERR_NEGATIVE_SQRT;
    if(base == 0){
        *retval = 0.0;
        return ERR_OK;
    }
    long start = 0, end = base;
    double mid;
    double ans;
 
    // find integral part of square
    while (start <= end) {
        long sum;
        add_int(start, end, &sum);
        divide_int(sum, 2, &mid);
        //Check if number is perfect square
        long square;
        times_int((long)mid, (long)mid, &square);
        if (square == base) {
            ans = mid;
            break;
        }
 
        long square_mid;
        times_int(mid, mid, &square_mid);
        if (square_mid < base) {
            ans=start;
            add_int(mid, 1, &start);
        }
        else {
            subs_int(mid, 1, &end);
        }
    }
 
    // Find the fractional part
    double increment = 0.0001;
    for (long i = 0; i < 10; add_int(i, 1, &i)) {
        
        while (ans*ans <= base) {
            ans += increment;
        }
        //TODO: REEMPLAZAR POR FUNCIONES PROPIAS
        ans -= increment;
        increment /= 10;
    }
    *retval = ans;
    return ERR_OK;

};