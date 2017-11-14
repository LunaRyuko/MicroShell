#include "common.h"
#include "util.h"

void append_char_to_string(char * dest, char src)
{
	int len = strlen(dest);
	assert(len < 255 && "Max length of string");
	dest[len] = src;
	dest[len + 1] = '\0';
}

int set_working_directory(char *dest)
{
	return chdir(dest);
}

void get_working_directory(char * dest, int bufSize)
{
	getcwd(dest, bufSize);
}

void get_user_name(char * dest, int bufSize)
{
#ifdef WIN32
	strncpy(dest, getenv("USERNAME"), bufSize);
#else
	strncpy(dest, getenv("USER"), bufSize);
#endif
}

void get_host_name(char * dest, int bufSize)
{
#ifdef WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	gethostname(dest, bufSize);

#ifdef WIN32
	WSACleanup();
#endif
}