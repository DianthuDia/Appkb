#include "stdafx.h"
#include "WinMain.h"

#ifdef _DEBUG
	#include <tchar.h>
	INT WINAPI _tWinMain(IN const HINSTANCE, IN const HINSTANCE, IN LPTSTR const, IN const INT)
#else
	#include "../../common/hack/atexit.h"
	void WINAPI WinMainCRTStartup()
#endif //!_DEBUG
{
#ifdef _DEBUG
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);	//デバック文字列ではなくWindowで表示
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);	//デバック文字列ではなくWindowで表示
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);	//デバック文字列ではなくWindowで表示
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
#else	// _DEBUG
	_callfunclist(__xi_a, __xi_z);		// atexit使用の為
	_callfunclist(__xc_a, __xc_z);		// atexit使用の為
#endif	// _DEBUG

	//---------------------多重起動防止処理-------------------------------
	HANDLE hMSP = ::CreateMutex(NULL, TRUE, PROGRAM_NAME);
	/* すでに起動しているか判定 */
	if(::GetLastError() == ERROR_ALREADY_EXISTS)	// すでに起動している
	{
		::ReleaseMutex(hMSP);
		::CloseHandle(hMSP);

		#ifdef _DEBUG
			return static_cast<INT>(-1);	// これが無いときちんとデストラクタ呼べない
		#else
			::ExitProcess(static_cast<UINT>(-1));	// 
		#endif //!_DEBUG
	}
	//---------------------------------------------------------------------

//	CONST HWND hWnd = ::CreateDialog(::GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_MAIN), NULL , DlgMainProc);

	WNDCLASS MainWC;

	MainWC.style = CS_HREDRAW | CS_VREDRAW/*| CS_DBLCLKS*/;
	MainWC.lpfnWndProc = MainProc;			//プロシージャ名
	MainWC.cbClsExtra = 0;
	MainWC.cbWndExtra = 0;
	MainWC.hInstance = ::GetModuleHandle(NULL);	//インスタンス
	MainWC.hIcon = ::LoadIcon(MainWC.hInstance,MAKEINTRESOURCE(IDI_MAIN));
	MainWC.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	MainWC.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_DESKTOP+1);
	MainWC.lpszMenuName = NULL;					//メニュー名
	MainWC.lpszClassName = PROGRAM_NAME;

	::RegisterClass(&MainWC);

	::CreateWindow(
		MainWC.lpszClassName,
		MainWC.lpszClassName,	//タイトルバーにこの名前が表示されます
		WS_DISABLED,	//ウィンドウの種類
		CW_USEDEFAULT,			//X座標
		CW_USEDEFAULT,			//Y座標
		CW_USEDEFAULT,			//幅
		CW_USEDEFAULT,			//高さ
		NULL,					//親ウィンドウのハンドル、親を作るときはNULL
		NULL,					//メニューハンドル、クラスメニューを使うときはNULL
		MainWC.hInstance,		//インスタンスハンドル
		NULL);

	MSG msg;
	msg.wParam = 0;
	while(::GetMessage(&msg, NULL, 0, 0))
	{
//		if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
//		}
	}
	
	///---------------------多重起動防止処理-------------------------------
	::ReleaseMutex(hMSP);
	::CloseHandle(hMSP);
	//---------------------------------------------------------------------

	::UnregisterClass(MainWC.lpszClassName, MainWC.hInstance);
#ifdef _DEBUG
	return static_cast<INT>(msg.wParam);	// これが無いときちんとデストラクタ呼べない
#else
	_callfunclist(__exit_a, __exit_z);				// atexit使用の為
	::HeapFree(::GetProcessHeap(),0,__exit_a);		// atexit使用の為

	::ExitProcess(static_cast<INT>(msg.wParam));	// この関数はかなり危険
#endif //!_DEBUG
}

