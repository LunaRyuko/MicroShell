CC=gcc
CFLAGS=-Wall -ansi

BINARY=microshell
SOURCEFILES=main.c tokenizer.c util.c

$(BINARY): $(SOURCEFILES) Makefile
    $(CC) $(CFLAGS) -o $(BINARY) $(SOURCEFILES) 