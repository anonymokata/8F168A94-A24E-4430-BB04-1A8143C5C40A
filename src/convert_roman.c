#include "convert_roman.h"

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


