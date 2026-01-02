#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
	#include "../include/哈希表.h"
#endif

#ifndef XIAOXIAOLE_H
#define XIAOXIAOLE_H
	#include "../include/字符消消乐之按顺序消除更多者胜.h"
#endif

void main()
{
	srand(time(NULL));
	TheWord *leftWord, *rightWord;
	leftWord=(TheWord*) malloc(sizeof (TheWord));
	rightWord=(TheWord*) malloc(sizeof (TheWord));
	
	TheWord* 双方[2]={leftWord, rightWord};
	
	// init for random
	TheWord_init_random(leftWord, rightWord);
	
	/*
	// test example: init for const
	// "heghgjfjg" VS "fhfggdjde"
	// "heghjgfjg" VS "fhfgdjgde"
	TheWord_init(leftWord, "MZJAWXU", "左");
	TheWord_init(rightWord,"XMJYAUZ", "右");
	*/
	
	TheWord_init(leftWord, "heghjgfjg", "左");
	TheWord_init(rightWord,"fhfgfjgde", "右");
	
	for (char i=0; i<2; i++)
	{
		TheWord_show_内容(双方[i]);
	}
	puts("🔎");
	for  (char i=0; i<2; i++)
	{
		TheWord_run(双方[i], 双方[1-i]->内容);
		if (!i) puts("\n\n🔎");
	}
	
	for  (char i=0; i<2; i++)
	{
		统一free(双方[i]);
	}
}
