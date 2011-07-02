#pragma once

#include "../../common/typedef.h"
#include "Resource.h"

#if 1 // CKeyHook
#define _CHOOK_CLASS_NAME CKeyHook		// 変数1 クラス名
#define _CHOOK_HOOK_ID WH_KEYBOARD_LL		// 変数2 フックID
#define HOOKED_SCANCODE WM_USER+1				// フック時のWM_SETTEXT#WPARAM
class _CHOOK_CLASS_NAME
{
public:
	static bool Begin(const IN HWND hWndRecv, const IN INT idHook = _CHOOK_HOOK_ID);
	static VOID End();
private:
	_CHOOK_CLASS_NAME();

	static HWND m_hWndRecv;
	static HHOOK m_hHook;
	
	static LRESULT CALLBACK HookProc(IN const INT nCode, IN const WPARAM wp, IN const LPARAM lp);
	static bool OnHook(IN const WPARAM wp, IN const LPARAM lp);
};
#undef _CHOOK_CLASS_NAME
#undef _CHOOK_HOOK_ID
#endif
