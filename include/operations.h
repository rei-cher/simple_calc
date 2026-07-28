#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdint.h>

int32_t add(int32_t f_num, int32_t s_num);
int32_t subtract(int32_t f_num, int32_t s_num);
int32_t multiply(int32_t f_num, int32_t s_num);
int32_t divide(int32_t f_num, int32_t s_num, int32_t *result);
int32_t modulo(int32_t f_num, int32_t s_num, int32_t *result);

#endif
