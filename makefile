CC = gcc
CFLAGS = -Wall -g -std=c99

BIN = ./bin/
SRC = ./src/

program:
	$(CC) $(CFLAGS) wordChecker.c scoreboard.c dictionary.c boardGenerator.c boggle.c -Iinclude -o program

cls:
	clear

clean:
	rm program