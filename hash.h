#include <stdio.h>

/*  This is a C 'interface' containing functions for a
	Hash Table (with seperate chaining) of key/val pairs
	with keys being char* and vals being void* types.

	@filename hash.h
	@author Colin St. Claire, colinst.claire@gmail.com
	@created 2/10/2016
	@modified 2/22/2016
*/

// Node struct
typedef struct _node {
	char *key;
	void *val; // a "generic" pointer
	struct _node *next; 
} Node;

//HashTable struct
typedef struct _hash {
	int size;
	int count;
	Node **array;
	int collisions;
} HashTable;

Node* nodeInit(char *key, void* val); // a node constructor

HashTable* hashInit(int size); // a HashTable constructor, default size is 16

void* search(HashTable *table, char *key); // returns the void* val associated with a char* key

void insert(HashTable *table, char *key, void* val); // inserts a new key/val pair

void freeBird(HashTable* table); // garbage collection

void hashApply(HashTable *table, void (*funcName) (char* key, void* val)); // allows user to apply a function

void resizeRehash(HashTable* oldTable);
