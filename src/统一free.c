#include <stdlib.h>
#include "../include/XiaoXiaoLe.h"

void 统一free(TheWord* self)
{
	for (short i = 0; i < self->长度; i++)
		free(self->每个字符情况[i]);
	free(self->每个字符情况);
	free(self->可消除内容列表);
	free(self->可消除内容在自身位置列表);
	free(self->可消除内容首次出现在对方位置列表);
	free(self->名称);
	free(self);
};