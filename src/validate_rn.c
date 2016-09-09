#include <stdio.h>
#include <stdbool.h>
#include "validate_rn.h"
#include <regex.h>

bool valid_rn(const char *str)
{
	const char *pattern = "^M{0,3}((CM|CD){0,1}|C{0,3})X{0,2}L?$";
	regex_t regex;
	int regexec_ = 0;
	printf("valid_rn ? %s\n", str);
	if (0 == regcomp(&regex, pattern, REG_EXTENDED + REG_NOSUB)) //don't need to validate after we know it works
	{
		regexec_ = regexec(&regex, str, 0, NULL, 0);
		if (REG_NOMATCH == regexec_ || REG_ESPACE == regexec_)
		{
			printf("%s doesn't match %s\n", str, pattern);
			return false;
		}
		printf("%s matches %s\n", str, pattern);
	}
	else
	{
		puts("regcomp failed");
	}
	regfree(&regex);
	return true;
}
