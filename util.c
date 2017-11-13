#include "common.h"
#include "util.h"

void append_char_to_string(char * dest, char src)
{
	int len = strlen(dest);
	assert(len < 255 && "Max length of string");
	dest[len] = src;
	dest[len + 1] = '\0';
}
