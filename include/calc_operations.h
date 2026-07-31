/** @file calc_operations.h
 *
 * @brief Definition of all functions for arithmetical operations
 *
 */

#ifndef CALC_OPERATIONS_H
#define CALC_OPERATIONS_H

#include <stdint.h>

typedef enum
{
	CALC_STATUS_OK = 0,
	CALC_STATUS_NULL_POINTER,
	CALC_STATUS_OVERFLOW,
	CALC_STATUC_DIVIDE_BY_ZERO
} calc_status_t;

int32_t add(int32_t f_num, int32_t s_num, int32_t * result);
int32_t subtract(int32_t f_num, int32_t s_num, int32_t * result);
int32_t multiply(int32_t f_num, int32_t s_num, int32_t * result);
int32_t divide(int32_t f_num, int32_t s_num, int32_t * result);
int32_t modulo(int32_t f_num, int32_t s_num, int32_t * result);

#endif

/*** end of the file ***/
