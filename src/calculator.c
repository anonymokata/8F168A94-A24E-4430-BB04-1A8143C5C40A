#include "validate.h"
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

void delete_char(char *str, int idx)
{
	strcpy(&str[idx], &str[idx + 1]);
}

void cancel_like_terms(char *left_operand, char *right_operand)
{
	size_t left_oper_length = strlen(left_operand);
	size_t right_oper_length = strlen(right_operand);
	int right_oper_offset;
	for(right_oper_offset = right_oper_length - 1; 0 <= right_oper_offset; right_oper_offset--)
	{
		char candidate = right_operand[right_oper_offset];
		int left_oper_offset;
		for(left_oper_offset = left_oper_length - 1; 0 <= left_oper_offset; left_oper_offset--)
		{
			if (candidate == left_operand[left_oper_offset])
			{
				delete_char(left_operand, left_oper_offset);
				delete_char(right_operand, right_oper_offset);
				break;
			}
		}
	}
}

void subtract(char *result, const char *left_oper, const char *right_oper)
{
	char left_operand[BUFFER_SIZE];
	char right_operand[BUFFER_SIZE];

	strcpy(left_operand, left_oper);
	strcpy(right_operand, right_oper);
	cancel_like_terms(left_operand, right_operand);
	strcpy(result, left_operand);
}
