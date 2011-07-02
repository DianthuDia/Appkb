#pragma once

#include "../../common/typedef.h"
#include "Resource.h"

#if 1 // CKeyHook
#define _CHOOK_CLASS_NAME CKeyHook		// �ϐ�1 �N���X��
#define _CHOOK_HOOK_ID WH_KEYBOARD_LL		// �ϐ�2 �t�b�NID
#define HOOKED_SCANCODE WM_USER+1				// �t�b�N����WM_SETTEXT#WPARAM
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
