/***************************************************************************************
*    Renate Danhoundo
*    0973919
*    Brief Description : This file contains function prototypes for word_checker.c
***************************************************************************************/

#include <string.h>
#include "board_generator.h"
#include <stdlib.h>


char getLetter( int i, int j, struct rolledDice **gameBoard );


int abidesRules( int i, int j, char *word, struct rolledDice** gameBoard, int subLen, int **visited );


int wordChecker( struct rolledDice **gameBoard, char *word );




char testGetLetter( int i, int j, char **boggle );


int testAbidesRules( int i, int j, char *word, char **gameBoard, int subLen, int **visited );


int testWordChecker( char **boggle, char *word );




char hcGetLetter( int i, int j, char boggle[][4] );


int hcAbidesRules( int i, int j, char *word, char boggle[][4], int subLen, int **visited );


int hcWordChecker( char boggle[][4], char *word );



