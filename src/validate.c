#include "validate.h"
#include "validate_rn.h"
#include <string.h>
#include <stdbool.h>

static bool is_roman_number(const char *str)
{
	if (NULL == str || 
            0u == strlen(str) || 
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
