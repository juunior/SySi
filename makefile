CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
BIN = uebung3 

.PHONY: clean

all: $(BIN) 

$(BIN): uebung3.c 
	$(CC) $(CFLAGS)  uebung3.c -o $(BIN)
clean:
	rm -rf $(BIN) 
