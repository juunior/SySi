CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
BIN = start sem sigtest sigtest2

.PHONY: clean

all: $(BIN)

sigtest2: sigtest2.c
	$(CC) $(CFLAGS) $? -o $@

sigtest: sigtest.c
	$(CC) $(CFLAGS) $? -o $@

sem: sem.c
	$(CC) $(CFLAGS) $? -o $@

start: start.c 
	$(CC) $(CFLAGS) $? -o $@
clean:
	rm -rf $(BIN) 
