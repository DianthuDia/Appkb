#pragma once
// ���������[�N���o

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <cstdlib>	// �K�v
	#include <crtdbg.h>
	#define _CRTDBG_MAP_ALLOC
	#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif	// _DEBUG
