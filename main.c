#include<stdio.h>
#include<math.h>

#define saludo "\n*************Bienvenido a la calculadora científica**************\n"
#define prompt_número "\nIntroduce el %s: "
#define prompt_operacion "\n¿Qué operación quieres seleccionar?\n(1) - Suma\n(2) - Resta\n(3) - Multiplicación\n(4) - Division\n(5) - Exponenciacion\n(6) - Raíz n-ésima"
#define prompt_zero_division "\nERROR: No se puede ejecutar la división por cero\n"
#define prompt_complex_sqrt "\nERROR: La raíz da resultados complejos\n"

double res, num1, num2, exp;

double add(double num1, double num2);
double subs(double num1, double num2);
double times(double base, double factor);
double div(double n, double d);
double pow(double num, double exp);
double root(double num, int index); 
double read_num();

int main(){
	
}

double add(double num1, double num2){

