#include "convert_roman.h"
#include "validate.h"
#include <string.h>
#include <stdbool.h>

#define MAX_ROMAN 3999

bool within_range(char *result)
{
	int sum = 0;
	for(int idx = 0; idx < strlen(result); idx++)
	{
		sum += convert_roman_char_to_dec(result + idx);
	}
	return sum < MAX_ROMAN;
}

bool is_roman_number(const char * result)
{
	const char VALID_CHARS[] = "IVXLCDM";
	bool rval = true;
	for(int idx = 0; idx < strlen(result); idx++)
	{
		rval &= (NULL == strchr(VALID_CHARS, result[idx]));
	}
	return rval;
}

void validate(char *result)
{
	if (!within_range(result) || is_roman_number(result))
	{
		strcpy(result, "ERROR");
	}
}
