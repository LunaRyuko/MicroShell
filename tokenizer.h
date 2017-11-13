#ifndef __TOKENIZER_H
#define __TOKENIZER_H

#ifdef WIN32
#pragma once
#endif

//extern char ** tokenArray;

char ** tokenize_input(char *input, int *tokenCount);

#endif
