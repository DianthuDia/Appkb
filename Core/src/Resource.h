#pragma once
/*
[プリフィックス]	[リソースの種類]						[有効範囲]
IDR_				多重リソース							1 ～ 0x6FFF
IDD_				ダイアログ テンプレート				1 ～ 0x6FFF
 
IDC_、IDI_、IDB_	カーソル、アイコン、ビットマップ	1 ～ 0x6FFF
IDS_、IDP_			文字列									1 ～ 0x7FFF
 
ID_					コマンド								0x8000 ～ 0xDFFF
 
IDC_				コントロール							8 ～ 0xDFFF
*/



#define PROGRAM_NAME	TEXT("AppKb")

// 多重リソース識別
#define IDR_TASKBAR			1
//#define IDR_MENU_MAIN					100
//#define IDR_TRACKMENU_DRAW				101
//#define IDR_TRACKMENU_DRAW_ARROW		102

//#define IDR_ACCEL_MAIN			100
//#define IDR_ACCEL_DRAW			101

//#define IDR_TOOLBAR_DRAW_COMMON				200
//#define IDR_TOOLBAR_EVENT_LIST				201

// ダイアログ テンプレート
#define IDD_MAIN		1

// カーソル、アイコン、ビットマップ
#define IDI_MAIN				1
#define IDI_SMALL				2

// 文字列
//#define IDS_WIZARD_WATERFALL				1
//#define IDS_WIZARD_SPIRAL					2
//#define IDS_TREE_EVENT_LIST					3

// コントロール(ダイヤログの)
// 共通
#define IDC_STATIC -1

#define IDC_COMBO_NIC			1
#define IDC_EDIT_LIMIT			2
#define IDC_EDIT_DATE			3
#define IDC_EDIT_CYCLE			4
#define IDC_BUTTON_APPLY		5

// ツールバーのボタン
//#define IDC_BUTTON_TOOLBAR_START			100
//#define IDC_BUTTON_EL_ADD					101
//#define IDC_BUTTON_EL_DELETE				102

// メニューID								
#define IDM_END						0x8000
//#define IDM_FILE_LOAD				0x8001
//#define IDM_FILE_SAVE				0x8002
//#define IDM_FILE_EXIT				0x8003
//#define IDM_HELP					0x8004
