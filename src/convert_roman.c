#include "convert_roman.h"
#include <string.h>

int convert_roman_char_to_dec(char *c) {
	int value;
	switch(*c)
	{
		case 'I' : value = 1; break;
		case 'V' : value = 5; break;
		case 'X' : value = 10; break;
		case 'L' : value = 50; break;
		case 'C' : value = 100; break;
		case 'D' : value = 500; break;
		case 'M' : value = 1000; break;
		default : value = 0; break;
	}
	return value;
}

const char * expansion_of(char roman_char)
{
	char *value;
	switch(roman_char)
	{
		case 'V' : value = "IIIII"; break;
		default : value = ""; break;
	}
	return value;
}

void delete_char(char *str, int idx)
{
	strcpy(&str[idx], &str[idx + 1]);
}

void cancel_like_terms(char *left_operand, char *right_operand)
{
	size_t left_oper_length = strlen(left_operand);
	size_t right_oper_length = strlen(right_operand);
	int right_oper_offset;
	for(right_oper_offset = right_oper_length - 1; 0 <= right_oper_offset; right_oper_offset--)
	{
		char candidate = right_operand[right_oper_offset];
		int left_oper_offset;
		for(left_oper_offset = left_oper_length - 1; 0 <= left_oper_offset; left_oper_offset--)
		{
			if (candidate == left_operand[left_oper_offset])
			{
				delete_char(left_operand, left_oper_offset);
				delete_char(right_operand, right_oper_offset);
				break;
			}
		}
	}
}

void replace_numeral_with_expansion(char *roman_numeral, int offset) 
{
	const char *expansion = expansion_of(roman_numeral[offset]);
	strcpy(&roman_numeral[offset + strlen(expansion)], &roman_numeral[offset + 1]);
	strcpy(&roman_numeral[offset], expansion);
}

void expand_terms(char *left_operand, char *right_operand)
{
	if (0 < strlen(right_operand))
	{
		size_t left_oper_length = strlen(left_operand);
		size_t right_oper_length = strlen(right_operand);
		int right_oper_offset = right_oper_length - 1;
		char candidate = right_operand[right_oper_offset];
		int left_oper_offset;
		for(left_oper_offset = left_oper_length - 1; 0 <= left_oper_offset; left_oper_offset--)
		{
			if (convert_roman_char_to_dec(&candidate) < convert_roman_char_to_dec(&left_operand[left_oper_offset])) 
			{
				replace_numeral_with_expansion(left_operand, left_oper_offset);
				break;
			}
		}
	}
}

