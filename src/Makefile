# TODO: REMOVE unused variable warings !!! was just annoyed by them !!!
CC=gcc
CFLAGS=-ggdb -Wall -Wextra -lm -O2
BIN=./bin

MAIN=$(BIN)/main
SRC=main.c hilbert.S hilbert.c file_helper.c arg_parse.c

.PHONY: all
all: $(MAIN)
$(BIN)/%: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f ./bin/*
	rm -f ./output/*
