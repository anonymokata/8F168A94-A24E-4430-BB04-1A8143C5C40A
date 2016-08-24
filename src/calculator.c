#include "calculator.h"
#include <string.h>

void add(char *result, const char *left_oper, const char *right_oper)
{
	strcpy(result, left_oper);
	strcpy(result+strlen(left_oper), right_oper);
}

