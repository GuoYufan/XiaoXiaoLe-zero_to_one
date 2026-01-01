#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LETTER_AVAILABLE 10


char 获取随机字符(char 随机范围最小值, char 随机范围最大值)
{
	return ( char ) ( rand()%(随机范围最大值 - 随机范围最小值 + 1) + 随机范围最小值 + 97 );
}


// 以随机的方式生成字符串
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


// 以随机的方式替换字符串
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