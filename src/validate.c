#include "convert_roman.h"
#include "adjust_roman.h"
#include "validate.h"
#include <string.h>
#include <stdbool.h>

#define MAX_ROMAN 3999
#define ROMAN_CHARS "IVXLCDM"

void validate(char *result)
{
	const char VALID_CHARS[] = ROMAN_CHARS;
	char buffer[strlen(result)*2];
	expand(buffer, result);
	bool all_roman_chars = true;
	int sum_of_digits = 0;
	int idx;
	for(idx = 0; idx < strlen(buffer); idx++)
	{
		sum_of_digits += convert_roman_char_to_dec(&buffer[idx]);
	}
	for(idx = 0; idx < strlen(result); idx++)
	{
		all_roman_chars &= (NULL != strchr(VALID_CHARS, result[idx]));
	}
	if (MAX_ROMAN < sum_of_digits || !all_roman_chars)
	{
		strcpy(result, "ERROR");
	} 
}
