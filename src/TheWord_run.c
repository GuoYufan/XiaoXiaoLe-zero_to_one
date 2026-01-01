#ifndef HASH_TABLE_H
#define HASH_TABLE_H
	#include "../include/哈希表.h"
#endif

#ifndef XIAOXIAOLE_H
#define XIAOXIAOLE_H
	#include "../include/字符消消乐之按顺序消除更多者胜.h"
#endif

// 统一运行整个流程
void TheWord_run(TheWord* self, char* 对方内容)
{
	HashTable ht;
	
	HashTable_init(&ht);
	
	// 记录该字符串中每个字符情况（相对于对手）
	if ( !TheChar_update_按顺序映射关系(self->每个字符情况, self->内容, 对方内容, &ht))
	{
		return;
	}
	TheWord_show_每个字符情况(self);
	TheWord_update(self);
	TheWord_show_可消除内容在自身位置与可消除内容(self);
	TheWord_show_可消除内容在自身位置与首次出现在对方位置的映射表(self);
	TheWord_show_单独处理首次出现在对方位置信息(self);
};