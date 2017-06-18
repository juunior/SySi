CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
BIN = start sem

.PHONY: clean

all: start sem

sem: sem.c
	$(CC) $(CFLAGS) $? -o $@

start: start.c 
	$(CC) $(CFLAGS) $? -o $@
clean:
	rm -rf $(BIN) 
