/***************************************************************************************
*    Srosh Khan
*    0955284
*    This file contains all the functions declared in board_generator.h
* 	 These functions control the rolling and shuffling of the dice used in the game as well as 
*	 functions to print the current condition of the game dice
* 
***************************************************************************************/

#include "boardGenerator.h"


// Initializes the dice in the list of pre-set dice. Call once at program start.
void initializePresetDice(struct presetDice* inputArrayOfDice) {
    for (int die = 0; die < 16; die++) {
		inputArrayOfDice[die].position = 0;
	}

	// Initializes individual potential chars for each dice
	inputArrayOfDice[0].configurations = "RIFOBX";
	inputArrayOfDice[1].configurations = "IFEHEY";
	inputArrayOfDice[2].configurations = "DENOWS";
	inputArrayOfDice[3].configurations = "UTOKND";
	inputArrayOfDice[4].configurations = "HMSRAO";
	inputArrayOfDice[5].configurations = "LUPETS";
	inputArrayOfDice[6].configurations = "ACITOA";
	inputArrayOfDice[7].configurations = "YLGKUE";
	inputArrayOfDice[8].configurations = "QBMJOA";
	inputArrayOfDice[9].configurations = "EHISPN";
	inputArrayOfDice[10].configurations = "VETIGN";
	inputArrayOfDice[11].configurations = "BALIYT";
	inputArrayOfDice[12].configurations = "EZAVND";
	inputArrayOfDice[13].configurations = "RALESC";
	inputArrayOfDice[14].configurations = "UWILRG";
	inputArrayOfDice[15].configurations = "PACEMD";
}


// Rolls the dice to be used at the start of each game. Puts the rolled dice in
// game_dice. Does not shuffle the dice. Helper function.
void rollButNotShuffleDice(struct rolledDice* gameDice,
		struct presetDice* inputArrayOfDice) {

	srand(time(NULL));
	for (int die = 0; die < 16; die++) {
		int randomNum = rand()%6;
		gameDice[die].character = inputArrayOfDice[die].configurations[randomNum];
	}
}


// Shuffles an array of rolled dice. Helper function.
void shuffleRolledDicePositions(struct rolledDice* gameDice) {

	struct rolledDice NewGameDice[16];

	int randomNum = 0;
	for (int die = 0; die < 16; die++) {

		srand(time(NULL));
		
		while (game_dice[randomNum].position == -1) {
			randomNum = (int) (rand()%16);
		}
		newGameDice[die] = game_dice[randomNum];
		gameDice[randomNum].position = -1;
	}

	for (int die = 0; die < 16; die++) {
		game_dice[die] = new_game_dice[die];
		game_dice[die].position = die+1;
	}
}


// Rolls the dice to be used at the start of the game and shuffles them, putting
// the dice into the 2D array game_dice. Call once at the start of every game.
void rollDice(struct rolledDice** gameBoard,
		struct presetDice* inputArrayOfDice){

	gameBoard[0] = malloc(sizeof(struct rolled_dice) * 4);
	gameBoard[1] = malloc(sizeof(struct rolled_dice) * 4);
	gameBoard[2] = malloc(sizeof(struct rolled_dice) * 4);
	gameBoard[3] = malloc(sizeof(struct rolled_dice) * 4);

	// temporary array of structs to contain adjusted 1D array of dice.
	struct rolledDice adjustedDiceArray[16];

	rollButNotShuffleDice(adjustedDiceArray, inputArrayOfDice);
	shuffleRolledDicePositions(adjustedDiceArray);

	for (int die = 0; die < 4; die++) {
		for (int die2 = 0; die2 < 4; die2++) {
		    gameBoard[die][die2] = adjustedDiceArray[die*4 +die2];
		}
	}
}


// Prints a visualization of the input array of rolled_dice.
void printGameBoard(struct rolledDice** gameBoard) {

	for (int die = 0; die < 4; die++) {
		for (int die2 = 0; die2 < 4; die2++) {
			if (die2 != 3) {
				printf("%c \t", gameBoard[die][die2].character);
			}
			else {
				printf("%c \n", gameBoard[die][die2].character);

			}
		}
	}
}

// Prints a visualization of the current boggle game board 
void printHCBoard(char boggle[][4]) {

	for (int die = 0; die < 4; die++) {
			for (int die2 = 0; die2 < 4; die2++) {
				if (die2 != 3) {
					printf("%c \t", boggle[die][die2]);
				}
				else {
					printf("%c \n", boggle[die][die2]);

				}
			}
		}
}


// Converts board from a string version to 2D array. Used in test mode
void convertToBoard(char *letters, char ***board){
	// allocate space for boggle board on heap in order to access it in main. 
	char *word;
	int die = 0;
	int die2 = 0;
	int die3 = 0;
	
	*board = malloc(sizeof(char * ) * 4);
	char **boardDeref = *board;

	boardDeref[0] = malloc(sizeof(char) * 4);
	boardDeref[1] = malloc(sizeof(char) * 4);
	boardDeref[2] = malloc(sizeof(char) * 4);
	boardDeref[3] = malloc(sizeof(char) * 4);

	for (die = 0; die < 4; die++) {
		for (die2 = 0; die2 < 4; die2++) {
			if (die2 != 3) {
				boardDeref[die][die2] = letters[die3];
				die3++;
				
			}
			else {
				boardDeref[die][die2] = letters[die3];
				die3++;
			}
		}
	}
}
