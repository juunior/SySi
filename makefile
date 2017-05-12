CC = gcc
CFLAGS = -Wall -pedantic -std=c99
BIN = aufgabe2 

.PHONY: clean

all: $(BIN) 

$(BIN): aufgabe2.c 
	$(CC) $(CFLAGS)  $(BIN).c -o $(BIN)
clean:
	rm -rf $(BIN) 
