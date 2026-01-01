#include <stdio.h>
#include <stdlib.h>


// 哈希表节点结构
typedef struct HashNode
{
	char key;
	short value;
	struct HashNode* previous;
} HashNode ;

// 哈希表结构
#define HASHSIZE 7
typedef struct
{
	HashNode* table[HASHSIZE];
} HashTable ;

void HashTable_init(HashTable* self);
void HashNode_show(HashNode* self);
short hash(char key);
void HashTable_create(HashTable* self, char key, short value);
short* HashTable_search(HashTable* self, char key);