#include "validate.h"
#include "convert_roman.h"
#include "adjust_roman.h"
#include "calculator.h"
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 100

bool validate_inputs(const char *left_oper, const char *right_oper)
{
	bool valid = true;
	if (0u == strlen(left_oper) || 0u == strlen(right_oper)) 
	{
		valid = false;
	}
	return valid;
}

void add(char *result, const char *left_oper, const char *right_oper)
{
	char left_operand[BUFFER_SIZE]; 
	char right_operand[BUFFER_SIZE];

	if (validate_inputs(left_oper, right_oper))
	{
		expand(left_operand, left_oper);
		expand(right_operand, right_oper);

		strcpy(result, left_operand);
		strcpy(&result[strlen(left_operand)], right_operand);

		validate(result);
		contract(result);
	} else {
		strcpy(result, "ERROR");
	}
}

void subtract(char *result, const char *left_oper, const char *right_oper)
{
	char left_operand[BUFFER_SIZE];
	char right_operand[BUFFER_SIZE];

	expand(left_operand, left_oper);
	expand(right_operand, right_oper);
	cancel_like_terms(left_operand, right_operand);
	expand_terms(left_operand, right_operand);
	cancel_like_terms(left_operand, right_operand);
	expand_terms(left_operand, right_operand);
	cancel_like_terms(left_operand, right_operand);
	strcpy(result, left_operand);
	contract(result);
}
