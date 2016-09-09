#include "convert_roman.h"
#include "adjust_roman.h"
#include "validate.h"
#include "validate_rn.h"
#include <string.h>
#include <stdbool.h>

#define MAX_ROMAN 3999

static bool validate_value_in_range(const char *result)
{
	char buffer[strlen(result)*2];
	int sum_of_digits = 0;
	int idx;
	expand(buffer, result);
	for(idx = 0; idx < (int)strlen(buffer); idx++)
	{
		sum_of_digits += convert_roman_char_to_dec(&buffer[idx]);
	}
	return 0 < sum_of_digits && sum_of_digits <= MAX_ROMAN;
}

static bool is_roman_number(const char *str)
{
	if (NULL == str || 
            0u == strlen(str) || 
            !validate_value_in_range(str) || 
	    !valid_rn(str))
	{
		return false;
	}
	return true;
}

void validate(char *result)
{
	if (!is_roman_number(result))
	{
		strcpy(result, "ERROR");
	} 
}

bool validate_inputs(const char *left_oper, const char *right_oper)
{
	return is_roman_number(left_oper) && is_roman_number(right_oper);
}
