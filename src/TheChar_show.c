#include <stdio.h>
#include "../include/XiaoXiaoLe.h"

// 显示该字符情况
void TheChar_show(TheChar *self)
{
	printf("我方位置%d字符%c上次消除后首次出现在对方哪个位置:%d\n",
		self->在自身哪个位置,
		self->内容, 
		self->首次出现在对方哪个位置);
};