/***************************************************************************************
*    Renate Danhoundo
*    0973919
*    Brief Description : This file contains function prototypes for word_checker.c
***************************************************************************************/

#include <string.h>
#include "boardGenerator.h"
#include <stdlib.h>


char getLetter(int val1, int val2, struct rolledDice **gameBoard);


int abidesRules(int val1, int val2, char *word, struct rolledDice** gameBoard, int subLen, int **visited);


int wordChecker(struct rolledDice **gameBoard, char *word);




char testGetLetter(int val1, int val2, char **boggle);


int testAbidesRules(int val1, int val2, char *word, char **gameBoard, int subLen, int **visited);


int testWordChecker(char **boggle, char *word);




char hcGetLetter(int val1, int val2, char boggle[][4]);


int hcAbidesRules(int val1, int val2, char *word, char boggle[][4], int subLen, int **visited);


int hcWordChecker(char boggle[][4], char *word);


