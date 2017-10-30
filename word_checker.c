#include <stdio.h>
#include <string.h>
#include "word_checker.h"
#include <ctype.h>

char getLetter(int i, int j, struct rolled_dice **game_board){
    return game_board[i][j].character;
}

int abidesRules(int i, int j, char *word, struct rolled_dice** game_board, int subLen, int **visited){
	int adjCell;
	char currentLetter = word[subLen];
	int ans = (subLen == (strlen(word)-1));


	if(subLen == (strlen(word)-1)){
		return 1;
	}

	// right, digUpRight, up, digUpLeft, left, digDownLeft, down, digDownRight
	int allXValues[] = {0, -1, -1, -1, 0, 1, 1, 1};
	int allYValues[] = {1, 1, 0, -1, -1, -1, 0, 1};

		int newXValue;
		int newYValue;
	
		char findLetter;
			  findLetter = word[subLen + 1];
			int result = 0;

			for(adjCell = 0; adjCell < 8; adjCell++){
				int newXValue = i + allXValues[adjCell];
				int newYValue = j + allYValues[adjCell];
				if((newXValue >= 0) && (newXValue < 4) && (newYValue >=0) && (newYValue < 4) && toupper(findLetter) == get_letter(newXValue, newYValue, game_board) && !visited[newXValue][newYValue]){
					visited[newXValue][newYValue] = 1;
					++subLen;
					result = abides_rules(newXValue, newYValue, word, game_board, subLen, visited);
				if(result){
					return 1;
				}else{
				--subLen;
				}
						
				}
			
		}
	
		return 0;
}


int wordChecker(struct rolled_dice **game_board, char *word){
	
	int row, letter, col, m, n;
	int **visited;
	visited = malloc(sizeof(int * ) * 4);

	visited[0] = malloc(sizeof(int) * 4);
	visited[1] = malloc(sizeof(int) * 4);
	visited[2] = malloc(sizeof(int) * 4);
	visited[3] = malloc(sizeof(int) * 4);

	for(m = 0; m < 4; m++){
		for(n = 0; n < 4; n++){
			if(m == 0 && n == 0){
				visited[m][n] = 1;
			}else{
			visited[m][n] = 0;
			}
		}
	}

		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				if(abides_rules(row, col, word, game_board, 0, visited)){
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

char testGetLetter(int i, int j, char **boggle){

	return boggle[i][j];
}



int testAbidesRules(int i, int j, char *word, char **game_board, int subLen, int **visited){
		int adjCell;
	// use subLen as index to see what letter to find
	char currentLetter = word[subLen];
	int ans = (subLen == (strlen(word)-1));
	if(subLen == (strlen(word)-1)){
		return 1;
	}

	int allXValues[] = {0, -1, -1, -1, 0, 1, 1, 1};
	int allYValues[] = {1, 1, 0, -1, -1, -1, 0, 1};

		int newXValue;
		int newYValue;
	
		char findLetter;
			if(toupper(currentLetter) == 'Q' && toupper(word[subLen + 2]) == test_get_letter(i,j,game_board)){
				 findLetter = word[subLen + 3];
				 subLen++;
				 subLen++;
				 currentLetter = word[subLen];
			}else{
				findLetter = word[subLen + 1];
			}
			int result = 0;

			for(adjCell = 0; adjCell < 8; adjCell++){
				int newXValue = i + allXValues[adjCell];
				int newYValue = j + allYValues[adjCell];
				if((newXValue >= 0) && (newXValue < 4) && (newYValue >=0) && (newYValue < 4) 
					&& toupper(findLetter) == test_get_letter(newXValue, newYValue, game_board) 
					&& !visited[newXValue][newYValue]){
					visited[newXValue][newYValue] = 1;
					++subLen;
					result = test_abides_rules(newXValue, newYValue, word, game_board, subLen, visited);
						if(result){
						return 1;
						}else{
						--subLen;
						}
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
    int letter;
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

    int letter = 0;
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
int hcAbidesRules(int i, int j, char *word, char boggle[][4], int subLen, int **visited){
 
    char currentLetter = word[subLen];
    int ans = (subLen == (strlen(word)-1));
    
    if(subLen == (strlen(word)-1)){
        return 1;
    }

    int allXValues[] = {0, -1, -1, -1, 0, 1, 1, 1};
    int allYValues[] = {1, 1, 0, -1, -1, -1, 0, 1};
    int newXValue;
    int newYValue;
    char findLetter;
   
    if(toupper(currentLetter) == 'Q' && toupper(word[subLen + 2]) == hcGetLetter(i,j,boggle)){
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
       
        int newXValue = i + allXValues[adjCell];
        int newYValue = j + allYValues[adjCell];
       
        if((newXValue >= 0) && (newXValue < 4) && (newYValue >=0) && (newYValue < 4) 
        && toupper(findLetter) == hc_get_letter(newXValue, newYValue, boggle) 
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
char hcGetLetter(int i, int j, char boggle[][4]){

    return boggle[i][j];
}
