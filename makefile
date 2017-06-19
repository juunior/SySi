CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
BIN = start sem sigtest

.PHONY: clean

all: $(BIN)

sigtest: sigtest.c
	$(CC) $(CFLAGS) $? -o $@

sem: sem.c
	$(CC) $(CFLAGS) $? -o $@

start: start.c 
	$(CC) $(CFLAGS) $? -o $@
clean:
	rm -rf $(BIN) 
