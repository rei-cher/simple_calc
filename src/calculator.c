#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "calculator.h"
#include "calc_operations.h"
#include "bit_operations.h"

static void usage(const char *name){
	printf("Incorrect supply of arguments.\n");
	printf("Usage: %s <number> <operator> <number>\n", name);
	printf("Operators: + - * / %\n");
}

int start(int argc, char *argv[]){
	int32_t f_num, s_num, result;
	char *op;

	// check if all 3 arguments were supplied
	if (4 != argc){
		usage(argv[0]);
		return 1;
	}

	f_num = atof(argv[1]);
	s_num = atof(argv[3]);

	op = argv[2];

	// check if the operator falls within the limits length
	if (0 == strlen(op) || strlen(op) > 3) { 
		printf("Error: incorrect operator.\n");
		usage(argv[0]);
		return 1;
	}

	switch (op[0]){
		case '+':
			printf("%d\n", add(f_num, s_num));
			break;
		case '-':
			printf("%d\n", subtract(f_num, s_num));
			break;
		case '*':
			printf("%d\n", multiply(f_num, s_num));
			break;
		case '/':
			if (0 != divide(f_num, s_num, &result)) {
				printf("Error: can not divide by 0.\n");
				return 1;
			}

			printf("%d\n", result);
			break;
		case '%':
			if (0 != modulo(f_num, s_num, &result)) {
				printf("Error: can not perform modulo by 0.\n");
				return 1;
			}
			
			printf("%d\n", result);
			break;
		case '&':
			printf("%u\n", op_and(f_num, s_num));
			break;
		case '|':
			printf("%u\n", op_or(f_num, s_num));
			break;
		case '^':
			printf("%u\n", op_xor(f_num, s_num));
			break;
		case '<':
			if (0 == strcmp(op, "<<")){
				printf("%u\n", l_shift(f_num, s_num));
			}
			else if (0 == strcmp(op, "<<<")){
				printf("%u\n", l_rotate(f_num, s_num));
			}
			else {
				printf("Error: incorrect operator.\n");
				usage(argv[0]);
				return 1;
			}
			break;
		case '>':
			if (0 == strcmp(op, ">>")){
				printf("%u\n", r_shift(f_num, s_num));
			}
			else if (0 == strcmp(op, ">>>")){
				printf("%u\n", r_rotate(f_num, s_num));
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
