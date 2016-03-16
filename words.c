
#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hash.h"
#define MAX_WORD_SIZE 256
#define INIT_HASH_SIZE 1

/*  This is a C program to open a text file,
	read it's "words" and store them in a 
	Hash Table (with seperate chaining).

	@filename words.c
	@author Colin St. Claire, colinst.claire@gmail.com
	@created 2/16/2016
	@modified 3/11/2016
*/

typedef struct {
	char* key;
	int val;
} Pair;


Pair* pairArray;
int arrayIndex = 0;


char* getNextWord(FILE* fd) {
	char word[MAX_WORD_SIZE];
	int i = 0;
	char c = tolower(fgetc(fd));

	while (c != EOF && !(isalnum(c))) { 
		c = tolower(fgetc(fd));
	}
 
	if (c == EOF) return NULL;

	while (c != EOF && isalnum(c) && i < MAX_WORD_SIZE-1) {
		word[i] = tolower(c);
		i++;
		c = tolower(fgetc(fd));
	}

	word[i] = '\0';
	return strdup(word);
}


void hashPrint(char* key, void* val) {
	int* intVal = (int*) val;
	printf("key = %-15s val = %i\n", key, *intVal);
}


int cmp(const void* first, const void* second) {
	Pair* firstPair = (Pair*) first;
	Pair* secPair = (Pair*) second;
	return (secPair->val - firstPair->val);
}


void putInArray(char* key, void* val) {
	int* intPtr = (int*) val;
	pairArray[arrayIndex].key = key;
	pairArray[arrayIndex].val = *intPtr;
	arrayIndex++;
	return;
}


int main(int argc, char* argv[]) {
	HashTable* table = hashInit(INIT_HASH_SIZE);
	int numLines = 0;
	int fileArg = 1;
	if (argv[1][0] == '-') {
		numLines = atoi(argv[1]) * -1;
		fileArg = 2;
	}

	for (int i = fileArg; i < argc; i++) {
		FILE* fd = fopen(argv[i], "r");

		if (!fd) {
			fprintf(stderr, "The argument being passed is not a file...\n");
			exit(1);
		}

		char *word = getNextWord(fd);

		while (word) {
			int* val = (int*) search(table, word);
			if (val) {
				(*val)++;
				free(word);
			} else {
				int* val = malloc(sizeof(int));
				*val = 1;
				insert(table, word, val);
			}

			word = getNextWord(fd);

		}

		fclose(fd);
		free(word);
	}

	pairArray = (Pair*) calloc(table->count, sizeof(Pair));
	hashApply(table, putInArray);
	
	qsort(pairArray, table->count, sizeof(Pair), cmp);

	if (numLines <= 0 || numLines > table->count) {
		numLines = table->count;
	}

	for (int i = 0; i < numLines; i++) {
		printf("[%i] key = %-15s val = %i\n", i, pairArray[i].key, pairArray[i].val);
	}
	free(pairArray);
	freeBird(table);
		
	return 0;
}







