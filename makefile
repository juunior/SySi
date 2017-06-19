CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
BIN = start sem sigtest sigtest2 sigtest3

.PHONY: clean

all: $(BIN)

sigtest3: sigtest3.c
	$(CC) $(CFLAGS) $? -o $@

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
