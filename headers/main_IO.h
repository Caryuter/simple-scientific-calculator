#ifndef MAIN_IO_H
#define MAIN_IO_H
#include "../headers/errors.h"

int read_num(char *input_type, double *retval);

void assert_equals_d(double a, double b, int err);

void assert_equals_i(int a, int b, int err);

void start();

void finish();

int ask_option(int *retval);

void send_res(char *op, double res);

void printError(ErrorCode errorcode);

void clearBuffer();

void clear_console(ErrorCode clear_err);

void trim(char *str);

#define OPTION "la opción"
#define INPUT_NUM "el número"
#define INPUT_NUM_1 "el primer número"
#define INPUT_NUM_2 "el segundo número"
#define INPUT_INDEX "el índice de la raíz"
#define INPUT_EXP "el exponente al cuál será elevado"
#define INPUT_BASE "la base"
#define INPUT_NUMERATOR "el numerador de la división"
#define INPUT_DENOMINATOR "el denominador de la división"

#endif