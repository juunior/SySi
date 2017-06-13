CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
BIN = aufgabe1 

.PHONY: clean

all: $(BIN) 

aufgabe1: aufgabe1.c 
	$(CC) $(CFLAGS)  aufgabe1.c -o $(BIN)
clean:
	rm -rf $(BIN) 
