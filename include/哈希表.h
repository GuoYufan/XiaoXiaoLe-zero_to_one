#include <stdio.h>
#include <stdlib.h>
#include "哈希表_types.h"

struct HashNode
{
	char key;
	short value;
	struct HashNode* previous;
};

// 哈希表结构
#define HASHSIZE 7
struct HashTable
{
	HashNode* table[HASHSIZE];
};


void HashTable_init(HashTable* self);
void HashNode_show(HashNode* self);
short hash(char key);
void HashTable_create(HashTable* self, char key, short value);
short* HashTable_search(HashTable* self, char key);