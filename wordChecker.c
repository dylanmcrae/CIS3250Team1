/***************************************************************************************
*    Renate Danhoundo
*    0973919
*    Brief Description : This file gets letters and checks to make sure they abide by 
*    the rules of the tobble game and it checks it checks the complete word entered.
***************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "wordChecker.h"
#include <ctype.h>


// Returns a letter
char getLetter(int val1, int val2, struct rolledDice **gameBoard){
    return gameBoard[val1][val2].character;
}


// Checks if the current letter found is within the set rules
int abidesRules(int val1, int val2, char *word, struct rolledDice **gameBoard, int subLen, int **visited){
	
	int ans = (subLen == (strlen(word)-1));

	if(ans){
	   return 1;
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

	for(int num1 = 0; num1 < 4; num1++){
		for(int num2 = 0; num2 < 4; num2++){
			if(num1 == 0 && num2 == 0){
				visited[num1][num2] = 1;
			}
			else{
			    visited[num1][num2] = 0;
			}
		}
	}
	

	for (int row = 0; row < 4; row++){
		for (int col = 0; col < 4; col++){
			if(abidesRules(row, col, word, gameBoard, 0, visited)){
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
 char testGetLetter(int val1, int val2, char **boggle){
	 return boggle[val1][val2];
 }


// Checks if the current letter found is within the set rules
int testAbidesRules(int val1, int val2, char *word, char **gameBoard, int subLen, int **visited){
	
	// Use subLen as index to see what letter to find
	char currentLetter = word[subLen];
	int ans = (subLen == (strlen(word)-1));
	if(ans){	
		return 1;
    }


	int allX[] = {0, -1, -1, -1, 0, 1, 1, 1};
	int allY[] = {1, 1, 0, -1, -1, -1, 0, 1};

	int newX = 0;
	int newY = 0;
	
	char findLetter;
	if(toupper(currentLetter) == 'Q' && toupper(word[subLen + 2]) == testGetLetter(val1,val2,gameBoard)){	
		findLetter = word[subLen + 3];
		subLen++;
		subLen++;
		currentLetter = word[subLen];
	}
	else{	
		findLetter = word[subLen + 1];
	}
	
	int result = 0;

	for(int adjCell = 0; adjCell < 8; adjCell++){	
		newX = val1 + allX[adjCell];
		newY = val2 + allY[adjCell];
		if( (newX >= 0) && 
		    (newX < 4) && 
		    (newY >= 0) && 
		    (newY < 4) && 
			(toupper(findLetter) == testGetLetter(newX, newY, gameBoard) && !visited[newX][newY])){
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

/**************************************************************************************************
*RJ Pabayo-Cruz
*ID:0970373
*
*
****************************************************************************************************/
//Tests to see if there is a word in the space
int testWordChecker(char **boggle, char *word){
    
    int **visited;
    visited = malloc(sizeof(int * ) * 4);

    for(int numRows = 0; numRows < 4; numRows++){
        visited[numRows] = malloc(sizeof(int) * 4);
    }

    for(int rowIndex = 0; rowIndex < 4; rowIndex++){
        for(int colIndex = 0; colIndex < 4; colIndex++){
            if(rowIndex == 0 && colIndex == 0){
                visited[rowIndex][colIndex] = 1;
            }
            else{
                visited[rowIndex][colIndex] = 0;
            }
        }
    }

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if(testAbidesRules(row, col, word, boggle, 0, visited)){
                free(visited[0]);
                free(visited[1]);
                free(visited[2]);
                free(visited[3]);
                return 1;
            }
        }
    }

    for(int i = 0; i < 4; i++){
        free(visited[i]);
    }   

    return 0;
}


//Tests to see if the word is in the space
int hcWordChecker(char boggle[][4], char *word){

    int **visited;
    visited = malloc(sizeof(int * ) * 4);

    for(int numCols = 0; numCols < 4; numCols++){
        visited[numCols] = malloc(sizeof(int) * 4);
    }

    for(int rowIndex = 0; rowIndex < 4; rowIndex++){
        for(int colIndex = 0; colIndex < 4; colIndex++){
            if(rowIndex == 0 && colIndex == 0){
                visited[rowIndex][colIndex] = 1;
            }
            else{
                visited[rowIndex][colIndex] = 0;
            }
        }
    }

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if(hcAbidesRules(row, col, word, boggle, 0, visited)){
                free(visited[0]);
                free(visited[1]);
                free(visited[2]);
                free(visited[3]);
                return 1;
            }
        }
    }

    for(int i = 0; i < 4; i++){
        free(visited[i]);
    }

    return 0;

}


//Checks to see if the word abides by the rules 
int hcAbidesRules(int val1, int val2, char *word, char boggle[][4], int subLen, int **visited){
 
    char currentLetter = word[subLen];
    int ans = (subLen == (strlen(word)-1));
    
    if(ans){
        return 1;
    }

    int allXValues[] = {0, -1, -1, -1, 0, 1, 1, 1};
    int allYValues[] = {1, 1, 0, -1, -1, -1, 0, 1};
    int newXValue;
    int newYValue;
    char findLetter;
   
    if(toupper(currentLetter) == 'Q' && toupper(word[subLen + 2]) == hcGetLetter(val1,val2,boggle)){
        findLetter = word[subLen + 3];
        subLen++;
        subLen++;
        currentLetter = word[subLen];
    }
    else{
        findLetter = word[subLen + 1];
    }

    int result = 0;

    for(int adjCell = 0; adjCell < 8; adjCell++){
       
        newXValue = val1 + allXValues[adjCell];
        newYValue = val2 + allYValues[adjCell];
       
        if((newXValue >= 0) && (newXValue < 4) && (newYValue >=0) && (newYValue < 4) 
        && toupper(findLetter) == hcGetLetter(newXValue, newYValue, boggle) 
        && !visited[newXValue][newYValue]){
           
            visited[newXValue][newYValue] = 1;
            ++subLen;
            result = hcAbidesRules(newXValue, newYValue, word, boggle, subLen, visited);

            if(result){
                return 1;
            }
            else{
                --subLen;
            }

        }

    }

    return 0;
}

//Returns a letter
char hcGetLetter(int val1, int val2, char boggle[][4]){

    return boggle[val1][val2];
}
