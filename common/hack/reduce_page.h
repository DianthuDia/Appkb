#pragma once
// 1ページ節約

#ifndef _DEBUG
	#pragma comment(linker, "/merge:.data=.text")
	#pragma comment(linker, "/merge:.rdata=.text")
	#pragma comment(linker, "/section:.text,erw")
#endif	// _DEBUG