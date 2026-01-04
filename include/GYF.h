#include "GYF_types.h"

struct 调试模式
{
	bool DoesMsgPrint;
	bool DoesTest;
};

extern GYF_Debug_Mode *gyf_debug_mode;

void GYF_Debug_Mode_init(GYF_Debug_Mode *self);