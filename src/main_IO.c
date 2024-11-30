#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "../headers/errors.h"
#include "../headers/main_IO.h"
#include "../headers/options.h"

#define assert_error_d "\n· ASSERT ERROR: %lf != %lf with error %lf\n"
#define assert_error_i "\n· ASSERT ERROR: %d != %d with error %d\n"
#define no_errors_bye "\nEXECUTED WITH NO ERRORS :)\n*******************BYE*********************\n"

#define prompt_math_err "\nError matemático: %d"
#define prompt_unknown_err "\nError desconocido: %d"
#define prompt_zero_division "\n!!ERROR!!: No se puede ejecutar la división por cero\n"
#define prompt_complex_sqrt "\n!!ERROR!!: La raíz par de un número negativo no está soportada. \n"
#define prompt_invalid_input "\n!!ERROR!!: Introduce un número válido\n"
#define prompt_overflow "\n!!ERROR!!: El número introducido es muy grande\n"
#define prompt_underflow "\n!!ERROR!!: El número introducido es muy pequeño\n"
#define prompt_out_of_domain "\n!!ERROR!!: El número ingresado está fuera del dominio de la función\n"
#define prompt_index_not_suported "\n!!ERROR!!: Índices menores a cero para raices, y cero para exponentes y raíces no está definido\n"
#define prompt_wait_clear "\n\n\n--------- Presiona [ENTER] Para continuar ----------\n\n\n"

#define greeting "\n*************Bienvenido a la calculadora científica**************\n"
#define prompt_number "\nIntroduce el %s: "
#define prompt_op "\n************\n¿Qué operación quieres seleccionar?\n(1) - Suma\n(2) - Resta\n(3) - Multiplicación\n(4) - Division\n(5) - Exponenciacion\n(6) - Raíz n-ésima\n(7) - inverso multiplicativo de un número\n(8) - mcm\n(9) - MCD\n(0) - número absoluto\n(.) - SALIR\n************\n"
#define prompt_bye "\n !! You have input Exit value\n************************************** BYE ********************************\n"


int error_count = 0;

void assert_equals_d(double a, double b, int err){
	if(err != ERR_OK){
		printf("\nYOUR ASSERT HAD AN ERROR\n");
		printError(err);
	}
	if(fabs(a-b) > EPSILON_EQUALS){
		error_count++;
		printf(assert_error_d, a, b, fabs(a-b));
	}
}
void assert_equals_i(int a, int b, int err){
	if(err != ERR_OK){
		printf("\nYOUR ASSERT HAD AN ERROR\n");
		printError(err);
	}
	if(a != b){
		error_count++;
		printf(assert_error_i, a, b, abs(a-b));
	}
}

//Starts the program asking for 
void start(){
	printf(greeting);
}
void finish(){
	if(error_count == 0){
		printf(no_errors_bye);
	}
}

int ask_option(int *retval){
	if(retval == NULL) return ERR_NULL_PTR;
	printf(prompt_op);

	double tmp;
	int err = read_num(OPTION, &tmp);
	if(err != 0 && err != EXIT){return err;}

	*retval = (int) tmp;
	return (*retval < 0 || *retval > 9) ? ERR_INVALID_INPUT : err;
}

void send_res(char *op, double res){
	printf("\n|| El resulado de %s es %g ||-\n", op, res);
}


// Asks user for a number and returns it
int read_num(char *input_type, double *retval){
	if(retval == NULL) return ERR_NULL_PTR;

	char input[100];
    double numero;

    printf("\n · Introduce un número %s: ", input_type);
    if (fgets(input, sizeof(input), stdin)) {
        char *endptr;
		trim(input);

		if(strcmp(input, ".") == 0){
			return EXIT;
		}
        numero = strtod(input, &endptr);

        if (*endptr == '\n' || *endptr == '\0') {
			*retval = numero;
        } else {
			return ERR_INVALID_INPUT;
        }
    } else {
		return ERR_FAILED_READ;
    }

    return 0;
}

void printError(ErrorCode errorCode) {
	//Print error category if defined (i.e math)
	//Quit if error iis unknown
	if(errorCode <= ERROR_MATH && errorCode){
		printf(prompt_math_err, errorCode);
	} else if(errorCode > 0 && errorCode <= -15){
		printf(prompt_unknown_err, errorCode);
		return;
	} 

	//Print specific error type
	switch (errorCode){
		case ERR_INVALID_INPUT:
			printf(prompt_invalid_input);
			break;
		case ERR_OVERFLOW:
			printf(prompt_overflow);
			break;
		case ERR_UNDERFLOW:
			printf(prompt_underflow);
			break;
		case ERR_OUT_OF_DOMAIN:
			printf(prompt_out_of_domain);
			break;
		case ERR_INDEX_NOT_SUPORTED:
			printf(prompt_index_not_suported);
			break;
		case ERR_DIV_BY_ZERO:
			printf(prompt_zero_division);
			break;
		case ERR_NEGATIVE_SQRT:
			printf(prompt_complex_sqrt);
			break;
		case EXIT:
			printf(prompt_bye);
			break;
		default:
			printf(prompt_unknown_err, errorCode);
			break;
	}
}

void clearBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}


void clear_console(ErrorCode clear_err) {
	printf(prompt_wait_clear);
	getchar();
	#ifdef _WIN32
	system("cls");
	#else
		system("clear");
	#endif
}



void trim(char *str){
	size_t len = strlen(str);
	if (len > 0 && str[len - 1] == '\n') {
		str[len - 1] = '\0';
	}
}


