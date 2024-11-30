
#include "../headers/utils.h"
#include<stdarg.h>
#include<stdint.h>
#include<stdio.h>

//Formats an String with a given template
char *format_string(const char *tmplt, ...) {
    static char buffer[256]; // Buffer reutilizable (no thread-safe)
    va_list args;
    va_start(args, tmplt);
    vsnprintf(buffer, sizeof(buffer), tmplt, args);
    va_end(args);
    return buffer;
}


//Checks if a number has decimal part
int has_decimal(double num){
    return ((long)num != num);
}

//Gets integer and fractional part of a double 
void get_fparts(double n, double *integer_part, double *fractional_part) {
    uint64_t *binary = (uint64_t *)&n;

    uint64_t sign = (*binary >> 63) & 1;           
    int64_t exponent = ((*binary >> 52) & 0x7FF) - 1023; 
    uint64_t mantissa = (*binary & ((1ULL << 52) - 1)) | (1ULL << 52); 

    if (exponent < 0) {
        *integer_part = 0.0;
        *fractional_part = n;
        return;
    }

    uint64_t int_bits = mantissa >> (52 - exponent);
    uint64_t frac_bits = mantissa & ((1ULL << (52 - exponent)) - 1);

    uint64_t int_rep = (sign << 63) | ((exponent + 1023) << 52) | (int_bits << (52 - exponent));
    *integer_part = *(double *)&int_rep;
    *fractional_part = n - *integer_part;
}