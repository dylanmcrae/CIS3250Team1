#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdlib.h>

typedef struct user{
	char name[100];
	int maxScore;
	int totalGames;
	int totalScore;
	struct user *next;

} User;

// Find specific nodes
User *findUserWithName(User *head, char *nameToFind);
int userIsInList(User *head, char *nameToFind);
User *getUserAtIndex(User *head, int index);



// Get locations
int getIndexOfUserWithName(User *head, char *nameToFind);
int getLength(User *head);
User *getLastNode(User *head);



// Prints
void printScoreboard(User *head);



// Node interactions
void addNode(User *head, char *name, int maxScore);
void freeAll(User *head);
void updateNodeWithName(User *head, char *name, int currentScore);



#endif
