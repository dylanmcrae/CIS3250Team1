/*
* Dylan McRae
* 0964089
* Looks up if given word is allowed
*/
#include <stdio.h>
#include <string.h>
#include "dictionary.h"



/* 
* Form hash value for string "s"
* This produces a starting value in the dictionary array
*/
unsigned hash(const char *s){
	unsigned hashVal;
	for( hashVal = 0; *s != '\0'; s++ ){
		hashVal = *s + 31 * hashVal;
	}
	return hashVal ;
}

/*
*Looks up given word from user
*/
dNode *lookup(dNode ** dictionary, int hashSize, const char *key){
	dNode *np;
	unsigned int hashVal = hash(key);
	for( np = dictionary [ hashVal % hashSize ]; np != NULL; np = np->next ){
		if( strcmp(key, np->key) == 0 ){
			return np; 
	}
	return NULL; 
}

/*
* Inserts node if lookup is NULL
*/
dNode *insert(dNode **dictionary, int hashSize,  const char *key){
	unsigned int hashVal;
	dNode *np;

	if((np = lookup(dictionary, hashSize, key)) == NULL ){ 
		np = (dNode *) malloc(sizeof (*np));

		if(np == NULL || (np->key = copystr (key)) == NULL){
			return NULL;
		}
		hashVal = hash (key) % hashSize;

		np->next = dictionary [hashVal];
		dictionary [hashVal] = np;
	}
	return np;
}

/*
*Frees node function
*/
void freeDictionary(dNode **dictionary, int hashSize){
	int i;
	for( i = 0; i < hashSize; i++ ){ 
		if( dictionary [i]!= NULL ){ 
		// If there is an entry at position i
			dNode *head = dictionary[i]; 
			dNode *current = head;
			while( current != NULL ){
				dNode *temp = current;
				current = current->next;
				free (temp);
			}
			dictionary[i] = NULL;  
			// BUG fix
		}
	}
}

/*
*String copy function
*/
char *copystr(const char *s){ 
// make a duplicate of s
	char *p;
	int len = strlen(s);

	p = (char *) malloc(len+1); 
	// +1 for ?\0? 
	if( p != NULL ){
		strncpy(p, s, len);
	}
	p[len] = '\0';

	return p;
}