#ifndef DICTIONARY_H
#define DICTIONARY_H
#define BIG_HASH_SIZE 20000
#define SMALL_HASH_SIZE 100

#include <stdlib.h>


typedef struct dNode{
	char *key;
    	struct dNode *next;
}dNode;

char *copystr(const char *);
unsigned hash(const char *s);

dNode * lookup(dNode ** dictionary, int hashSize, const char *key);

dNode * insert(dNode ** dictionary, int hashSize, const char * key);

void freeDictionary (dNode ** dictionary, int hashSize);

#endif
