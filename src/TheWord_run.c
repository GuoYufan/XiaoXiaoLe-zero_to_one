#include "../include/XiaoXiaoLe.h"
#include "../include/哈希表.h"

// 统一运行整个流程
void TheWord_run(TheWord* self, char* 对方内容)
{
	HashTable ht;
	
	HashTable_init(&ht);
	
	// 记录该字符串中每个字符情况（相对于对手）
	if ( !TheChar_update_按顺序映射关系(self, 对方内容, &ht))
	{
		return;
	}
	TheWord_show_每个字符情况(self);
	TheWord_update(self);
	TheWord_show_可消除内容在自身位置与可消除内容(self);
	TheWord_show_可消除内容在自身位置与首次出现在对方位置的映射表(self);
	TheWord_show_单独处理首次出现在对方位置信息(self);
};