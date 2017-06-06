CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
BIN = uebung3 

.PHONY: clean

all: $(BIN) 

$(BIN): uebung3.c 
<<<<<<< HEAD
	$(CC) $(CFLAGS) $(BIN).c $^ -o $(BIN)
=======
	$(CC) $(CFLAGS)  uebung3.c -o $(BIN)
>>>>>>> fc5497d0459585dc65307362cfbde2ee0a6d896b
clean:
	rm -rf $(BIN) 
