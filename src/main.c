#include<stdio.h>
#include "../headers/config.h"
#include "../headers/basics.h"
#include "../headers/misc_op.h"
#include "../headers/basics_int.h"
#include "../headers/main_IO.h"
#include "../headers/tests.h"
#include "../headers/options.h"
#include "../headers/utils.h"

int option;
double a,b,res_double;
long res_long;
int err;
int frst = 0;

int main(){
	#ifdef DEBUG
	test();
	#else

	start();

	while(err != EXIT){
		if(frst != 0)clear_console(err);
		err = ask_option(&option);
		if(err != ERR_OK) {
			if(err != ERR_EXIT) printError(err);
			continue;
		}
		switch (option){
		case OPT_SUM:
			err = read_num(INPUT_NUM_1, &a);
			if(err != 0){printError(err); continue;}
			err = read_num(INPUT_NUM_2, &b);
			if(err != 0){printError(err); continue;}
			
			if (has_decimal(a) == 1 || has_decimal(b) == 1) {
				err = add(a,b,0,&res_double);
				if(err != 0){printError(err); continue;}
				send_res(format_string("%g + %g", a, b), res_double);
			} else {
				err = add_int((long)a,(long)b,&res_long);
				if(err != 0){printError(err); continue;}
				send_res(format_string("%g + %g", a, b), (double) res_long);
			}
			break;
		case OPT_SUBS:
			err = read_num(INPUT_NUM_1, &a);
			if(err != 0){printError(err); continue;}
			err = read_num(INPUT_NUM_2, &b);
			if(err != 0){printError(err); continue;}
			
			if (has_decimal(a) == 1 || has_decimal(b) == 1) {
				err = subs(a,b,0,&res_double);
				if(err != 0){printError(err); continue;}
				send_res(format_string("%g - %g", a, b), res_double);
			} else {
				err = subs_int((long)a,(long)b,&res_long);
				if(err != 0){printError(err); continue;}
				send_res(format_string("%g - %g", a, b), (double) res_long);
			}
			break;
		case OPT_MULT:
			err = read_num(INPUT_NUM_1, &a);
			if(err != 0){printError(err); continue;}
			err = read_num(INPUT_NUM_2, &b);
			if(err != 0){printError(err); continue;}
			
			if (has_decimal(a) == 1 || has_decimal(b) == 1) {
				err = times(a,b,0,&res_double);
				if(err != 0){printError(err); continue;}
				send_res(format_string("%g * %g", a, b), res_double);
			} else {
				err = times_int((long)a,(long)b,&res_long);
				if(err != 0){printError(err); continue;}
				send_res(format_string("%g * %g", a, b), (double) res_long);
			}
			break;
		case OPT_DIV:
			err = read_num(INPUT_NUMERATOR, &a);
			if(err != 0){printError(err); continue;}
			err = read_num(INPUT_DENOMINATOR, &b);
			if(err != 0){printError(err); continue;}
			
			if (has_decimal(a) == 1 || has_decimal(b) == 1) {
				err = divide(a,b,0,&res_double);
				if(err != 0){printError(err); continue;}
				send_res(format_string("%g / %g", a, b), res_double);
			} else {
				err = divide_int((long)a,(long)b,&res_double);
				if(err != 0){printError(err); continue;}
				send_res(format_string("%g / %g", a, b), res_double);
			}
			break;
		case OPT_power:
			err = read_num(INPUT_BASE, &a);
			if(err != 0){printError(err); continue;}
			err = read_num(INPUT_EXP, &b);
			if(err != 0){printError(err); continue;}
			if(has_decimal(b) == 1){
					printError(ERR_INDEX_NOT_SUPORTED);
					continue;
				}
			
			if (has_decimal(a) == 1) {
				err = power(a,b,0,&res_double);
				if(err != 0){printError(err); continue;}
				send_res(format_string("%g ^ %g", a, b), res_double);
			} else {
				err = power_int((long)a,(long)b,&res_double);
				if(err != 0){printError(err); continue;}
				send_res(format_string("%g ^ %g", a, b), (double) res_double);
			}
			break;
		case OPT_SQR:
			err = read_num(INPUT_BASE, &a);
			if(err != 0){printError(err); continue;}
			err = read_num(INPUT_INDEX, &b);
			if(err != 0){printError(err); continue;}
			if(has_decimal(b) == 1){
					printError(ERR_INDEX_NOT_SUPORTED);
					continue;
				}

			if((b == 2) && has_decimal(a) == 0){
				err = sqroot_int((long)a,&res_double);
				if(err != 0){printError(err); continue;}
				send_res(format_string(" ²√ %g", a, b), res_double);
			}
			else {
				err = root(a,b,0,&res_double);
				if(err != 0){printError(err); continue;}
				send_res(format_string("%g√ %g", a, b), res_double);
			} 
			break;
		case OPT_INV:
			err = read_num(INPUT_NUM, &a);
			if(err != 0){printError(err); continue;}
			
			if (has_decimal(a) == 1) {
				err = inverse(a, 0, &res_double);
				if(err != 0){printError(err); continue;}
				send_res(format_string("(%g) ^ -1", a), res_double);
			} else {
				err = inverse_int((long)a, &res_double);
				if(err != 0){printError(err); continue;}
				send_res(format_string("(%g) ^ -1", a), res_double);
			}
			break;
		case OPT_MCM:
			err = read_num(INPUT_NUM_1, &a);
			if(err != 0){printError(err); continue;}
			if(has_decimal(a)) {
				printError(ERR_OUT_OF_DOMAIN);
				continue;
			}
			err = read_num(INPUT_NUM_2, &b);
			if(err != 0){printError(err); continue;}
			if(has_decimal(b)) {
				printError(ERR_OUT_OF_DOMAIN);
				continue;
			}

			err = mcm(a, b, &res_long);
			if(err != 0){printError(err); continue;}

			send_res(format_string("mcm %g y %g", a, b), (double)res_long);

			break;
		case OPT_MCD:
			err = read_num(INPUT_NUM_1, &a);
			if(err != 0){printError(err); continue;}
			if(has_decimal(a)) {
				printError(ERR_OUT_OF_DOMAIN);
				continue;
			}
			err = read_num(INPUT_NUM_2, &b);
			if(err != 0){printError(err); continue;}
			if(has_decimal(b)) {
				printError(ERR_OUT_OF_DOMAIN);
				continue;
			}


			err = mcd(a, b, &res_long);
			if(err != 0){printError(err); continue;}

			send_res(format_string("MCD %g y %g", a, b), (double)res_long);
			break;
		case OPT_ABS:
			err = read_num(INPUT_NUM, &a);
			if(err != 0){printError(err); continue;}
			if (has_decimal(a) == 1) {
				double tmp = a;

				err = absolute(&a);
				if(err != 0){printError(err); continue;}
				send_res(format_string("abs()"), a);
			} else {
				long tmp = (long)a;

				err = absolute_int(&tmp);
				if(err != 0){printError(err); continue;}
				send_res(format_string("abs(%g)", a), (double)tmp);
			}
			break;
		default:
			break;
		}
		frst = 1;
		
	}

	if(err != ERR_OK && err != EXIT){
		printf("\nOops :(\nSomethign strange happened and program broke\n)");
		printError(err);
	}
	
	printf("\n******************************* BYE *****************************************\n");
	return ERR_OK;
	#endif
}
