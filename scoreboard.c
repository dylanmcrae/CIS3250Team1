/***************************************************************************************
 *    Justin Reynoso
 *    0939095
 *    Controls printing and updating the scoreboard of the boggle game
 *
 ***************************************************************************************/


#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "scoreboard.h"


/*
 * Finds and returns a pointer to the User in the linked list beginning with
 * head which has the name nameToFind. If such a User is not in the Linked
 * List, it will return NULL. Helper function to increment_score.
 */

User *findUserWithName(User *headNode, char *nameToFind){

	if ( headNode == NULL ){
		return headNode;
	}
	User *currentNode = headNode;
	while ( currentNode != NULL ){
		if ( strcmp( currentNode -> name, nameToFind ) == 0 ){
			return currentNode;
		}
		currentNode = ( currentNode ) -> next;
	}
	return NULL;
}


/* 
 * Frees every element of the linked list 
 */

void freeAll(User *headNode){

	if ( headNode -> next == NULL ){
		free( headNode );
	}
	else {
		User *currentNode = headNode -> next;
		User *previous = headNode;
		while ( currentNode != NULL ){
			free( previous );
			previous = currentNode;
			currentNode = ( currentNode ) -> next;
		}
	}
}


/* 
 * Cycles through the linked list untill the index desired has been reached, 
 * Or until its confirmed that the index is outside the length of the linked list
 */

User *getUserAtIndex(User *headNode, int index){

	if ( headNode == NULL ){
		return NULL;
	}
	User *currentNode = headNode;
	int count = 0;
	while ( currentNode != NULL ){
		if ( count == index + 1 ){
			return currentNode;
		}
		currentNode = ( currentNode) -> next;
		count++;
	}
	return NULL;
}


/* Searches through the linkedlist looking for a node that matches nameToFind
 * returns count if name is found, return -1 if name can't be found
 */

int getIndexOfUserWithName(User *headNode, char *nameToFind){

	if ( headNode == NULL && headNode -> name != nameToFind ){
		return -1;
	}
	User *currentNode = headNode;
	int count = 0;
	while ( currentNode != NULL ){
		if ( strcmp ( currentNode->name,  nameToFind ) ){
			return count;
		}
		currentNode = ( currentNode ) -> next;
		count++;
	}
	return -1;
}


/*
 * Finds whether or not an existing user is already in the list. If they are,
 * returns 1. If not, returns 0.
 */

int userIsInList(User *headNode, char *nameToFind){
	User *currentNode = headNode;
    while ( currentNode != NULL ){
		if ( strcmp( currentNode -> name, nameToFind ) == 0 ){
			return 1;
		}
		currentNode = ( currentNode ) -> next;
	}
	return 0;
}


// Finds the length of the linkedlist

int getLength(User *headNode){
	if ( headNode == NULL ){
		return 0;
	}
	User *currentNode = headNode;
	int count = 0;
	while ( currentNode != NULL ){
		count++;
		if ( currentNode -> next == NULL ){
			return count;
		}
		currentNode = ( currentNode ) -> next;
	}
	return 0;
}


/*
 * Helper function. Finds the last node in the linked list and returns it.
 * Returns NULL if called with an empty head, although such a case is not used
 * in the main function addNode.
 */

User *getLastNode(User *headNode){
	if ( headNode == NULL ){
		return headNode;
	}
	User *currentNode = headNode;
	while ( currentNode != NULL ){
		if ( currentNode -> next == NULL ){
			return currentNode;
		}
		currentNode = ( currentNode ) -> next;
	}
	return NULL;
}


// Iterates through list printing each node

void printScoreboard(User *headNode){
    fprintf( stdout, "\n" );
    fprintf( stdout, "---- SCORE BOARD ---- \n" );
	if ( headNode -> next != NULL ){
		User *currentNode = headNode -> next;
		while ( currentNode != NULL ){
			printf( "\n" );
			printf( "Player name: %s \n", currentNode -> name );
			printf( "High score: %d \n", currentNode -> maxScore );
			printf( "Games played: %d \n", currentNode -> totalGames );
			printf( "Total score: %d \n", currentNode -> totalScore );
			printf( "\n--------------------- \n" );

			if ( currentNode -> next == NULL ){
				break;
			}
			currentNode = ( currentNode ) -> next;
		}
	}
}


// Adds a new node to the end of the list

void addNode(User *headNode, char *name, int maxScore){
	User *userPtr;
	if ( headNode != NULL ){
	    userPtr = malloc( sizeof( struct user ) );
	}
	strcpy( userPtr -> name, name );
	userPtr -> maxScore = maxScore;
	userPtr -> totalGames = 1;
	userPtr -> totalScore = maxScore;
	userPtr -> next = NULL;

	if ( headNode == NULL ){
		headNode = userPtr;
	}
	else {
		getLastNode( headNode ) -> next = userPtr;
	}
}


/*
 * Updates both the currentScore and the totalScore of a Node
 */

void updateNodeWithName ( User *headNode, char *name, int currentScore ){
	if ( userIsInList( headNode, name ) == 1 ){
		User *userPtr = findUserWithName(headNode, name);
		if ( currentScore > (userPtr -> maxScore) ){
			userPtr -> maxScore = currentScore;
		}
		userPtr -> totalGames += 1;
		userPtr -> totalScore += currentScore;
	}
}
/***************************************************************************************/
