#include <stdio.h>
#include <stdlib.h>
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
	#include "../include/哈希表.h"
#endif

#ifndef XIAOXIAOLE_H
#define XIAOXIAOLE_H
	#include "../include/字符消消乐之按顺序消除更多者胜.h"
#endif

// 记录该字符串中每个字符情况（相对于对手）
// 感觉要不要——或者说有什么办法可以跳过不可消除的（从未出现的、或消除过几次后再也不能出现的）字符而不记录它们呢？
// 现在的情况下，如果用哈希表查找到，得知其不再出现，于是我不记录，而直接continue掉了。
// 那么，*p_每个字符情况，每次循环还是在malloc分配新内存空间返回一个地址值。
// 那么，而循环次数就是有多少个字符就是循环多少次。
// 那么，造成*p_每个字符情况会malloc出大量我没使用的空间，这些空间全部被初始化为“空”“0”。
// 我躲掉那些再也不可消除的字符，以为节省了；事实上还是存在浪费没完全避开。
bool TheChar_update_按顺序映射关系(TheChar** 每个字符情况, char* 我方, char* 对方, HashTable* ht)
{
	if (*我方=='\0'||*对方=='\0')
	{
		printf("❗️双方有其中一方无任何内容，不需要消除\n");
		return false;
	}
	char* pos_address = NULL;
	char 占位符集[2] = {'-','_'};
	char 占位符序号 = 0;
	
	char* p_我方 = 我方;
	TheChar** p_每个字符情况 = 每个字符情况;
	TheChar* self = NULL;
	
	// 考虑在更靠后的位置出现已消除过的内容，从而“首次出现在对方哪个位置”失效的情况
	char* 最近相同内容消除到哪里 = 对方;
	printf("最近相同内容消除到哪里：%s\n",最近相同内容消除到哪里);
	short* 哈希表查找结果=NULL;
	
	for (short pos_index=0; *p_我方 != '\0'; pos_index++, p_我方++)
	{		
		*p_每个字符情况=(TheChar*) malloc(sizeof (TheChar) );
		self = *p_每个字符情况;
		p_每个字符情况++;
		
		self->在自身哪个位置 = pos_index;
		
		// 遍历左字符串的当前搜索到的字符是否出现在对方以及首次出现的位置。
		// 获取到的位置是指针表示的。用指针相减得到索引表示的位置。
		// 下次消除检查起始点必须是上次消除点的下一位
		哈希表查找结果 = HashTable_search(ht, *p_我方);
		
		// 如果该字符已经被检查过至少一次，且该字符的下次消除检查起始点是结尾之后
		if (哈希表查找结果 != NULL && *哈希表查找结果 <0 ){
			self->首次出现在对方哪个位置 = -1;
			self->内容 = *p_我方;
			continue;
		}				
		
		if (哈希表查找结果 != NULL) {
			最近相同内容消除到哪里 = 对方 + *哈希表查找结果 + 1;
		} else 最近相同内容消除到哪里 = 对方;
		
		printf("当前字符:%c 最近相同内容消除到哪里：%s",*p_我方, 最近相同内容消除到哪里);getchar();

		pos_address = strchr( 最近相同内容消除到哪里, *p_我方);
		
		// 《在上次相同内容被消除之后首次出现在哪里》
		// 如果出现在对方，则记录下该内容出现在对方哪个位置。
		// 以及将该内容在这份存档中正常显示。
		if (pos_address != NULL)
		{
			self->首次出现在对方哪个位置 = pos_address - 对方;
			self->内容 = *p_我方;			
		}
		// 如果未出现在对方，将索引号记为-2。（因为如果-1再+1不是后移，而是回到开头，又能搜索了。）
		// 将该内容以占位符显示。
		else
		{
			self->首次出现在对方哪个位置 = -1;
			//占位符序号 = 1 - 占位符序号;
			//self->内容 = 占位符集[占位符序号];
			self->内容 = *p_我方;
		}

		// 将该内容最近一次消除位置记录在哈希表中
		// 该值加在使用时1用以表示下次消除检查起始点
		// 不使用时保持为上次消除点位置，不需要加1，不需要到下一位
		// 因为这样这个数字与需要求解的数字是相同的。
		HashTable_create(ht, self->内容, self->首次出现在对方哪个位置);
		printf("消除的或不消除的记录于哈希表：(%c,%d)",ht->table[hash(self->内容)]->key, ht->table[hash(self->内容)]->value);getchar();
	}
	
	return true;
}