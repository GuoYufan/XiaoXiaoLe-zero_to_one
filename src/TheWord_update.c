#ifndef XIAOXIAOLE_H
#define XIAOXIAOLE_H
	#include "../include/字符消消乐之按顺序消除更多者胜.h"
#endif

// 感觉用“上次消除后首次出现在对方哪个位置”来表示“该字符是否可消除”有点险。
void TheWord_update(TheWord* self)
{
	// 将这一波每个字符情况被所在字符串所需要的信息收集到后者中
	TheChar** p_每个字符情况 = self->每个字符情况;	
	for (short i=0; i < self->长度; i++, p_每个字符情况++)
	{
		// 如果该字符可消除
		if ( (*p_每个字符情况) -> 首次出现在对方哪个位置 != -1)
		{
			self->可消除内容在自身位置列表[self->可消除数量] = (*p_每个字符情况)->在自身哪个位置;
			self->可消除内容首次出现在对方位置列表[self->可消除数量] = (*p_每个字符情况)->首次出现在对方哪个位置;
			self->可消除内容列表[self->可消除数量] = (*p_每个字符情况)->内容;
			self->可消除数量++;
		}	
	}
}