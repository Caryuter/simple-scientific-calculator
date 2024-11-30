#ifndef ERRORS_H
#define ERRORS_H

#define ERROR_GENERIC    -1
#define ERROR_MATH       -10
#define EXIT             -20    //SPECIAL VALUE FOR EXITING APP

// Specific errors for simple math operations
typedef enum {
    ERR_OK = 0,                 //Successful operation
    ERR_INVALID_INPUT = -1,     //Used for type validation (i.e input text for any math operation)
    ERR_FAILED_READ = -2,       //Attempt to read a value failed due unexpected input
    ERR_OVERFLOW = -3,          //When right bit shift overflows
    ERR_UNDERFLOW = -4,         //When left bit shift overflows
    ERR_OUT_OF_DOMAIN = -5,     //In case one or more to perform a function is out of its domain
    ERR_NULL_PTR = -6,          //For Null Retvals pointers passed to math functions
    ERR_INDEX_NOT_SUPORTED = -7,      //In case user inputs a decimal index for pow operation

    ERR_DIV_BY_ZERO = -10,      //zero on divisor for division
    ERR_NEGATIVE_SQRT = -11,    //When input de even-index sqroot of negative number
    ERR_CONVERGENCE = -12,      // When Root b doesn't converges
    ERR_EXIT = EXIT,


} ErrorCode;

#define EPSILON_EQUALS 0.000000001 //PERMITED RANGE OF ERROR

#endif