#include <stdlib.h>
#ifndef XIAOXIAOLE_H
#define XIAOXIAOLE_H
	#include "../include/字符消消乐之按顺序消除更多者胜.h"
#endif

void TheWord_init(TheWord *self, const char* content, const char* name)
{
	self->长度 = strlen(content);
	self->内容 = malloc(self->长度 + 1);
	strcpy(self->内容, content);
	
	self->可消除内容在自身位置列表 = malloc(sizeof ( short ) * self->长度);
	self->可消除内容首次出现在对方位置列表 = malloc(sizeof ( short ) * self->长度);
	self->可消除内容列表 = malloc(sizeof ( char ) * self->长度);	
	self->可消除数量 = 0;
	self->每个字符情况 = malloc( sizeof (TheChar*) * self->长度 );
	
	self->名称 = malloc(sizeof (char ) * strlen(name) + 1);
	strcpy(self->名称, name);
}

// 将TheWord以这种方式初始化：其字符串是随机生成，对方字符串是从己方随机替换得到。
// 该功能缺少自定义。
// 8、10、3这样的数字，就连名称都仍然在函数内写。
// 但是传值到函数参数括号里又懒得传。大量信息储存到结构体，直接传结构体吗？
void TheWord_init_random(TheWord* self, TheWord* opponent)
{	
	char random_word_minLen = 8;
	char random_word_maxLen = 10;
	char* random_word = malloc(sizeof (char ) * random_word_maxLen);
	char random_replace_maxLen = 3;
	
	产生任意长度的任意字符串(random_word, random_word_minLen, random_word_maxLen);
	TheWord_init(self, random_word, "左");

	//free(random_word);
	random_word = malloc(sizeof (char ) * random_word_maxLen);
	strcpy(random_word, self->内容);

	字符串任何部分替换成任意新内容或不替换(random_word, random_replace_maxLen);
	TheWord_init(opponent,random_word, "右");
}