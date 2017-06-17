CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
BIN = start

.PHONY: clean

all: start

start: start.c 
	$(CC) $(CFLAGS) $? -o $@
clean:
	rm -rf $(BIN) 
