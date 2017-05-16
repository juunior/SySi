CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
BIN = aufgabe2 

.PHONY: clean

all: $(BIN) 

$(BIN): aufgabe2.c 
	$(CC) $(CFLAGS)  aufgabe2.c -o $(BIN)
clean:
	rm -rf $(BIN) 
