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
			if(msg == uTaskbarRestart)	// タスクバーの作成通知
			{
				DelTaskbar(&nid);
				AddTaskbar(hWnd, &nid);
			}

			return ::DefWindowProc(hWnd, msg, wp, lp);
	}
	return FALSE;
}

// タクスバーに登録
VOID AddTaskbar(IN HWND hWnd, OUT PNOTIFYICONDATA lpNid)
{
	lpNid->cbSize = sizeof(NOTIFYICONDATA);							//サイズ
	lpNid->hWnd = hWnd;
	lpNid->uID = IDR_TASKBAR;										//識別ID
	lpNid->uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;				//指定項目
	lpNid->uCallbackMessage = WM_TASKBAR;							//返すウィンドウmsg
	lpNid->hIcon = ::LoadIcon(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAIN));		//アイコン
	::lstrcpy(lpNid->szTip,PROGRAM_NAME);							//ツールヒント

	while (! ::Shell_NotifyIcon(NIM_ADD, lpNid)) {::Sleep(1000);}	//タクスバーに登録します。
}

// タクスバーから削除
VOID DelTaskbar(IN PNOTIFYICONDATA lpNid)
{
	::Shell_NotifyIcon(NIM_DELETE, lpNid);
	lpNid = NULL;
}

// タクスバー メニューを作る
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