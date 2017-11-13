CC=gcc
CFLAGS=-Wall

BINARY=microshell
SOURCEFILES=main.c tokenizer.c util.c

$(BINARY): $(SOURCEFILES) Makefile
	$(CC) $(CFLAGS) -o $(BINARY) $(SOURCEFILES) 
