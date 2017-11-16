CC=gcc
CFLAGS=-Wall -ansi

BUILD_DIR=build/
BINARY=microshell
SOURCEFILES=main.c tokenizer.c util.c cmds.c

$(BINARY): $(SOURCEFILES) Makefile
	$(CC) $(CFLAGS) -o $(BUILD_DIR)$(BINARY) $(SOURCEFILES) 