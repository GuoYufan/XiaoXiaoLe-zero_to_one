#include <stdbool.h>
#include "XiaoXiaoLe_types.h"
#include "哈希表_types.h"

struct 字符串内当前位置情况
{
	// 该索引到的内容如果出现在对方，则正常显示
	// 如果不出现在对方，则显示为占位符	
	char 内容;
	short 在自身哪个位置;
	short 首次出现在对方哪个位置;	
};


struct 一段字符串情况
{
	char* 内容;
	short 长度;
	short* 可消除内容在自身位置列表;	
	char* 可消除内容列表;
	// 首次出现在对方位置：以相同内容最近一次消除点的下一位作为检查起点
	short* 可消除内容首次出现在对方位置列表;
	short 可消除数量;
	TheChar** 每个字符情况;
	short 记录了几个字符情况;
	
	char* 名称;
};


// TheChar
bool TheChar_update_按顺序映射关系(TheWord* 我方, char* 对方, HashTable* ht);
// 显示该字符情况
void TheChar_show(TheChar *self);

// TheWord
void TheWord_init(TheWord *self, const char* content, const char* name);
void TheWord_init_random(TheWord* self, TheWord* opponent);
void TheWord_update(TheWord* self);
void TheWord_show_内容(TheWord *self);
void TheWord_show_每个字符情况(TheWord *self);
void TheWord_show_可消除内容在自身位置与可消除内容(TheWord* self);
void TheWord_show_可消除内容在自身位置与首次出现在对方位置的映射表(TheWord* self);
void TheWord_show_单独处理首次出现在对方位置信息(TheWord *self);
void TheWord_run(TheWord* self, char* 对方内容);

// 随机生成字符串
char 获取随机字符(char 随机范围最小值, char 随机范围最大值);
void 产生任意长度的任意字符串(char* word, char minLen, char maxLen);
bool 判断是否在概率内(float 概率, char 随机数, char 随机数范围);
void 字符串任何部分替换成任意新内容或不替换(char* result, char 替换部分最大长度);


void 统一free(TheWord* self);
