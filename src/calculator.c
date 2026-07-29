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
	printf("Arithmetic operators: + - * / %\n");
	printf("Bitwise operators: & | ^ << >> <<< >>>\n");
}

// ------OPERATORS-------
// determine either to use signed or unsigned int32_t
static int is_calc_op(const char *op){
	return 0 == strcmp(op, "+") || 0 == strcmp(op, "-") || 0 == strcmp(op, "*") || 0 == strcmp(op, "/") || 0 == strcmp(op, "%");
}

static int is_bit_op(const char *op){
	return 0 == strcmp(op, "&") || 0 == strcmp(op, "|") || 0 == strcmp(op, "^") || 0 == strcmp(op, "<<") || 0 == strcmp(op, ">>") || 0 == strcmp(op, "<<<") || 0 == strcmp(op, ">>>");
}


// -------VALIDATIONS---------
// input validation functions
// handle bad inputs, integer overflow, etc
// usigned int should not be negative (it is never negative)

static int validate_int32(const char *argv, int32_t *converted_argv){
	long long num;
	char *end_ptr = NULL;

	num = strtoll(argv, &end_ptr, 10);

	// out of boundary check
	if (INT32_MIN > num || INT32_MAX < num){
		return 1;
	}

	*converted_argv = (int32_t)num;

	return 0;
}

static int validate_uint32(const char *argv, uint32_t *converted_argv){
	unsigned long long num;
	char *end_ptr = NULL;

	// check if user's tryes to provide negative number for bitwise operations
	if ('-' == argv[0]){
		printf("Can not accept negative number for bitwise operations\n");
		return 1;
	}

	// check if the uint32_t within the range of 0 and UINT32_MAX
	num = strtoull(argv, &end_ptr, 10); 
	if (UINT32_MAX < num){
		printf("Number is out-of-boundary: %s\n", argv);
		return 1;
	}

	*converted_argv = (uint32_t)num;

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
	
	op = argv[2];

	// check if the operator is valid
	if (!is_calc_op(op) && !is_bit_op(op)) { 
		printf("Error: incorrect operator '%s'.\n", op);
		usage(argv[0]);
		return 1;
	}

	// check what type to use for int32_t
	// validate user's input
	if (is_calc_op(op)){
		if (0 != validate_int32(argv[1], &f_num.signed_value) || 0 != validate_int32(argv[3], &s_num.signed_value)){
			printf("Error: must use int32_t in arithmetic operations\n");
			return 1;
		}
	}
	else {
		if (0 != validate_uint32(argv[1], &f_num.unsigned_value) || 0 != validate_uint32(argv[3], &s_num.unsigned_value)){
			printf("Error: must use uint32_t in bitwise operations\n");
			return 1;
		}
	}

	switch (op[0]){
		case '+':
			if (0 < s_num.signed_value && INT32_MAX - s_num.signed_value < f_num.signed_value){
				printf("Error: result of addition is exceeded the size of int32_t\n");
				return 1;
			}
			else if (0 > s_num.signed_value && INT32_MAX - s_num.signed_value > f_num.signed_value){
				printf("Error: result of addition is exceeded the size of int32_t\n");
				return 1;
			}

			printf("%d\n", add(f_num.signed_value, s_num.signed_value));
			break;
		case '-':
			if (0 < s_num.signed_value && INT32_MAX + s_num.signed_value > f_num.signed_value){
				printf("Error: result of subtraction is exceeded the size of int32_t\n");
				return 1;
			}
			else if (0 > s_num.signed_value && INT32_MAX + s_num.signed_value < f_num.signed_value){
				printf("Error: result of subtraction is exceeded the size of int32_t\n");
				return 1;
			}

			printf("%d\n", subtract(f_num.signed_value, s_num.signed_value));
			break;
		case '*':
			if (INT32_MAX / s_num.signed_value > f_num.signed_value){
				printf("Error: result of mulriplication is exceeded the size of int32_t\n");
				return 1;
			}

			printf("%d\n", multiply(f_num.signed_value, s_num.signed_value));
			break;
		case '/':
			if (0 != divide(f_num.signed_value, s_num.signed_value, &result.signed_value)) {
				printf("Error: can not divide by 0.\n");
				return 1;
			}

			printf("%d\n", result.signed_value);
			break;
		case '%':
			if (0 != modulo(f_num.signed_value, s_num.signed_value, &result.signed_value)) {
				printf("Error: can not perform modulo by 0.\n");
				return 1;
			}

			printf("%d\n", result.signed_value);
			break;
		case '&':
			printf("%u\n", op_and(f_num.unsigned_value, s_num.unsigned_value));
			break;
		case '|':
			printf("%u\n", op_or(f_num.unsigned_value, s_num.unsigned_value));
			break;
		case '^':
			printf("%u\n", op_xor(f_num.unsigned_value, s_num.unsigned_value));
			break;
		case '<':
			if (0 == strcmp(op, "<<")){
				printf("%u\n", l_shift(f_num.unsigned_value, s_num.unsigned_value));
			}
			else if (0 == strcmp(op, "<<<")){
				printf("%u\n", l_rotate(f_num.unsigned_value, s_num.unsigned_value));
			}
			else {
				printf("Error: incorrect operator.\n");
				usage(argv[0]);
				return 1;
			}
			break;
		case '>':
			if (0 == strcmp(op, ">>")){
				printf("%u\n", r_shift(f_num.unsigned_value, s_num.unsigned_value));
			}
			else if (0 == strcmp(op, ">>>")){
				printf("%u\n", r_shift(f_num.unsigned_value, s_num.unsigned_value));
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
