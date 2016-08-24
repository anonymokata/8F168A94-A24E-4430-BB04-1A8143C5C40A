#include "calculator.h"
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 100

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

void expand(char *operand, const char *oper)
{
	strcpy(operand, oper);
	replace(operand, "IV", "IIII");
}

void add(char *result, const char *left_oper, const char *right_oper)
{
	char left_operand[BUFFER_SIZE]; 
	char right_operand[BUFFER_SIZE];

	expand(left_operand, left_oper);
	expand(right_operand, right_oper);

	strcpy(result, left_operand);
	strcpy(result+strlen(left_operand), right_operand);
	contract(result);
}

