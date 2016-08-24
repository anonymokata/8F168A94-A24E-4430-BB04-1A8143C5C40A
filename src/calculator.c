#include "calculator.h"
#include <string.h>
#include <stdbool.h>

void replace(char *result, const char *pattern, const char *replacement)
{
        char *sub_string_pointer;
        if (NULL != (sub_string_pointer = strstr(result, pattern)))
        {
        	int pattern_length = strlen(pattern);
                int replacement_length = strlen(replacement);
                strcpy(sub_string_pointer + replacement_length, sub_string_pointer + pattern_length);
                memcpy(sub_string_pointer, replacement, replacement_length);
        }
}

void contract(char *result)
{
	replace(result, "IIIII", "V");
	replace(result, "IIII", "IV");
}

void add(char *result, const char *left_oper, const char *right_oper)
{
	strcpy(result, left_oper);
	strcpy(result+strlen(left_oper), right_oper);
	contract(result);
}

