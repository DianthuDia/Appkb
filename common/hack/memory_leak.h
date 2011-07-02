#pragma once
// メモリリーク検出

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <cstdlib>	// 必要
	#include <crtdbg.h>
	#define _CRTDBG_MAP_ALLOC
	#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif	// _DEBUG
