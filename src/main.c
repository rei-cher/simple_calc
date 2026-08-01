/** @file main.c
 *
 *	@brief Program entry point
 *
 */

#include <stdlib.h>
#include "calculator.h"

#define REQUIRED_NUMBER_OF_ARGUMENTS 4
#define PROGRAM_NAME 0
#define USER_FIRST_INTEGER 1
#define USER_OPERATOR 2
#define USER_SECOND_INTEGER 3

int main(int argc, char *argv[])
{
	calc_status_t status = CALC_STATUS_OK;
	operator_t operator = OPERATOR_ADD;
	integer_type_t integer_type = INTEGER_TYPE_SIGNED;

	integer_t f_integer = {0};
	integer_t s_integer = {0};
	integer_t result = {0};

	int exit_status = EXIT_FAILURE;

	if (REQUIRED_NUMBER_OF_ARGUMENTS != argc)
	{
		status = CALC_STATUS_INVALID_ARGUMENT_COUNT;
	}

	if (CALC_STATUS_OK == status)
	{
		status = get_operator(argv[USER_OPERATOR], &operator);
	}
	
	if (CALC_STATUS_OK == status)
	{
		integer_type = get_integer_type(operator);
	}

	if (CALC_STATUS_OK == status)
	{
		status = validate_integers(argv[USER_FIRST_INTEGER],
								   argv[USER_SECOND_INTEGER],
								   integer_type,
								   &f_integer,
								   &s_integer);
	}

	if (CALC_STATUS_OK == status)
	{
		status = calculate_result(operator,
								  &f_integer,
								  &s_integer,
								  &result);
	}

	if (CALC_STATUS_OK == status)
	{
		print_result(&result);
		exit_status = EXIT_SUCCESS;
	}
	else
	{
		print_error(status);

		if ((CALC_STATUS_INVALID_ARGUMENT_COUNT == status) ||
			(CALC_STATUS_INVALID_OPERATOR == status))
		{
			print_usage(argv[PROGRAM_NAME]);
		}
	}

	return exit_status;
}

/*** end of the file ***/
