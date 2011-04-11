#include "stdafx.h"
#include "CHook.h"

#pragma data_seg( ".CHook" )
	INT		CHook::m_idHook = WH_MIN;
	HHOOK	CHook::m_hHook = NULL;
	bool (*CHook::m_fpOnHook)(IN const WPARAM wp,IN const LPARAM lp) = NULL;
#pragma data_seg()

bool CHook::Begin(const IN INT idHook, bool (*fpOnHook)(IN const WPARAM wp, IN const LPARAM lp))
{
	m_idHook = idHook;
	m_fpOnHook = fpOnHook;

	return NULL != (m_hHook = ::SetWindowsHookEx( m_idHook,
		static_cast<HOOKPROC>(CHook::HookProc), ::GetModuleHandle(NULL), NULL));
}

VOID CHook::End() { ::UnhookWindowsHookEx( m_hHook ); }

LRESULT CALLBACK CHook::HookProc(IN const INT nCode,IN const WPARAM wp, IN const LPARAM lp)
{
	if( nCode < 0)		// フックしてよいかチェックする
		return ::CallNextHookEx( m_hHook, nCode, wp, lp );

	if(m_fpOnHook(wp, lp))
		return TRUE;

	// 処理してもMSGを消さない場合
	return ::CallNextHookEx( m_hHook, nCode, wp, lp );
}
