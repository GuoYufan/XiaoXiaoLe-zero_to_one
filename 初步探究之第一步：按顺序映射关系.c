#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <哈希表.c>
#define LETTER_AVAILABLE 10

typedef struct 字符串内当前位置情况 TheChar;
typedef struct 一段字符串情况 TheWord;
typedef struct 字符消消乐 Game;

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
	short* 可消除内容首次出现在对方位置列表;
	short 可消除数量;
	TheChar** 每个字符情况;
	
	char* 名称;
};


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
	
	self->名称 = malloc(sizeof (char ) * strlen(name)+1);
	strcpy(self->名称, name);
}



// 记录该字符串中每个字符情况（相对于对手）
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
			最近相同内容消除到哪里 = 对方 + *哈希表查找结果;
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
		// 如果未出现在对方，将索引号记为-1。
		// 将该内容以占位符显示。
		else
		{
			self->首次出现在对方哪个位置 = -1;
			//占位符序号 = 1 - 占位符序号;
			//self->内容 = 占位符集[占位符序号];
			self->内容 = *p_我方;
		}

		// 将该内容最近一次消除位置记录在哈希表中
		// 该值加1用以表示下次消除检查起始点
		HashTable_create(ht, self->内容, self->首次出现在对方哪个位置 + 1);
		printf("消除的或不消除的记录于哈希表：(%c,%d)",ht->table[hash(self->内容)]->key, ht->table[hash(self->内容)]->value);getchar();
	}
	
	return true;
}

// 显示该字符情况
void TheChar_show(TheChar *self)
{
	printf("我方位置%d字符%c上次消除后首次出现在对方哪个位置:%d\n",
		self->在自身哪个位置,
		self->内容, 
		self->首次出现在对方哪个位置);
}

void TheWord_show_内容(TheWord *self)
{
	printf("《显示名称为:%s 字符串内容》", self->名称);
	puts(self->内容);
}


void TheWord_show_每个字符情况(TheWord *self)
{
	TheChar** p_每个字符情况 = self->每个字符情况;

	// 显示这一波每个字符情况
	printf("《在字符串%s中》\n", self->内容);
	for (short i=0; i < self->长度; i++ )
	{
		TheChar_show(*p_每个字符情况);
		p_每个字符情况++;
	}
	
}
void TheWord_update(TheWord* self)
{
	// 将这一波每个字符情况被所在字符串所需要的信息收集到后者中
	TheChar** p_每个字符情况=self->每个字符情况;	
	for (short i=0; i < self->长度; i++, p_每个字符情况++)
	{
		// 如果当前字符可消除
		if ( (*p_每个字符情况) -> 首次出现在对方哪个位置 != -1)
		{
			self->可消除内容在自身位置列表[self->可消除数量] = (*p_每个字符情况)->在自身哪个位置;
			self->可消除内容首次出现在对方位置列表[self->可消除数量] = (*p_每个字符情况)->首次出现在对方哪个位置;
			self->可消除内容列表[self->可消除数量] = (*p_每个字符情况)->内容;
			self->可消除数量++;
		}	
	}
}


void TheWord_show_可消除内容在自身位置与可消除内容(TheWord* self)
{
	//显示可消除内容在自身位置与内容相关信息
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
	
}


void 统一free(TheWord* self)
{
	for (short i=0; i<self->长度; i++)
		free(self->每个字符情况[i]);
	free(self->每个字符情况);
	free(self->可消除内容列表);
	free(self->可消除内容在自身位置列表);
	free(self->可消除内容首次出现在对方位置列表);
	free(self->名称);
	free(self);
}

char 获取随机字符(char 随机范围最小值, char 随机范围最大值)
{
	return ( char ) ( rand()%(随机范围最大值 - 随机范围最小值 + 1) + 随机范围最小值 + 97 );
}


void 产生任意长度的任意字符串(char* word, char minLen, char maxLen)
{
	char 随机长度 = rand()%(maxLen - minLen + 1) + minLen;
	for (char i=0, 随机字符; i<随机长度; i++)
	{
		随机字符 = 获取随机字符(0, LETTER_AVAILABLE);
		*word = 随机字符;
		word++;
	}
	*word = '\0';
}

bool 判断是否在概率内(float 概率, char 随机数, char 随机数范围)
{
	return 随机数 <= 概率 * 随机数范围;
	
}

void 字符串任何部分替换成任意新内容或不替换(char* result, char 替换部分最大长度)
{
	char 随机替换长度_对方 = -1, 随机替换长度_我方 = -1;
	char 随机数 = 101;
	float 设置替换概率 = 0.5;
	
	while (*result != '\0')
	{
		随机数 = rand()%100 + 1;
	
		if (!判断是否在概率内(设置替换概率, 随机数, 100))
		{
			result ++;
			continue;
		}
		
		随机替换长度_对方 = rand() % (替换部分最大长度 - 1 + 1) + 1;
		随机替换长度_我方 = rand() % (替换部分最大长度 - 1 + 1) + 1;
		
		strcpy(result + 随机替换长度_我方, result + 随机替换长度_对方);
		
		for (char i=0; i<随机替换长度_我方; i++)
		{
			*result = 获取随机字符(0, LETTER_AVAILABLE);
			result ++;
		}
	}
	result = '\0';
	
}


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


void main()
{
	srand(time(NULL));
	TheWord *leftWord, *rightWord;
	leftWord=(TheWord*) malloc(sizeof (TheWord));
	rightWord=(TheWord*) malloc(sizeof (TheWord));

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
	TheWord_init(rightWord,"fhfgdjgde", "右");

	TheWord_show_内容(leftWord);
	TheWord_show_内容(rightWord);
	
	//TheWord_run(leftWord, rightWord->内容);
	//puts("\n");
	TheWord_run(rightWord, leftWord->内容);

	
	统一free(leftWord);
	统一free(rightWord);
}