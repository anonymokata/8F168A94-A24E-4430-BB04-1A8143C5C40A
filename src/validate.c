#include "convert_roman.h"
#include "adjust_roman.h"
#include "validate.h"
#include <string.h>
#include <stdbool.h>

#define MAX_ROMAN 3999
#define ROMAN_CHARS "IVXLCDM"

bool validate_value_in_range(const char *result)
{
	char buffer[strlen(result)*2];
	expand(buffer, result);
	int sum_of_digits = 0;
	int idx;
	for(idx = 0; idx < strlen(buffer); idx++)
	{
		sum_of_digits += convert_roman_char_to_dec(&buffer[idx]);
	}
	return 0 < sum_of_digits && sum_of_digits <= MAX_ROMAN;
}

bool validate_is_roman_number(const char *result)
{
	const char VALID_CHARS[] = ROMAN_CHARS;
	bool all_roman_chars = true;
	int idx;
	for(idx = 0; idx < strlen(result); idx++)
	{
		all_roman_chars &= (NULL != strchr(VALID_CHARS, result[idx]));
	}
	return all_roman_chars;
}

void validate(char *result)
{
	if (0u == strlen(result) || !validate_value_in_range(result) || !validate_is_roman_number(result))
	{
		strcpy(result, "ERROR");
	} 
}

bool validate_inputs(const char *left_oper, const char *right_oper)
{
	bool valid = true;
	if (NULL == left_oper || NULL == right_oper || 
	    0u == strlen(left_oper) || 0u == strlen(right_oper) || 
	    !validate_is_roman_number(left_oper) || !validate_is_roman_number(right_oper) ||
	    !validate_value_in_range(left_oper) || !validate_value_in_range(right_oper)) 
	{
		valid = false;
	}
	return valid;
}
