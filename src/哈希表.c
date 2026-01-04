#include "../include/哈希表.h"


void HashTable_init(HashTable* self)
{
	memset(self->table, 0, sizeof (self->table));	
}


void HashNode_show(HashNode* self)
{
	printf("(key,value):(%c,%d)\n", self->key, self->value);	
}


short hash(char key)
{
	return ( short )key % HASHSIZE;
}


void HashTable_create(HashTable* self, char key, short value)
{
	HashNode* newNode =(HashNode*) malloc( sizeof (HashNode));
	short index = hash(key);
	HashNode* latest = self->table[index];
	
	newNode->key = key;
	newNode->value = value;
	newNode->previous = latest;
	self->table[index] = newNode;
}


short* HashTable_search(HashTable* self, char key)
{
	short index = hash(key);
	for (HashNode* current = self->table[index]; current!=NULL;)
	{
		if (current->key == key){
			return & (current->value);
		}
		current = current->previous;
	}
	
	return NULL;
}


/*
void main()
{
	
	HashTable ht;
	HashTable_init(&ht);
	
	HashTable_create(&ht, 'f', 6);
	HashTable_create(&ht, 'f', -1);
	HashTable_create(&ht, 'e', -2);
	HashTable_create(&ht, 'z',-3);
	
	char key = 'z';
	short *val = HashTable_search(&ht, key);
	if (val != NULL){
		printf("找到键%c对应的值：%d\n", key, *val);
	} else {
		printf("未找到键%c对应的值", key);
	}
}
*/