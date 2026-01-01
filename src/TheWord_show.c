#include <stdio.h>
#ifndef XIAOXIAOLE_H
#define XIAOXIAOLE_H
	#include "../include/字符消消乐之按顺序消除更多者胜.h"
#endif

void TheWord_show_内容(TheWord *self)
{
	printf("《显示名称为:%s 字符串内容》", self->名称);
	puts(self->内容);
}

// 显示这一波每个字符情况
void TheWord_show_每个字符情况(TheWord *self)
{
	TheChar** p_每个字符情况 = self->每个字符情况;

	printf("《在字符串%s中》\n", self->内容);
	for (short i=0; i < self->长度; i++ )
	{
		TheChar_show(*p_每个字符情况);
		p_每个字符情况++;
	}	
}

// 显示可消除内容在自身位置与内容相关信息
void TheWord_show_可消除内容在自身位置与可消除内容(TheWord* self)
{
	puts("\n《显示可消除内容在自身位置与内容相关信息》");
	for (char j=0; j<2; j++, j<2?putchar('='):0)
	{
		printf("%s",self->名称);
		putchar('(');
		for (short i=0; i < self->可消除数量; i++)
		{
			printf(j? "%c": "%d", j? self->可消除内容列表[i]: self->可消除内容在自身位置列表[i] );
			putchar(i+1 < self->可消除数量?',':'\0');
		}
		putchar(')');
	}
	putchar(10);
}


/*
《显示映射表》
M(0,1)
Z(1,5)
X(4,0)
*/
void TheWord_show_可消除内容在自身位置与首次出现在对方位置的映射表(TheWord* self)
{
	puts("\n《可消除内容在自身位置与上次消除后首次出现在对方位置的映射表》");
	
	/*TheChar* 可消除字符情况;
	for (short i=0; i < self->可消除数量; i++)
	{
		可消除字符情况 = *(self->每个字符情况 + self->可消除内容在自身位置列表[i]);
		putchar( 可消除字符情况 -> 内容);
		printf("(%d,%d)\n", 可消除字符情况->在自身哪个位置, 可消除字符情况->首次出现在对方哪个位置);
	}
	*/
	
	for (short i=0; i < self->可消除数量; i++)
	{
		putchar( self ->可消除内容列表[i]);
		printf("(%d,%d)\n", self->可消除内容在自身位置列表[i], self->可消除内容首次出现在对方位置列表[i]);
	}
	
}


void TheWord_show_单独处理首次出现在对方位置信息(TheWord *self)
{
	puts("\n《单独处理上次消除后首次出现在对方位置信息》");
	for (short i=0; i < self->可消除数量; i++)
	{
		printf("%d",self->可消除内容首次出现在对方位置列表[i]);
		putchar(i+1 < self->可消除数量?',':'\0');
	}
}