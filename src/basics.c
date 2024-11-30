#include "../headers/misc_op.h"
#include "../headers/basics.h"
#include "../headers/basics_int.h"
#include "../headers/errors.h"
#include "../headers/utils.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>
//Takes two decimal numbers and sums them. 
//Precision specifies (almost) the number of decimals taken in count by operation
//Result is set to 'retval' pointer
int add(double a, double b, int precision, double *retval){
	if (retval == NULL) return ERR_NULL_PTR;
    *retval = a + b;
    /*
	if(precision == 0) precision = DEFAULT_PRECISION;

    union {
        double d;
        long long bits;
    } ua = { .d = a }, ub = { .d = b };

    int exp_a = (ua.bits >> 52) & 0x7FF;
    int exp_b = (ub.bits >> 52) & 0x7FF;
    printf("\nADD initial config: a = %lf, b = %lf, prec = %i, retval = %p and val = %lf", a, b, precision, retval, *retval);
    
    while (exp_a != exp_b) {
        printf("\n\ta^b\tEXP\t\t\tua\t\t\tub\n\ta\t%i\t\t\t%lf\t\t\t%lf\n\tb\t%i\t\t\t%lli\t\t\t%lli", exp_a, ua.d, ub.d, exp_b, ua.bits, ub.bits);
        if (exp_a > exp_b) {
            ua.bits >>= 1;
            exp_a--;
        } else {
            ub.bits >>= 1;
            exp_b--;
        }
    }

    long long result_mantissa;
    result_mantissa = ua.bits + ub.bits;

    ua.bits = ((long long)exp_a << 52) | (result_mantissa & ((1LL << 52) - 1));
    *retval = ua.d;
    */
    return ERR_OK;
}

//Takes two decimal numbers and substracts 'b' to 'a'. 
//Precision specifies (almost) the number of decimals taken in count by operation
//Result is set to 'retval' pointer
int subs(double a, double b, int precision, double *retval){
	if(retval == NULL) return ERR_NULL_PTR;
	if(precision == 0) precision = DEFAULT_PRECISION;
	return add(a, -b, precision, retval);
}

//Takes two decimal numbers and multiplies them. 
//Precision specifies (almost) the number of decimals taken in count by operation
//Result is set to 'retval' pointer
int times(double a, double b, int precision, double *retval){
	if(retval == NULL) return ERR_NULL_PTR;
    *retval = a * b;
    /*
	if(precision == 0) precision = DEFAULT_PRECISION;
	long scaled_mult;
	long scale_factor;
	long retval_long;
	int err;
	//Scale to a powerer of two. precision indicates decimal digits that are considered for multiplication (or almost)
	long scale = 1 << precision; 
	long a_scaled = (long) a * scale;
	long b_scaled = (long)b * scale;

	//multiply as normal integer numbers
	err = times_int(a_scaled, b_scaled, &scaled_mult);
	if(err != 0) {return err;}

	//Both numbers were scaled to 2^n, so divide res to (2^n)^2
	err = times_int(scale,scale, &scale_factor);
	if(err != 0) {return err;}

	err = divide_int(scaled_mult, scale_factor, retval);
	if(err != 0) {return err;}
    */
	return 0;
	
}


//Takes two decimal numbers and divides them. 
//Precision specifies (almost) the number of decimals taken in count by operation
//Result is set to 'retval' pointer
int divide(double n, double d, int precision, double *retval){
	if(retval == NULL) return ERR_NULL_PTR;
	if(d == 0.0) return ERR_DIV_BY_ZERO;
    *retval = n / d;
    /*
	if(precision == 0) precision = DEFAULT_PRECISION;

    uint64_t *ua = (uint64_t *)&n;
    uint64_t *ub = (uint64_t *)&d;

    uint64_t sign_a = (*ua >> 63) & 1;
    uint64_t exp_a = (*ua >> 52) & 0x7FF;
    uint64_t mant_a = (*ua & ((1ULL << 52) - 1)) | (1ULL << 52); 

    uint64_t sign_b = (*ub >> 63) & 1;
    uint64_t exp_b = (*ub >> 52) & 0x7FF;
    uint64_t mant_b = (*ub & ((1ULL << 52) - 1)) | (1ULL << 52); 

    uint64_t sign_res = sign_a ^ sign_b;

    int64_t exp_res = (int64_t)(exp_a - exp_b + 1023);

    uint64_t quotient = 0;
    uint64_t remainder = mant_a;

    for (int i = 0; i < 53 + precision; ++i) { 
        remainder <<= 1;
        if (remainder >= mant_b) {
            remainder -= mant_b;
            quotient = (quotient << 1) | 1;
        } else {
            quotient <<= 1;
        }
    }

    while ((quotient & (1ULL << 52)) == 0 && exp_res > 0) {
        quotient <<= 1;
        exp_res--;
    }

    if (exp_res <= 0) return ERR_UNDERFLOW;
    if (exp_res >= 2047) return ERR_OVERFLOW;

    uint64_t res = (sign_res << 63) | ((uint64_t)exp_res << 52) | (quotient & ((1ULL << 52) - 1));
    *retval = *(double *)&res;
    */
    return ERR_OK;
}


//Takes two decimal numbers and raise base to the powerer of n. 
//Result is set to 'retval' pointer
int power(double base, double n, int precision, double *retval){
	int err;
	if (retval == NULL) return ERR_NULL_PTR;
	if(precision == 0) precision = DEFAULT_PRECISION;
    if (base == 0) {

        if (n > 0) {
            *retval = 0;
            return ERR_OK;
        } 
        return ERR_INDEX_NOT_SUPORTED;
    }
    if (n < 0) {
        *retval =  1 / pow(base, -n); 
    }
    *retval = pow(base, n);
    /*
    
	if(n == 0.0){
		*retval = 1.0;
		return ERR_OK;
	}

    if (n < 0.0) {
        double temp;
        err = power(base, -n, 0, &temp);
        if (err != ERR_OK) return err;

        return divide(1.0, temp, 0,retval);
    } else {
        
        double numerator, denominator;
        get_fparts(n, &numerator,&denominator);

		int int_exp = (int)numerator;

		
		*retval = 1.0;
		double temp_base = base;
		for (int i = 0; i < int_exp; i++) {
			err = times(*retval, temp_base, 0, retval);  
			if (err != ERR_OK) return err;
		}
        
        if (denominator > 0) {
            err = sqroot(*retval, 0, retval);
			if (err != ERR_OK) return err;
        }
    }
    */
    return ERR_OK;
}

//Gets the n-root of 'base' number and sets its result to 'retval' pointer
int root(double base, int index, int precision, double *retval){
	if(retval == NULL) return ERR_NULL_PTR; 
    if(index < 0) return ERR_INDEX_NOT_SUPORTED;
    if(base < 0 && (index % 2 == 0)) return ERR_NEGATIVE_SQRT;
    if(base == 0){
        *retval = 0.0;
        return ERR_OK;
    }
    if(base == 0) return ERR_DIV_BY_ZERO;
    double x = base; 
    double epsilon = 1e-10; 

    while (1) {
        double next_x = (1.0 / index) * ((index - 1) * x + base / pow(x, index - 1));
        if (fabs(next_x - x) < epsilon) break;
        x = next_x;
    }

    *retval = x;
    return ERR_OK;
}