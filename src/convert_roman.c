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

static const char *expansions[] = { "IIIII", "VV", "XXXXX", "LL", "CCCCC", "DD", "" };

static const char *expansion_of(char roman_char)
{
	const char *value;
	switch(roman_char)
	{
		case 'V' : value = expansions[0]; break;
		case 'X' : value = expansions[1]; break;
		case 'L' : value = expansions[2]; break;
		case 'C' : value = expansions[3]; break;
		case 'D' : value = expansions[4]; break;
		case 'M' : value = expansions[5]; break;
		default  : value = expansions[6]; break;
	}
	return value;
}

static void delete_char(char *str, int idx)
{
	strcpy(&str[idx], &str[idx + 1]);
}

int cancel_like_terms(char *left_operand, char *right_operand)
{
	int cancel_count = 0;
	size_t left_oper_length = strlen(left_operand);
	size_t right_oper_length = strlen(right_operand);
	int right_oper_offset;
	for(right_oper_offset = (int)right_oper_length - 1; 0 <= right_oper_offset; right_oper_offset--)
	{
		char candidate = right_operand[right_oper_offset];
		int left_oper_offset;
		for(left_oper_offset = (int)left_oper_length - 1; 0 <= left_oper_offset; left_oper_offset--)
		{
			if (candidate == left_operand[left_oper_offset])
			{
				delete_char(left_operand, left_oper_offset);
				delete_char(right_operand, right_oper_offset);
				cancel_count++;
				break;
			}
		}
	}
	return cancel_count;
}

static void replace_numeral_with_expansion(char *roman_numeral, int offset) 
{
	const char *expansion = expansion_of(roman_numeral[offset]);
	strcpy(&roman_numeral[offset + strlen(expansion)], &roman_numeral[offset + 1]);
	strcpy(&roman_numeral[offset], expansion);
}

int expand_terms(char *left_operand, char *right_operand)
{
	int expansion_count = 0;
	if (0 < (int)strlen(right_operand))
	{
		size_t left_oper_length = strlen(left_operand);
		size_t right_oper_length = strlen(right_operand);
		int right_oper_offset = (int)right_oper_length - 1;
		char candidate = right_operand[right_oper_offset];
		int left_oper_offset;
		for(left_oper_offset = (int)left_oper_length - 1; 0 <= left_oper_offset; left_oper_offset--)
		{
			if (convert_roman_char_to_dec(&candidate) < convert_roman_char_to_dec(&left_operand[left_oper_offset])) 
			{
				replace_numeral_with_expansion(left_operand, left_oper_offset);
				expansion_count++;
				break;
			}
		}
	}
	return expansion_count;
}

