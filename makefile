CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
BIN = uebung3 

.PHONY: clean

all: $(BIN) 

$(BIN): uebung3.c 
	$(CC) $(CFLAGS) $(BIN).c $^ -o $(BIN)
clean:
	rm -rf $(BIN) 
