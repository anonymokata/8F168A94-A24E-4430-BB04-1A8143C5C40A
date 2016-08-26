#include "adjust_roman.h"
#include "convert_roman.h"
#include <string.h>
#include <stdlib.h>

void replace(char *result, const char *pattern, const char *replacement)
{
        char *sub_string_pointer;
        if (NULL != (sub_string_pointer = strstr(result, pattern)))
        {
		size_t pattern_length = strlen(pattern);
		size_t replacement_length = strlen(replacement);
		strcpy(&sub_string_pointer[replacement_length], &sub_string_pointer[pattern_length]);
		strncpy(sub_string_pointer, replacement, replacement_length);
        }
}

static void replace_all(const char *patterns[][2], int patternsc, char *result)
{
	int pidx;
	for(pidx = 0; pidx < patternsc; pidx++)
	{
		replace(result, patterns[pidx][0], patterns[pidx][1]);
	}
}

static int compare_roman_chars(const void *a, const void *b)
{
	int ia = convert_roman_char_to_dec((char *)a);
	int ib = convert_roman_char_to_dec((char *)b);

	return (int)((ia < ib) - (ia > ib));
}

void expand(char *operand, const char *oper)
{
	const char *patterns[6][2] = {
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

void contract(char *result)
{
	const char *patterns[12][2] = { 
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

