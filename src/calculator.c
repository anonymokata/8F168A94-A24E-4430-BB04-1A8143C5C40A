#include "validate.h"
#include "convert_roman.h"
#include "calculator.h"
#include <string.h>
#include <stdlib.h>

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

int compare_roman_chars(const void *a, const void *b)
{
	int ia = convert_roman_char_to_dec((char *)a);
	int ib = convert_roman_char_to_dec((char *)b);

	return (ia < ib) - (ia > ib);
}

void contract(char *result)
{
	qsort(result, strlen(result), sizeof(char), compare_roman_chars);
	replace(result, "CCCCC", "D");
	replace(result, "XXXXX", "L");
	replace(result, "IIIII", "V");
	replace(result, "DD", "M");
	replace(result, "LL", "C");
	replace(result, "VV", "X");
	replace(result, "DCCCC", "CM");
	replace(result, "CCCC", "CD");
	replace(result, "LXXXX", "XC");
	replace(result, "XXXX", "XL");
	replace(result, "VIIII", "IX");
	replace(result, "IIII", "IV");
}

void expand(char *operand, const char *oper)
{
	strcpy(operand, oper);
	replace(operand, "CM", "DCCCC");
	replace(operand, "CD", "CCCC");
	replace(operand, "XC", "LXXXX");
	replace(operand, "XL", "XXXX");
	replace(operand, "IX", "VIIII");
	replace(operand, "IV", "IIII");
}

void add(char *result, const char *left_oper, const char *right_oper)
{
	char left_operand[BUFFER_SIZE]; 
	char right_operand[BUFFER_SIZE];

	expand(left_operand, left_oper);
	expand(right_operand, right_oper);

	strcpy(result, left_operand);
	strcpy(result + strlen(left_operand), right_operand);

	contract(result);

	validate(result);
}

