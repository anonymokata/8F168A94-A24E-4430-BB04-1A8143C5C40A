#include <stdlib.h>
#include <stdbool.h>
#include "validate_rn.h"
#include <regex.h>

bool valid_rn(const char *str)
{
	bool valid = true;
	const char *pattern = "^M{0,3}(C[MD]|D?C{0,3})(X[CL]|L?X{0,3})(I[XV]|V?I{0,3})$";
	regex_t regex;
	int regexec_ = 0;
	if (0 == regcomp(&regex, pattern, REG_EXTENDED + REG_NOSUB)) //don't need to validate after we know it works
	{
		regexec_ = regexec(&regex, str, 0, NULL, 0);
		if (REG_NOMATCH == regexec_ || REG_ESPACE == regexec_)
		{
			valid = false;
		}
	}
	regfree(&regex);
	return valid;
}
