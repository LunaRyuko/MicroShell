#include "common.h"

int main_loop(int argc, char *argv[]);

typedef int CmdFunc(void);
int CMD_Exit(void);

char *userinput;

int currentInputIndex;

typedef struct builtInCmds_s {
	const char *cmd;
	CmdFunc * func;
} builtInCmds_t;

static builtInCmds_t builtInCmds[] =
{
	{"quit", &CMD_Exit},
	{"exit", &CMD_Exit}
};

int main(int argc, char *argv[])
{
	currentInputIndex = -1;
	userinput = 0;

	printf("MicroShell v0.1        \n");
	printf("   by Maciej Ray Marcin\n");
	printf("                       \n");

	return main_loop(argc, argv);
}

int CMD_Exit(void)
{
	exit(0);
	return 0;
}

int ProcessUserInput(char ** tokenizedInput, int inputTokenCount)
{
	for (int i = 0; i < sizeof(builtInCmds) / sizeof(builtInCmds_t); i++)
	{
		if (strcmp(tokenizedInput[0], builtInCmds[i].cmd) == 0)
		{
			builtInCmds[i].func();
		}
	}
}

int main_loop(int argc, char *argv[])
{
	static char cwd[1024];
	static char username[64];
	static char host[256];
	while (1)
	{
		getcwd(cwd, 1024); // get working directory
#ifdef WIN32
		strcpy(username, getenv("USERNAME"));
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		gethostname(host, 256);
		WSACleanup();
#else
		strcpy(username, getenv("USER"));
		gethostname(host, 256);
#endif

		char **tokenizedInput = 0;
		int inputTokenCount = 0;
		currentInputIndex = -1;
		printf(ANSI_COLOR_GREEN"%s@%s:"ANSI_COLOR_YELLOW"%s"ANSI_COLOR_RESET"> ", username, host, cwd);
		userinput = (char *)calloc(50, 1);
		while (1)
		{
			currentInputIndex++;

			if (currentInputIndex != 0 && currentInputIndex % 50 == 0)
				userinput = (char *)realloc(userinput, currentInputIndex + 50);

			userinput[currentInputIndex] = fgetc(stdin);
			if (userinput[currentInputIndex] == '\n')
			{
				break;
			}
		}
		tokenizedInput = tokenize_input(userinput, &inputTokenCount);
		for (int i = 0; i < inputTokenCount; i++)
		{
			//printf("Token %d: %s\n", i, tokenizedInput[i]);
		}
		ProcessUserInput(tokenizedInput, inputTokenCount);
		//printf("%s", userinput);
		free(userinput);
	}
	return 0;
}
