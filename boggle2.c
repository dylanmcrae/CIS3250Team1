#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include "board_generator.h"
#include "wordChecker.h"
#include "scoreboard.h"

#define MAXLINE 100

/**
 - set up board,
 - set up dictionary,
 **/

void incrementTotalScore(int *user_score, char *word);

void free_and_reset_board(struct rolled_dice** boardGame,
        struct preset_dice* input_array_of_dice) {

    for (int i = 0; i < 4; i++) {
        free(boardGame[i]);
    }
    roll_dice(boardGame, input_array_of_dice);
}


char *convert_to_upper(char **upper){
    char *upper_deref = *upper;

    for(int i = 0; upper_deref[i]; i++){
      upper_deref[i] = toupper(upper_deref[i]);
    }
    return upper_deref;
}

char *convert_to_upper2(char (*upper)[]){
    char *upper_deref = *upper;

    for(int i = 0; upper_deref[i]; i++){
      upper_deref[i] = toupper(upper_deref[i]);
    }
    return upper_deref;
}

void incrementTotalScore(int *user_score, char *word){
    int word_len = strlen(word);
    fprintf(stdout, "word_len: %d\n",word_len );
    if(word_len == 3 || word_len == 4){
        *user_score+=1;
    }else if(word_len == 5){
        *user_score+=2;
    }else if(word_len == 6){
        *user_score+=3;
    }else if(word_len == 7){
        *user_score+=5;
    }else if(word_len >= 8){
        *user_score+=11;
    }
}


int main (int argc, char ** argv) {
    int i, points = 0, testPoints = 0, invalid_size = 0;
    char inputWord[100];
    char originalInputWord[100];

    FILE *input_FP;
    char line [MAXLINE];
    char *fileName;
    
    const char * dict_name = "assets/EnglishWords.txt";
    DNode* checkEnglish;
    DNode* checkSubmitted;
    static DNode* englishDictionary [BIGHASHSIZE];
    static DNode* guessedWords [SMALLHASHSIZE];

    int currentScore = 0;
    int turnCount = 0;

    User* head = NULL;
    head = (User*)malloc(sizeof(User));

    PresetDice global_dice[16];
    RolledDice *boardGame[4];

    FILE *outputFP;
    char read_line[MAXLINE]; 


    if(!(input_FP = fopen ( dict_name , "r" )))    {
        fprintf(stderr,"Could not open file \"%s\" for reading dictionary words\n", dict_name);
        return 1;
    }

    while( fgets (line, MAXLINE, input_FP)!=NULL ) {
        line[strcspn(line, "\r\n")] = '\0';  //trim new line characters
        insert (englishDictionary, BIGHASHSIZE, convert_to_upper2(&line));
    }   
    fclose (input_FP);


    if (argc == 1){
        fprintf(stdout, "playing in normal mode\n\n");

        system("clear");

        initialize_preset_dice(global_dice);

        roll_dice(boardGame, global_dice);

        while (turnCount >= 0) {
            strcpy(originalInputWord, inputWord);

            convert_to_upper2(&inputWord);

            User *thisUser;
            char input_name[100];

            if (strcmp(originalInputWord, "q") == 0) {
                // "q" is the input, print scoreboard and exit game
                print_scoreboard(head);
                break;
            }
            // "n" is the input, adds user to/changes user in linked list and
            // resets game
            if (strcmp(originalInputWord, "n") == 0) {

                print_scoreboard(head);
                fprintf(stdout, "Your current score: %d \n", currentScore);
                fprintf(stdout, "What is your name? \n");
                scanf("%s", input_name);

                if (user_is_in_list(head, input_name) == 0){
                    add_node(head, input_name, currentScore);
                }
                else {
                    update_node_with_name(head, input_name, currentScore);
                }

                currentScore = 0;

                strcpy(inputWord, "");

                free_and_reset_board(boardGame, global_dice);
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
