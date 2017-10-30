#ifndef DICTIONARYH
#define DICTIONARYH
#define BIGHASHSIZE 20000
#define SMALLHASHSIZE 100

#include <stdlib.h>


typedef struct dNode{
	char *key;
    	struct dNode *next;
}dNode;

char *copystr(const char *s);
unsigned hash(const char *s);

dNode *lookup(dNode **dictionary, int hashSize, const char *key);

dNode *insert(dNode **dictionary, int hashSize, const char *key);

void freeDictionary (dNode **dictionary, int hashSize);

#endif
