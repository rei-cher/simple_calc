#include <stdint.h>
#include "bit_operations.h"

// TODO: edge cases for shifts and rotations

uint32_t l_shift(uint32_t f_num, uint32_t s_num){
	return f_num << s_num;
}

uint32_t r_shift(uint32_t f_num, uint32_t s_num){
	return f_num >> s_num;
}

uint32_t op_and(uint32_t f_num, uint32_t s_num){
	return f_num & s_num;
}

uint32_t op_or(uint32_t f_num, uint32_t s_num){
	return f_num | s_num;
}

uint32_t op_xor(uint32_t f_num, uint32_t s_num){
	return f_num ^ s_num;
}

uint32_t l_rotate(uint32_t f_num, uint32_t s_num){
	s_num = s_num % 32;
	return (f_num << s_num) | (f_num >> (32 - s_num));
}

uint32_t r_rotate(uint32_t f_num, uint32_t s_num){
	s_num = s_num % 32;
	return (f_num >> s_num) | (f_num << (32 - s_num));
}
