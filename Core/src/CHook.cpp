#include "stdafx.h"
#include "CHook.h"

#pragma comment(linker, "/Section:.CHook,rws")

#if 1 // CKeyHook
#define _CHOOK_CLASS_NAME CKeyHook
#pragma data_seg( ".CHook" )
	HWND	_CHOOK_CLASS_NAME::m_hWndRecv = NULL;
	HHOOK	_CHOOK_CLASS_NAME::m_hHook = NULL;
#pragma data_seg()

bool _CHOOK_CLASS_NAME::Begin(const IN HWND hWndRecv, const IN INT idHook)
{
	m_hWndRecv = hWndRecv;
	return NULL != (m_hHook = ::SetWindowsHookEx( idHook,
		static_cast<HOOKPROC>(_CHOOK_CLASS_NAME::HookProc), ::GetModuleHandle(NULL), 0));
}
VOID _CHOOK_CLASS_NAME::End() { ::UnhookWindowsHookEx( m_hHook ); }
LRESULT CALLBACK _CHOOK_CLASS_NAME::HookProc(IN const INT nCode,IN const WPARAM wp, IN const LPARAM lp)
{
	if( nCode < 0 || nCode == HC_NOREMOVE )		// フックしてよいかチェックする
		return ::CallNextHookEx( m_hHook, nCode, wp, lp );

	if(OnHook(wp, lp))
		return TRUE;

	// 処理してもMSGを消さない場合
	return ::CallNextHookEx( m_hHook, nCode, wp, lp );
}
#undef _CHOOK_CLASS_NAME
#endif

// フック時の処理(ここに固有処理をかく)
// (return trueで入力を奪い取る)
bool CKeyHook::OnHook(IN const WPARAM /*wp*/, IN const LPARAM lp)
{
	const static DWORD IME_OFF_SCANCODE	= 113; // 英数
	const static DWORD IME_ON_SCANCODE	= 114; // かな
	
	// 現在のForegroundWindowからIMEハンドル取得
	const DWORD threadId = ::GetWindowThreadProcessId(::GetForegroundWindow(), NULL);
	::AttachThreadInput(::GetCurrentThreadId(), threadId, TRUE);
	const HWND hWndIME = ::ImmGetDefaultIMEWnd( ::GetFocus() );
	::AttachThreadInput(::GetCurrentThreadId(), threadId, FALSE);
	
	// 該当キーのチェック
	const DWORD scanCode = ((LPKBDLLHOOKSTRUCT)lp)->scanCode;
	if(scanCode == IME_OFF_SCANCODE)
		::SendMessage(hWndIME, WM_IME_CONTROL, IMC_SETOPENSTATUS, FALSE);
	else if(scanCode == IME_ON_SCANCODE)
		::SendMessage(hWndIME, WM_IME_CONTROL, IMC_SETOPENSTATUS, TRUE);
	else
		return false;	// 該当しないので、フックしない

	return true;	// 奪い取る
}