#ifndef UTILS_H
#define UTILS_H

char *format_string(const char *tmplt, ...);

int has_decimal(double num);

void get_fparts(double n, double *integer_part, double *fractional_part);

#endif