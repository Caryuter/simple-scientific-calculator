#include "../headers/config.h"
#include "../headers/tests.h"

#ifdef DEBUG

#include<stdio.h>
#include "../headers/basics.h"
#include "../headers/misc_op.h"
#include "../headers/basics_int.h"
#include "../headers/main_IO.h"
#include "../headers/tests.h"

long test_long;
double test_double;
int test_err;

void test(){
    test_sum();
    test_substract();
    test_multiplication();
    test_division();
    test_misc();
    test_power();
    test_sqroot();

    finish();
}

void test_sum(){
    //test_err = add(4.2, 5.6, 0,&test_double);
    //assert_equals_d(test_double,9.8, test_err);

    test_err = add_int(50,100000, &test_long);
    assert_equals_i(test_long, 100050, test_err);

    test_err = add_int(95,-24,&test_long);
    assert_equals_i(test_long, 71, test_err);

    test_err = add_int(-85,15,&test_long);
    assert_equals_i(test_long, -70, test_err);

    test_err = add_int(74,1,&test_long);
    assert_equals_i(test_long, 75, test_err);

    //test_err = add(-7, -2, 0,&test_double);
    //assert_equals_d(test_double,-9, test_err);
}

void test_substract(){
    //test_err = subs(9.123663,2.8995, 0, &test_double);
    //assert_equals_d(test_double, 6.2242, test_err);

    test_err = subs_int(80,14, &test_long);
    assert_equals_i(test_long,66, test_err);

    test_err = subs_int(50,-49, &test_long);
    assert_equals_i(test_long,99, test_err);

    test_err = subs_int(0,140, &test_long);
    assert_equals_i(test_long,-140, test_err);

    test_err = subs_int(-23,0, &test_long);
    assert_equals_i(test_long,-23, test_err);

    test_err = subs_int(-5,10, &test_long);
    assert_equals_i(test_long, -15, test_err);

    test_err = subs_int(-2,-11, &test_long);
    assert_equals_i(test_long, 9, test_err);
}

void test_misc(){
    test_mcd();
    test_mcm();
    test_absolute();
    test_inverse();
}

void test_absolute(){

    test_long = -7;
    test_err = absolute_int(&test_long);
    assert_equals_i(test_long, -7, test_err);

    test_double = -25.7;
    test_err = absolute(&test_double);
    assert_equals_d(test_double, 25.7, test_err);

    test_long = 9000;
    test_err = absolute_int(&test_long);
    assert_equals_i(test_long, 9000, test_err);


    test_long = -43525;
    test_err = absolute_int(&test_long);
    assert_equals_i(test_long, 43525, test_err);

    test_long = 0;
    test_err = absolute_int(&test_long);
    assert_equals_i(test_long,0, test_err);
}

void test_mcm(){
    test_err = mcm(15,1, &test_long);
    assert_equals_i(test_long, 15, test_err);
    

    test_err = mcm(47, 7, &test_long);
    test_err = mcm(test_long, 11, &test_long);
    assert_equals_i(test_long, 3619, test_err);
}

void test_mcd(){
    test_err = mcd(95, 85, &test_long);
    assert_equals_i(test_long, 5, test_err);

    test_err = mcd(4368, 1071, &test_long);
    assert_equals_i(test_long, 21, test_err);
}

void test_inverse(){
    test_err = inverse_int(5, &test_double);
    assert_equals_d(test_double, 0.2, test_err);

    test_err = inverse_int(-23, &test_double);
    assert_equals_d(test_double, -0.043478261, test_err);

    test_err = inverse_int(3, &test_double);
    assert_equals_d(test_double, 0.4, test_err);

    //test_err = inverse(0.7, 0, &test_double);
    //assert_equals_d(test_double, 1.4286, test_err);
}

void test_multiplication(){
    test_err = times_int(13, 323, &test_long);
    assert_equals_i(test_long, 4199, test_err);

    test_err = times_int(-25, 0, &test_long);
    assert_equals_i(test_long, 0, test_err);


    test_err = times_int(7, -5, &test_long);
    assert_equals_i(test_long, -35, test_err);

    test_err = times_int(-7, 5, &test_long);
    assert_equals_i(test_long, -35, test_err);

    test_err = times_int(-11, -3, &test_long);
    assert_equals_i(test_long, 33, test_err);

    test_err = times(-6.4, 4.1, 0, &test_double);
    assert_equals_d(test_double, -26.24, test_err);

    test_err = times(0, 10000.1, 0, &test_double);
    assert_equals_d(test_double, 0, test_err);
}

void test_division(){
    test_err  = divide_int(5, 2, &test_double);
    assert_equals_i(test_double, 2.5, test_err);

    test_err  = divide_int(-28, 4, &test_double);
    assert_equals_i(test_double, -7, test_err);

    test_err  = divide_int(-920, -580, &test_double);
    assert_equals_i(test_double, 1.586206897, test_err);

    test_err  = divide_int(0, 123, &test_double);
    assert_equals_i(test_double, 0, test_err);



    test_err = divide(-6.4, 4.1, 0, &test_double);
    assert_equals_d(test_double, -1.5610, test_err);

    test_err = divide(0, 10000.1, 0, &test_double);
    assert_equals_d(test_double, 0, test_err);
}

//TODO: Test Power of N
void test_power(){
    test_err = power_int(5,2,&test_double);
    assert_equals_d(test_double, 25.0, test_err);

    test_err = power_int(9, -2, &test_double);
    assert_equals_d(test_double, 0.012345679, test_err);

    test_err = power_int(-123,4,&test_double);
    assert_equals_d(test_double, 228886641.0, test_err);

    test_err = power(0.2, 0.5, 4, &test_double);
    assert_equals_d(test_double, 0.4472, test_err);
}

void test_sqroot(){
    printf("\nTESTING sqrootS");
    test_err = sqroot_int(5,&test_double);
    assert_equals_d(test_double, 2.236067977, test_err);

    test_err = sqroot_int(9, &test_double);
    assert_equals_d(test_double, 3.0, test_err);

    test_err = sqroot_int(123, &test_double);
    assert_equals_d(test_double, 11.090536506, test_err);

    test_err = sqroot_int(687, &test_double);
    assert_equals_d(test_double, 26.210684844, test_err);

    test_err = root(2, 4, 4, &test_double);
    assert_equals_d(test_double, 1.1892, test_err);

    test_err = root(52, 7, 4, &test_double);
    assert_equals_d(test_double, 1.75850, test_err);
}

#endif