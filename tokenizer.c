#include "common.h"
#include "tokenizer.h"

char ** tokenArray;
static char tokenized[8192];

char ** tokenize_input(char * input, int *tokenCount)
{
	rbool isInStringLiteral = rfalse;
	int currentTokenID = 0;
	int currentTokenStrIndex = 0;
	tokenArray = (char **)calloc(1, sizeof(uintptr_t));
	tokenArray[0] = tokenized;
	memset(tokenArray[0], 0, 8192);

	for(int i = 0;;i++)
	{
		assert(currentTokenStrIndex < 8192);
		if (input[i] == '\0')
		{
			tokenized[currentTokenStrIndex] = '\0';
			break;
		}
		if (i != 0)
		{
			if (input[i] == '"' && input[i - 1] != '\\') isInStringLiteral = !isInStringLiteral;
		}
		if (input[i] == ' ' && strlen(tokenArray[currentTokenID]) != 0)
		{
			if (!isInStringLiteral)
			{
				tokenized[currentTokenStrIndex] = '\0';
				currentTokenStrIndex++;
				currentTokenID++;
				tokenArray[currentTokenID] = &tokenized[currentTokenStrIndex];
				continue;
			}
		}
		if (input[i] == '"' && input[i - 1] == '\\')
		{
			tokenized[currentTokenStrIndex] = input[i];
			currentTokenStrIndex++;
			continue;
		}
		if (input[i] == 'n' && input[i - 1] == '\\')
		{
			tokenized[currentTokenStrIndex] = '\n';
			currentTokenStrIndex++;
			continue;
		}

		if (input[i] == '\n')
		{
			tokenized[currentTokenStrIndex] = '\0';
			break;
		}
		if (input[i] == '\\') continue;
		if ((input[i] != ' ' || isInStringLiteral) && input[i] != '"')
		{
			tokenized[currentTokenStrIndex] = input[i];
			currentTokenStrIndex++;
		}
	}
	*tokenCount = currentTokenID + 1;

	return tokenArray;
}
