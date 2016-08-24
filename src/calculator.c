#include <stdio.h>
#include "validate.h"
#include "convert_roman.h"
#include "calculator.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 100

void replace(char *result, const char *pattern, const char *replacement)
{
        char *sub_string_pointer;
        if (NULL != (sub_string_pointer = strstr(result, pattern)))
        {
		size_t pattern_length = strlen(pattern);
		size_t replacement_length = strlen(replacement);
		strcpy(&sub_string_pointer[replacement_length], &sub_string_pointer[pattern_length]);
		memcpy(sub_string_pointer, replacement, replacement_length);
        }
}

void replace_all(char *patterns[][2], int patternsc, char *result)
{
	int pidx;
	for(pidx = 0; pidx < patternsc; pidx++)
	{
		replace(result, patterns[pidx][0], patterns[pidx][1]);
	}
}

int compare_roman_chars(const void *a, const void *b)
{
	int ia = convert_roman_char_to_dec((char *)a);
	int ib = convert_roman_char_to_dec((char *)b);

	return (ia < ib) - (ia > ib);
}

void contract(char *result)
{
	char *patterns[12][2] = { 
				{"CCCCC", "D"}, 
				{"XXXXX", "L"}, 
				{"IIIII", "V"},
				{"DD", "M"},
				{"LL", "C"},
				{"VV", "X"},
				{"DCCCC", "CM"},
				{"CCCC", "CD"},
				{"LXXXX", "XC"},
				{"XXXX", "XL"},
				{"VIIII", "IX"},
				{"IIII", "IV"}
			       };
	qsort(result, strlen(result), sizeof(char), compare_roman_chars);
	replace_all(patterns, 12, result);
}

void expand(char *operand, const char *oper)
{
	char *patterns[6][2] = {
				{"CM", "DCCCC"},
				{"CD", "CCCC"},
				{"XC", "LXXXX"},
				{"XL", "XXXX"},
				{"IX", "VIIII"},
				{"IV", "IIII"}
			       };
	strcpy(operand, oper);
	replace_all(patterns, 6, operand);
}

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
		strcpy(result + strlen(left_operand), right_operand);

		validate(result);
		contract(result);
	} else {
		strcpy(result, "ERROR");
	}
}

void subtract(char *result, const char *left_opr, const char *right_opr)
{
	strcpy(result, "I");
}
