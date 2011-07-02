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
//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);	//�f�o�b�N������ł͂Ȃ�Window�ŕ\��
//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);	//�f�o�b�N������ł͂Ȃ�Window�ŕ\��
//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);	//�f�o�b�N������ł͂Ȃ�Window�ŕ\��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
#else	// _DEBUG
	_callfunclist(__xi_a, __xi_z);		// atexit�g�p�̈�
	_callfunclist(__xc_a, __xc_z);		// atexit�g�p�̈�
#endif	// _DEBUG

	//---------------------���d�N���h�~����-------------------------------
	HANDLE hMSP = ::CreateMutex(NULL, TRUE, PROGRAM_NAME);
	/* ���łɋN�����Ă��邩���� */
	if(::GetLastError() == ERROR_ALREADY_EXISTS)	// ���łɋN�����Ă���
	{
		::ReleaseMutex(hMSP);
		::CloseHandle(hMSP);

		#ifdef _DEBUG
			return static_cast<INT>(-1);	// ���ꂪ�����Ƃ�����ƃf�X�g���N�^�ĂׂȂ�
		#else
			::ExitProcess(static_cast<UINT>(-1));	// 
		#endif //!_DEBUG
	}
	//---------------------------------------------------------------------

//	CONST HWND hWnd = ::CreateDialog(::GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_MAIN), NULL , DlgMainProc);

	WNDCLASS MainWC;

	MainWC.style = CS_HREDRAW | CS_VREDRAW/*| CS_DBLCLKS*/;
	MainWC.lpfnWndProc = MainProc;			//�v���V�[�W����
	MainWC.cbClsExtra = 0;
	MainWC.cbWndExtra = 0;
	MainWC.hInstance = ::GetModuleHandle(NULL);	//�C���X�^���X
	MainWC.hIcon = ::LoadIcon(MainWC.hInstance,MAKEINTRESOURCE(IDI_MAIN));
	MainWC.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	MainWC.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_DESKTOP+1);
	MainWC.lpszMenuName = NULL;					//���j���[��
	MainWC.lpszClassName = PROGRAM_NAME;

	::RegisterClass(&MainWC);

	::CreateWindow(
		MainWC.lpszClassName,
		MainWC.lpszClassName,	//�^�C�g���o�[�ɂ��̖��O���\������܂�
		WS_DISABLED,	//�E�B���h�E�̎��
		CW_USEDEFAULT,			//X���W
		CW_USEDEFAULT,			//Y���W
		CW_USEDEFAULT,			//��
		CW_USEDEFAULT,			//����
		NULL,					//�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
		NULL,					//���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
		MainWC.hInstance,		//�C���X�^���X�n���h��
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
	
	///---------------------���d�N���h�~����-------------------------------
	::ReleaseMutex(hMSP);
	::CloseHandle(hMSP);
	//---------------------------------------------------------------------

	::UnregisterClass(MainWC.lpszClassName, MainWC.hInstance);
#ifdef _DEBUG
	return static_cast<INT>(msg.wParam);	// ���ꂪ�����Ƃ�����ƃf�X�g���N�^�ĂׂȂ�
#else
	_callfunclist(__exit_a, __exit_z);				// atexit�g�p�̈�
	::HeapFree(::GetProcessHeap(),0,__exit_a);		// atexit�g�p�̈�

	::ExitProcess(static_cast<INT>(msg.wParam));	// ���̊֐��͂��Ȃ�댯
#endif //!_DEBUG
}

