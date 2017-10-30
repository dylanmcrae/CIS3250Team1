/***************************************************************************************
*    Renate Danhoundo
*    0973919
*    Brief Description : This file gets letters and checks to make sure they abide by 
*    the rules of the tobble game and it checks it checks the complete word entered.
***************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "word_checker.h"
#include <ctype.h>


// Returns a letter
char getLetter(int i, int j, struct rolledDice **gameBoard){
    return gameBoard[i][j].character;
}


// Checks if the current letter found is within the set rules
int abidesRules(int i, int j, char *word, struct rolledDice **gameBoard, int subLen, int **visited){
	
	char currentLetter = word[subLen];
	int ans = ( subLen == ( strlen( word )-1 ) );

	if(subLen == (strlen(word)-1)){
	   return 1;
	}

	// Right, digUpRight, up, digUpLeft, left, digDownLeft, down, digDownRight
	int allX[] = {0, -1, -1, -1, 0, 1, 1, 1};
	int allY[] = {1, 1, 0, -1, -1, -1, 0, 1};

	char findLetter = word[subLen + 1];
		int result = 0;

		for( int adjCell = 0; adjCell < 8; adjCell++){	
		    int newX =val1+ allX[adjCell];
			int newY = val2 + allY[adjCell];
			if( ( newX >= 0 ) && ( newX < 4 ) && ( newY >= 0 ) && ( newY < 4 ) && toupper( findLetter ) == get_letter( newX, newY, gameBoard ) && !visited[ newX ][ newY ] ){	
				visited[newX][newY] = 1;
				++subLen;
				result = abidesRules(newX, newY, word, gameBoard, subLen, visited);
				if( result ){
				    return 1;
				}
				else{
				    --subLen;
				}
						
			}
			
		}
	
		return 0;
}


// Checks if the word is valid
int wordChecker(struct rolledDice **gameBoard, char *word){
	
	int **visited = malloc(sizeof(int * ) * 4);

	visited[0] = malloc(sizeof(int) * 4);
	visited[1] = malloc(sizeof(int) * 4);
	visited[2] = malloc(sizeof(int) * 4);
	visited[3] = malloc(sizeof(int) * 4);

	for( int m = 0; m < 4; m++ ){
		for( int n = 0; n < 4; n++ ){
			if( m == 0 && n == 0 ){
			    visited[m][n] = 1;
			}
			else{
                            visited[m][n] = 0;
			}
		}
	}

	for ( int row = 0; row < 4; row++ ) {
		for ( int col = 0; col < 4; col++ ) {
			if( abidesRules( row, col, word, gameBoard, 0, visited ) ){
				free(visited[0]);
				free(visited[1]);
				free(visited[2]);
				free(visited[3]);
				return 1;

			}
		}
			
	}
	
	free(visited[0]);
	free(visited[1]);
	free(visited[2]);
	free(visited[3]);

	return 0;

}


// Returns a letter
char testGetLetter(int i, int j, char **boggle){
    return boggle[i][j];
}


// Checks if the current letter found is within the set rules
int testAbidesRules(int i, int j, char *word, char **gameBoard, int subLen, int **visited){
	
	// Use subLen as index to see what letter to find
	char currentLetter = word[subLen];
	int ans = ( subLen == ( strlen( word )-1 ) );
	if( subLen == ( strlen( word)-1 ) ){	
	    return 1;
    }


	int allX[] = {0, -1, -1, -1, 0, 1, 1, 1};
	int allY[] = {1, 1, 0, -1, -1, -1, 0, 1};

	int newX = 0;
	int newY = 0;
	
	char findLetter;
	if( toupper( currentLetter ) == 'Q' && toupper( word[ subLen + 2 ] ) == testGetLetter( i,j,gameBoard ) ){	
		findLetter = word[subLen + 3];
		subLen++;
		subLen++;
		currentLetter = word[subLen];
	}
	else{	
	    findLetter = word[subLen + 1];
	}
	
	int result = 0;

	for( int adjCell = 0; adjCell < 8; adjCell++ ){	
		int newX = i + allX[adjCell];
		int newY = j + allY[adjCell];
		if( ( newX >= 0 ) && 
		    ( newX < 4 ) && 
		    ( newY >= 0 ) && 
		    ( newY < 4) ) &&
		     toupper(findLetter) == testGetLetter(newX, newY, gameBoard) &&
		     !visited[newX][newY]){
	     	     visited[newX][newY] = 1;
		         ++subLen;
			 result = testAbidesRules(newX, newY, word, gameBoard, subLen, visited);
		}		
		if(result){
		    return 1;
		}
		else{
		    --subLen;
		}
	}

	return 0;
}


