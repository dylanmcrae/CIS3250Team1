/***************************************************************************************
*    Srosh Khan
*    0955284
*    This file contains functions that control the rolling and shuffling of the dice used in the game as well as 
*	 functions to print the current condition of the game dice
* 
***************************************************************************************/


#ifndef BOARD_GEN
#define BOARD_GEN


#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


// The pre-set dice which keep their values between games.
typedef struct presetDice{
	char *configurations;
	int position;
} presetDice;

// The rolled dice which do not keep their values between games.
typedef struct rolledDice{
	char character;
	int position;
} rolledDice;


// Initializes the dice in the list of pre-set dice. Call once at program start.
void initializePresetDice(struct presetDice* inputArrayOfDice);


// Rolls the dice to be used at the start of each game. Puts the rolled dice in
// game_dice. Does not shuffle the dice. Helper function.
void rollButNotShuffleDice(struct rolledDice* gameDice,
		struct presetDice* inputArrayOfDice);


// Shuffles an array of rolled dice. Helper function.
void shuffleRolledDicePositions(struct rolledDice* gameDice);


// Prints a visualization of the input array of rolled_dice.
void printGameBoard(struct rolledDice** gameBoard);


// Rolls the dice to be used at the start of the game and shuffles them, putting
// the dice into the 2D array game_dice. Call once at the start of every game.
void rollDice(struct rolledDice** gameBoard,
		struct presetDice* inputArrayOfDice);

// Converts board from a string version to 2D array. Used in test mode
void convertToBoard(char *letters, char ***board);


// Prints a visualization of the current boggle game board
void printHCBoard(char boggle[][4]);

#endif
