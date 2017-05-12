CC = gcc
CFLAGS = -Wall -pedantic 
BIN = aufgabe2 

.PHONY: clean

all: $(BIN) 

$(BIN): aufgabe2.c 
	$(CC) $(CFLAGS)  $^ -o $(BIN)
clean:
	rm -rf $(BIN) 
