#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include "board_generator.h"
#include "word_checker.h"
#include "scoreboard.h"

#define MAXLINE 100


//set up board, set up dictionary
void incrementTotalScore(int *userScore, char *word);


void freeAndResetBoard(struct rolledDice **gameBoard, struct presetDice *inputArrayOfDice){

	for(int i = 0; i < 4; i++){
		free(gameBoard[i]);
	}

	rollDice(gameBoard, inputArrayOfDice);
}


char *convertToUpper(char **upper){
	char *upperDeref = *upper;

	for(int i = 0; upperDeref[i]; i++){
	  upperDeref[i] = toupper(upperDeref[i]);
	}

	return upperDeref;
}


char *convertToUpper2(char (*upper)[]){
	char *upperDeref = *upper;

	for(int i = 0; upperDeref[i]; i++){
	  upperDeref[i] = toupper(upperDeref[i]);
	}

	return upperDeref;
}


void incrementTotalScore(int *userScore, char *word){
	int wordLen = strlen(word);
	
	fprintf(stdout, "wordLen: %d\n",wordLen);

	if (wordLen == 3 || wordLen == 4){
		*userScore += 1;
	}
	else if (wordLen == 5){
		*userScore += 2;
	}
	else if (wordLen == 6){
		*userScore += 3;
	}
	else if (wordLen == 7){
		*userScore += 5;
	}
	else if (wordLen >= 8){
		*userScore += 11;
	}
}


int main(int argc, char **argv){
	int i = 0;
	int points = 0;
	int testPoints = 0;
	int invalidSize = 0;
	char inputWord[100];
	char originalInputWord[100];

	FILE *inputFP;
	char line [MAXLINE];
	char *fileName;
 	
 	const char *dictName = "EnglishWords.txt";
	DNode* checkEnglish;
	DNode* checkSubmitted;
	static DNode* englishDictionary [BIGHASHSIZE];
	static DNode* guessedWords [SMALLHASHSIZE];

	int currentScore = 0;
	int turnCount = 0;

	User *head = NULL;
	head = (User*)malloc(sizeof(User));

	PresetDice globalDice[16];
	RolledDice *gameBoard[4];

	FILE *output_FP;
	char readLine[MAXLINE]; 


	if (!(inputFP = fopen(dictName, "r"))){
        fprintf(stderr,"Could not open file \"%s\" for reading dictionary words\n", dictName);
        return 1;
    }

	while(fgets(line, MAXLINE, inputFP)!=NULL){
		//trim new line characters
		line[strcspn(line, "\r\n")] = '\0';  
		insert(englishDictionary, BIGHASHSIZE, convertToUpper2(&line));
	}	
	fclose(inputFP);


	if (argc == 1){
		fprintf(stdout, "Playing in Normal Mode\n\n");

		system("clear");

		initializePresetDice(globalDice);

		rollDice(gameBoard, globalDice);

		while(turnCount >= 0){
			strcpy(originalInputWord, inputWord);

			convertToUpper2(&inputWord);

			User *thisUser;
			char inputName[100];

			if (strcmp(originalInputWord, "q") == 0){
				// "q" is the input, print scoreboard and exit game
				printScoreboard(head);
				break;
			}
			// "n" is the input, adds user to/changes user in linked list and
			// resets game
			if (strcmp(originalInputWord, "n") == 0){

				printScoreboard(head);
				fprintf(stdout, "Your current score: %d \n", currentScore);
				fprintf(stdout, "What is your name? \n");
				scanf("%s", inputName);

				if (userIsInList(head, inputName) == 0){
					addNode(head, inputName, currentScore);
				}
				else{
					updateNodeWithName(head, inputName, currentScore);
				}

				currentScore = 0;

				strcpy(inputWord, "");

				freeAndResetBoard(gameBoard, globalDice);
				turnCount = 0;
				system("clear");
				continue;
			}

            /***************************************************************************************
            *    Jacob Parr
            *    0971846
            *    From line 150 to the end of the file, I am responsible for the refactoring of this code.
            *
            ***************************************************************************************/


            printBoardGame(boardGame);

            checkEnglish = lookup (englishDictionary, BIGHASHSIZE, inputWord);          
            
            if (checkEnglish != NULL) {
                checkSubmitted = lookup (guessedWords, SMALLHASHSIZE, inputWord);
                
                if ( checkSubmitted == NULL ) {

                    if ( strlen(inputWord) > 2 ){

                        if ( wordChecker (boardGame, inputWord) ){
                            insert ( guessedWords, SMALLHASHSIZE, inputWord );
                            incrementTotalScore( &currentScore, inputWord );
                            fprintf ( stdout, "Correct! You current score is now: %d \n", currentScore );
                    
                        } 
                        else {
                            fprintf (stderr, "The submitted word: \'%s\'' does not abide game rules. Try again!\n", originalInputWord);
                        }
                    } 
                    else {
                        fprintf (stderr, "The submitted word: \'%s\'' must be at least 3 letters long. Try again!\n", originalInputWord);
                    }

                } 
                else {
                    fprintf (stderr, "You have already submitted the word: \'%s\'' Try again!\n", originalInputWord);
                }

            } 
            else if (turnCount > 0) {
                fprintf (stderr, "Incorrect word: \'%s\' is not in the English Dictionary. Try again!\n", originalInputWord);
            }

            fprintf(stdout, "Submit a word you found:\n");
            scanf("%s", inputWord);
            turnCount++;
            system("clear");

        }
        for ( int i = 0; i < 4; i++ ) {
            free(boardGame[i]);
        }
        freeAll(head);

    }



        
    else if (argc == 2) {
        fileName =  argv[1];
        fprintf(stdout, "playing in test mode with file: %s\n", fileName);
        FILE *testFileFP;
        char testLine [MAXLINE];
        char *testWords;
        char **testBoard;
        int fileLineCounter = 1;
        DNode* testResult;
        int begin = 0;


        // (1) read first line which is the board
        if (!(testFileFP = fopen ( fileName , "r" )))    {
            fprintf(stderr,"Could not open test file \'%s\' for reading\n", fileName);
            return 1;
        }
        else if(!(outputFP = fopen("result.txt", "w" ))) {
         fprintf(stderr,"Could not open result file \'%s\' for writing\n", "result.txt");
            return 1;
        }

        while (fgets (testLine, MAXLINE, testFileFP)!=NULL ) {
            testLine[strcspn(testLine, "\r\n")] = '\0';  //trim new line characters

            if(fileLineCounter == 1){
                convert_to_board(testLine, &testBoard);

                    // this can be removed, its just for testing purposes
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        if (j != 3) {
                            fprintf(stdout, "%c \t", testBoard[i][j] );
                        }
                        else {
                            fprintf(stdout, "%c \n", testBoard[i][j] );
                            
                        }
                    }
                    
                }
            
            }
            else if (fileLineCounter >= 2){
                for (char *p = strtok(testLine,","); p != NULL; p = strtok(NULL, ",")){
                    checkEnglish = lookup (englishDictionary, BIGHASHSIZE, convert_to_upper(&p));
                        
                    if (checkEnglish != NULL) {
                        checkSubmitted = lookup (guessedWords, SMALLHASHSIZE, p);
                        
                        if (checkSubmitted == NULL) {
                            if(test_wordChecker(testBoard, p)) {
                                insert (guessedWords, SMALLHASHSIZE, p);
                                incrementTotalScore(&testPoints, p);
                                fprintf(stdout,"Correct! You total score is now: %d \n",testPoints );
                        
                            }
                            else {
                                if(begin == 0){                             
                                    fprintf(outputFP, "%s", p );
                                    begin++;
                                }
                                else {
                                    fprintf(outputFP, ",%s", p );
                                }
                                
                                fprintf(stderr,"The submitted word: \'%s\'' does not abide game rules. Try again!\n", p);                               
                            }

                        }
                        else {
                            if(begin == 0) {                                
                                fprintf(outputFP, "%s", p );
                                begin++;
                            }
                            else {
                                fprintf(outputFP, ",%s", p );
                            }
                            fprintf(stderr,"You have already submitted the word: \'%s\'' Try again!\n", p);
                        }

            
                    }
                    else { 
                        if ( begin == 0 ){                              
                            fprintf( outputFP, "%s", p );
                            begin++;
                        }
                        else {
                            fprintf( outputFP, ",%s", p );
                        }

                        fprintf( stderr,"Incorrect word: \'%s\'' is not in the English Dictionary. Try again!\n", p);
                    }
                }
            }
            fileLineCounter++;
        }

        fprintf(outputFP, "\n");
        fprintf(outputFP, "%d\n", testPoints);

        fclose (testFileFP);

        for (int i = 0; i < 4; i++) {
            free(testBoard[i]);
        }
        free(testBoard);

        fclose(outputFP);

    }

    freeDictionary(englishDictionary, BIGHASHSIZE);
    freeDictionary(guessedWords, SMALLHASHSIZE);

    return 0;
}