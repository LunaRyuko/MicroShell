CC=gcc
CFLAGS=-Wall

BUILD_DIR=build/
BINARY=microshell
SOURCEFILES=main.c tokenizer.c util.c

$(BINARY): $(SOURCEFILES) Makefile
	$(CC) $(CFLAGS) -o $(BUILD_DIR)$(BINARY) $(SOURCEFILES) 
