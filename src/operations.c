#include <stdint.h>
#include "operations.h"

int32_t add(int32_t f_num, int32_t s_num){
	return f_num + s_num;
}

int32_t subtract(int32_t f_num, int32_t s_num){
	return f_num - s_num;
}

int32_t multiply(int32_t f_num, int32_t s_num){
	return f_num * s_num;
}

int32_t divide(int32_t f_num, int32_t s_num, int32_t *result){
	if (0 == s_num){
		return 1;
	}

	*result = f_num / s_num;
	return 0;
}

int32_t modulo(int32_t f_num, int32_t s_num, int32_t *result){
	if (0 == s_num){
		return 1;
	}

	*result = f_num % s_num;
	return 0;
}
