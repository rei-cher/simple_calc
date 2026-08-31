/** @file calculator.h
 *
 * @brief Defines calculator interface
 *
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdint.h>
#include "calc_status.h"

/**
 * @brief List of operators
 */
typedef enum
{
	OPERATOR_ADD = 0,
	OPERATOR_SUBTRACT,
	OPERATOR_MULTIPLY,
	OPERATOR_DIVIDE,
	OPERATOR_MODULO,
	OPERATOR_AND,
	OPERATOR_OR,
	OPERATOR_XOR,
	OPERATOR_LEFT_SHIFT,
	OPERATOR_RIGHT_SHIFT,
	OPERATOR_LEFT_ROTATE,
	OPERATOR_RIGHT_ROTATE
} operator_t;

/**
 * @brief List in integer types
 */
typedef enum
{
	INTEGER_TYPE_SIGNED = 0,
	INTEGER_TYPE_UNSIGNED
} integer_type_t;

/**
 * @brief Integer value based on type
 */
typedef union
{
	int32_t signed_value;
	uint32_t unsigned_value;
} value_t;

/**
 * @brief Structure to hold type and corresponding integer value
 */
typedef struct
{
	integer_type_t type;
	value_t	   value;
} integer_t;

/**
 * @brief Structure to hold parameters for validate_integers function
 */
typedef struct
{
	const char * p_f_input;
	const char * p_s_input;
	integer_type_t integer_type;
	integer_t * p_f_integer;
	integer_t * p_s_integer;
} integer_validation_t;

/**
 * @brief Function that based on the user's input string operator
 * 		  determines what operation to perform
 *
 * @param p_operator_string
 * @param p_operator
 *
 * @return calc_status_t
 */
calc_status_t get_operator(const char * p_operator_string,
						   operator_t * p_operator);

/**
 * @brief Determines integer type based on the operator
 *
 * @param operator
 *
 * @return calc_status_t
 */
integer_type_t get_integer_type(operator_t operator);

/**
 * @brief Validates integer based on its type
 *
 * @param p_f_input
 * @param p_s_input
 * @param integer_type
 * @param p_f_integer
 * @param p_s_integer
 *
 * @return calc_status_t
 */
calc_status_t validate_integers(integer_validation_t * p_validation);

/**
 * @brief Calculating result based on the operator and operands
 *
 * @param operator
 * @param p_f_integer
 * @param 
 *
 * @return calc_status_t
 */
calc_status_t calculate_result(operator_t operator,
							   const integer_t * p_f_integer,
							   const integer_t * p_s_integer,
							   integer_t * p_result);

/**
 * @brief Prints the result on the screen
 *
 * @param p_result
 */
void print_result(const integer_t * p_result);

/**
 * @brief Prints errors on the screen
 *
 * @param status
 */
void print_error(calc_status_t status);

/**
 * @brief Prints usage on the screen
 *
 * @param p_name
 */
void print_usage(const char * p_name);

#endif

/*** end of the file ***/
