#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "calculator.h"
#include "calc_operations.h"
#include "bit_operations.h"

// union statement to manage both signed and unsigned types
typedef union {
	int32_t signed_value;
	uint32_t unsigned_value;
} int32_value;

static void usage(const char *name){
	printf("Incorrect supply of arguments.\n");
	printf("Usage: %s <number> <operator> <number>\n", name);
	printf("Operators: + - * / %\n");
}

static void validate_and_print_signed_result(int32_t *result){
	if (INT32_MIN > *result || INT32_MAX < *result){
		printf("Error: result is out of int32_t boundary");
	}
	else {
		printf("%d\n", *result);
	}
}

static void validate_and_print_unsigned_result(uint32_t *result){
	if (0 > *result || UINT32_MAX < *result){
		printf("Error: result is out of uint32_t boundary");
	}
	else {
		printf("%u\n", *result);
	}
}

// TODO: input validation function
// handle bad inputs, integer overflow, etc
// usigned int should not be negative (it is never negative)
static int validate_int(const char *argv){
	int num = atoi(argv);
	// out of boundary check
	if (INT32_MIN > num || INT32_MAX < num){
		return 1;
	}

	return 0;
}

int start(int argc, char *argv[]){
	int32_value f_num, s_num, result;
	char *op;

	// check if all 3 arguments were supplied
	if (4 != argc){
		usage(argv[0]);
		return 1;
	}
	
	// checking if user's values are in boundaries of int32_t size
	if (0 != validate_int(argv[1]) || 0 != validate_int(argv[3])){
		printf("Error: one of the user's input number is out of the boundary of int32_t size");
		return 1;
	}

	f_num.signed_value = atoi(argv[1]);
	s_num.signed_value = atoi(argv[3]);

	op = argv[2];

	// check if the operator falls within the limits length
	if (0 == strlen(op) || strlen(op) > 3) { 
		printf("Error: incorrect operator.\n");
		usage(argv[0]);
		return 1;
	}

	switch (op[0]){
		case '+':
			result.signed_value = add(f_num.signed_value, s_num.signed_value);
			validate_and_print_signed_result(&result.signed_value);
			break;
		case '-':
			result.signed_value = subtract(f_num.signed_value, s_num.signed_value);
			validate_and_print_signed_result(&result.signed_value);
			break;
		case '*':
			result.signed_value = multiply(f_num.signed_value, s_num.signed_value);
			validate_and_print_signed_result(&result.signed_value);
			break;
		case '/':
			if (0 != divide(f_num.signed_value, s_num.signed_value, &result.signed_value)) {
				printf("Error: can not divide by 0.\n");
				return 1;
			}
			validate_and_print_signed_result(&result.signed_value);
			break;
		case '%':
			if (0 != modulo(f_num.signed_value, s_num.signed_value, &result.signed_value)) {
				printf("Error: can not perform modulo by 0.\n");
				return 1;
			}
			validate_and_print_signed_result(&result.signed_value);
			break;
		// TODO: should not operate with negative numbers
		case '&':
			result.unsigned_value = op_and(f_num.unsigned_value, s_num.unsigned_value);
			validate_and_print_unsigned_result(&result.unsigned_value);
			break;
		case '|':
			result.unsigned_value = op_or(f_num.unsigned_value, s_num.unsigned_value);
			validate_and_print_unsigned_result(&result.unsigned_value);
			break;
		case '^':
			result.unsigned_value = op_xor(f_num.unsigned_value, s_num.unsigned_value);
			validate_and_print_unsigned_result(&result.unsigned_value);
			break;
		case '<':
			if (0 == strcmp(op, "<<")){
				result.unsigned_value = l_shift(f_num.unsigned_value, s_num.unsigned_value);
				validate_and_print_unsigned_result(&result.unsigned_value);
			}
			else if (0 == strcmp(op, "<<<")){
				result.unsigned_value = l_rotate(f_num.unsigned_value, s_num.unsigned_value);
				validate_and_print_unsigned_result(&result.unsigned_value);
			}
			else {
				printf("Error: incorrect operator.\n");
				usage(argv[0]);
				return 1;
			}
			break;
		case '>':
			if (0 == strcmp(op, ">>")){
				result.unsigned_value = r_shift(f_num.unsigned_value, s_num.unsigned_value);
				validate_and_print_unsigned_result(&result.unsigned_value);
			}
			else if (0 == strcmp(op, ">>>")){
				result.unsigned_value = r_rotate(f_num.unsigned_value, s_num.unsigned_value);
				validate_and_print_unsigned_result(&result.unsigned_value);
			}
			else {
				printf("Error: incorrect operator.\n");
				usage(argv[0]);
				return 1;
			}
			break;
		default:
			printf("Error: unsupported operator");
			return 1;
	}

	return 0;
}
