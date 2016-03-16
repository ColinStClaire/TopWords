#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hash.h"

/*  This is a C implementation of Hash Table (with seperate chaining)
	for the storing of key/val pairs, keys being char*, and vals
	being void* types.

	@filename hash.c
	@author Colin St. Claire, colinst.claire@gmail.com
	@created 2/10/2016
	@modified 3/11/2016
*/


Node* nodeInit(char *key, void *val) {
	Node *newNode = (Node*) malloc(sizeof(Node));
	newNode->key = key;
	newNode->val = val;
	newNode->next = NULL;
	return newNode;
} 


HashTable* hashInit(int size) {
	HashTable *table = NULL;
	table = malloc(sizeof(HashTable));
	table->size = size;
	table->array = (Node**) calloc(size, sizeof(Node*));
	table->count = 0;
	table->collisions = 0;
	return table;
}


static void freeBirdAux(Node *ptr) {
	if (ptr) {
		free(ptr->key);
		free(ptr->val);
		freeBirdAux(ptr->next);
		free(ptr);
	}
}


void freeBird(HashTable* table) {
	int size = table->size;
	int i;
	for (i = 0; i < size; i++) {
		freeBirdAux(table->array[i]);
	}
	free(table->array);
	free(table);
}


unsigned long hashFunc(char *key) {
	// hash function written by Dan Bernstein
	// stackoverflow.com/questions/7666509/hash-function-for-string
	unsigned long hash = 5381;
	int c;

	while ((c = *key++)) {
		hash = ((hash << 5) + hash + c);
	}

	return hash;
}


static Node* findNode(Node *ptr, char *newKey) {
	if (!ptr) {
		return NULL;
	} else if (strcmp(ptr->key, newKey) == 0) {
		return ptr;	
	} else {
		return findNode(ptr->next, newKey);
	}
}


void* search(HashTable *table, char *key) {
	unsigned long hash = hashFunc(key) % table->size;
	Node* ptr = findNode(table->array[hash], key); 
	return (ptr) ? ptr->val : NULL;
}


static Node* addNode(Node **head, char *newKey, void* newVal) {
	Node *newNode = nodeInit(newKey, newVal);

	if (!*head) { // if the linked list is empty
		*head = newNode;
		return *head;
	} 
	
	Node* test = findNode(*head, newKey);
	if (test) {
		free(test);
		return *head;
	}

	newNode->next = *head;
	
	return newNode;
}


void insert(HashTable *table, char *key, void* val) {
	unsigned long hash = hashFunc(key) % table->size;
	table->array[hash] = addNode(&table->array[hash], key, val);
	table->count++;
	double col = table->count / table->size;
	table->collisions = col;
	if (col >= 2) {
		resizeRehash(table);
	}

	return;
}


void hashApply(HashTable *table, void (*funcName) (char* key, void* val)) {
	int i;
	for (i = 0; i < table->size; i++) {
		Node* ptr = table->array[i];
		while (ptr) {
			funcName(ptr->key, ptr->val);
			ptr = ptr->next;
		}
	}
}


void resizeRehash(HashTable* oldTable) {
	int newSize = oldTable->size * 5;
	HashTable* newTable = hashInit(newSize);
	int i;
	Node* oldNode;
	for (i = 0; i < oldTable->size; i++) {
		oldNode = oldTable->array[i];
		while (oldNode) {
			insert(newTable, oldNode->key, oldNode->val);
			oldNode = oldNode->next;
		}
	}
	
	Node* cursor;
	for (int i = 0; i < oldTable->size; i++) {
		oldNode = oldTable->array[i];
		while (oldNode) {
			cursor = oldNode;
			oldNode = oldNode->next;
			free(cursor);

		}
	}	

	oldTable->size = newTable->size;
	free(oldTable->array);
	oldTable->array = newTable->array;
	free(newTable);
	return;
}








