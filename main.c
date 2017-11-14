#include "common.h"
#include "cmds.h"

int main_loop(int argc, char *argv[]);

char *userinput;

int currentInputIndex;

int main(int argc, char *argv[])
{
	currentInputIndex = -1;
	userinput = 0;

	printf("*************************\n");
	printf("* MicroShell v0.1       *\n");
	printf("*  by Maciej Ray Marcin *\n");
	printf("*************************\n");

	return main_loop(argc, argv);
}

int ProcessUserInput(char ** tokenizedInput, int inputTokenCount)
{
	for (int i = 0; i < sizeof(builtInCmds) / sizeof(builtInCmds_t); i++)
	{
		if (strcmp(tokenizedInput[0], builtInCmds[i].cmd) == 0)
		{
			return builtInCmds[i].func(tokenizedInput, inputTokenCount);
		}
	}
	if(fork() == 0)
	{
		exit(execvp(tokenizedInput[0], tokenizedInput));
	} else {
		wait(NULL);
		return 0;
	}
}

int main_loop(int argc, char *argv[])
{
	static char cwd[1024];
	static char username[64];
	static char host[256];
	while (1)
	{
		get_working_directory(cwd, 1024);
		get_user_name(username, 64);
		get_host_name(host, 256);

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
