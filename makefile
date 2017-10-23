CC = gcc
CFLAGS = -Wall -g -std=c99

BIN = ./bin/
SRC = ./src/

program:
	$(CC) $(CFLAGS) $(SRC)word_checker.c $(SRC)scoreboard.c $(SRC)dictionary.c $(SRC)board_generator.c $(SRC)boggle.c -Iinclude -o $(BIN)program

cls:
	clear

clean:
	rm $(BIN)program