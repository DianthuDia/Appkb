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
	if( nCode < 0 || nCode == HC_NOREMOVE )		// �t�b�N���Ă悢���`�F�b�N����
		return ::CallNextHookEx( m_hHook, nCode, wp, lp );

	if(OnHook(wp, lp))
		return TRUE;

	// �������Ă�MSG�������Ȃ��ꍇ
	return ::CallNextHookEx( m_hHook, nCode, wp, lp );
}
#undef _CHOOK_CLASS_NAME
#endif

// �t�b�N���̏���(�����ɌŗL����������)
// (return true�œ��͂�D�����)
bool CKeyHook::OnHook(IN const WPARAM /*wp*/, IN const LPARAM lp)
{
	const static DWORD IME_OFF_SCANCODE	= 113; // �p��
	const static DWORD IME_ON_SCANCODE	= 114; // ����
	
	// ���݂�ForegroundWindow����IME�n���h���擾
	const DWORD threadId = ::GetWindowThreadProcessId(::GetForegroundWindow(), NULL);
	::AttachThreadInput(::GetCurrentThreadId(), threadId, TRUE);
	const HWND hWndIME = ::ImmGetDefaultIMEWnd( ::GetFocus() );
	::AttachThreadInput(::GetCurrentThreadId(), threadId, FALSE);
	
	// �Y���L�[�̃`�F�b�N
	const DWORD scanCode = ((LPKBDLLHOOKSTRUCT)lp)->scanCode;
	if(scanCode == IME_OFF_SCANCODE)
		::SendMessage(hWndIME, WM_IME_CONTROL, IMC_SETOPENSTATUS, FALSE);
	else if(scanCode == IME_ON_SCANCODE)
		::SendMessage(hWndIME, WM_IME_CONTROL, IMC_SETOPENSTATUS, TRUE);
	else
		return false;	// �Y�����Ȃ��̂ŁA�t�b�N���Ȃ�

	return true;	// �D�����
}