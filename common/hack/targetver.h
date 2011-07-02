#pragma once
// 下で指定された定義の前に対象プラットフォームを指定しなければならない場合、以下の定義を変更してください。
// 異なるプラットフォームに対応する値に関する最新情報については、MSDN を参照してください。
#define _WIN32_IE			0x0200	// 95,NT でのデフォIE

#ifdef _UNICODE
	#define WINVER			0x0400
	#define _WIN32_WINNT	0x0400	// NTから
#else //!_UNICODE
	#define WINVER			0x0400
	#define _WIN32_WINDOWS	0x0400	// 95から
#endif	// !_UNICODE
