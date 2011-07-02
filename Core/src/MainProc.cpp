#include "stdafx.h"
#include "MainProc.h"

LRESULT CALLBACK MainProc(IN HWND hWnd, IN UINT msg, IN WPARAM wp, IN LPARAM lp)
{
	static NOTIFYICONDATA nid;
	static UINT uTaskbarRestart;
	static LPCTSTR const TASKBAR_MSG = TEXT("TaskbarCreated");

	switch (msg)
	{
		case WM_CREATE:
			::AddTaskbar(hWnd, &nid);
			uTaskbarRestart = ::RegisterWindowMessage(TASKBAR_MSG);

			CKeyHook::Begin(hWnd);
			break;
		case WM_TASKBAR:
			if (wp != IDR_TASKBAR)
				break;
			if (lp == WM_RBUTTONDOWN)
				::ShowTaskbarMenu(hWnd);
			break;
		case WM_COMMAND:
			switch (LOWORD(wp))
			{
				case IDM_END:
					::DestroyWindow(hWnd);
					break;
			}
			break;
		case WM_CLOSE:
			::DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			::DelTaskbar(&nid);
			CKeyHook::End();
			::PostQuitMessage(0);
			return TRUE;
		default:
			if(msg == uTaskbarRestart)	// �^�X�N�o�[�̍쐬�ʒm
			{
				DelTaskbar(&nid);
				AddTaskbar(hWnd, &nid);
			}

			return ::DefWindowProc(hWnd, msg, wp, lp);
	}
	return FALSE;
}

// �^�N�X�o�[�ɓo�^
VOID AddTaskbar(IN HWND hWnd, OUT PNOTIFYICONDATA lpNid)
{
	lpNid->cbSize = sizeof(NOTIFYICONDATA);							//�T�C�Y
	lpNid->hWnd = hWnd;
	lpNid->uID = IDR_TASKBAR;										//����ID
	lpNid->uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;				//�w�荀��
	lpNid->uCallbackMessage = WM_TASKBAR;							//�Ԃ��E�B���h�Emsg
	lpNid->hIcon = ::LoadIcon(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAIN));		//�A�C�R��
	::lstrcpy(lpNid->szTip,PROGRAM_NAME);							//�c�[���q���g

	while (! ::Shell_NotifyIcon(NIM_ADD, lpNid)) {::Sleep(1000);}	//�^�N�X�o�[�ɓo�^���܂��B
}

// �^�N�X�o�[����폜
VOID DelTaskbar(IN PNOTIFYICONDATA lpNid)
{
	::Shell_NotifyIcon(NIM_DELETE, lpNid);
	lpNid = NULL;
}

// �^�N�X�o�[ ���j���[�����
VOID ShowTaskbarMenu(IN HWND hWnd)
{
	POINT pt;

	HMENU hMenu = ::LoadMenu(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_TASKBAR));
	HMENU hSubMenu = ::GetSubMenu(hMenu, 0);
	::GetCursorPos(&pt);
	::SetForegroundWindow(hWnd);
	::TrackPopupMenu(hSubMenu, TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd, NULL);
	::DestroyMenu(hMenu);
}