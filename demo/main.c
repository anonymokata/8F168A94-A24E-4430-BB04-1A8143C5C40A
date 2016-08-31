#include <stdio.h>
#include <string.h>
#include "calculator.h"

int main(int argc, const char* argv[])
{
	char result[100];
	const char *operator, *left_operand, *right_operand;
	int idx;
	for(idx = 1; idx < argc; idx++)
	{
		if ((char)argv[idx][0] == '-' || (char)argv[idx][0] == '+')
		{
			break;
		}
	}
	switch(idx)
	{
		case 1:
			{
				operator = argv[idx];
				left_operand = argv[idx + 1];
				right_operand = argv[idx + 2];
			}
			break;
		case 2:
			{
				left_operand = argv[idx - 1];
				operator = argv[idx];
				right_operand = argv[idx + 1];
			}
			break;
		case 3:
			{
				left_operand = argv[idx - 2];
				right_operand = argv[idx - 1];
				operator = argv[idx];
			}
			break;
		default:
			{
				strcpy(result, "ERROR - no operator provided"); 
			}
			break;
	}
	switch(operator[0])
	{
		case '-': subtract(result, left_operand, right_operand); break;
		case '+': add(result, left_operand, right_operand); break;
		default : strcpy(result, "ERROR - unknown operator"); break;
	}
	printf("%s\n", result);
	return 0;
}
