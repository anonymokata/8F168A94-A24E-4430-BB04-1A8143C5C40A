#include <stdlib.h>
#include <stdbool.h>
#include "validate_rn.h"
#include <regex.h>

bool valid_rn(const char *str)
{
	bool valid = false;
	const char *pattern = "^M{0,3}(C[MD]|D?C{0,3})(X[CL]|L?X{0,3})(I[XV]|V?I{0,3})$";
	regex_t regex;
	regcomp(&regex, pattern, REG_EXTENDED + REG_NOSUB);
	valid = (0 == regexec(&regex, str, 0, NULL, 0));
	regfree(&regex);
	return valid;
}
