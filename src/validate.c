#include "convert_roman.h"
#include "adjust_roman.h"
#include "validate.h"
#include <string.h>
#include <stdbool.h>

#define MAX_ROMAN 3999
#define ROMAN_CHARS "IVXLCDM"

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

static bool validate_is_roman_number(const char *result)
{
	const char VALID_CHARS[] = ROMAN_CHARS;
	bool all_roman_chars = true;
	int idx;
	for(idx = 0; idx < (int)strlen(result); idx++)
	{
		all_roman_chars &= (NULL != strchr(VALID_CHARS, result[idx]));
	}
	return all_roman_chars;
}

static bool has_quads(const char *str)
{
	const char VALID_CHARS[] = ROMAN_CHARS;
	int counts[strlen(ROMAN_CHARS)];
	int idx, jdx;
	char last = '\0';
	for(idx = 0; idx < (int)strlen(ROMAN_CHARS); idx++)
	{
		counts[idx] = 0;
	}
	for(idx = 0; idx < (int)strlen(str); idx++)
	{
		for(jdx = 0; jdx < (int)strlen(ROMAN_CHARS); jdx++)
		{
			if (str[idx] == VALID_CHARS[jdx])
			{
				if (last == VALID_CHARS[jdx])
				{
					counts[jdx]++;
				}
				else
				{
					counts[jdx] = 1;
					last = VALID_CHARS[jdx];
				}
			}
		}
		
	}
	for(idx = 0; idx < (int)strlen(ROMAN_CHARS); idx++)
	{
		if (counts[idx] > 3)
		{
			return true;
		}
	}
	return false;
}

static bool is_roman_number(const char *str)
{
	if (NULL == str || 
            0u == strlen(str) || 
            !validate_value_in_range(str) || 
            !validate_is_roman_number(str) ||
            has_quads(str))
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
