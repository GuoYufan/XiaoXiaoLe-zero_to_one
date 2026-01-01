#include <stdio.h>
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
	#include "../include/哈希表.h"
#endif

#ifndef XIAOXIAOLE_H
#define XIAOXIAOLE_H
	#include "../include/字符消消乐之按顺序消除更多者胜.h"
#endif

// 显示该字符情况
void TheChar_show(TheChar *self)
{
	printf("我方位置%d字符%c上次消除后首次出现在对方哪个位置:%d\n",
		self->在自身哪个位置,
		self->内容, 
		self->首次出现在对方哪个位置);
};