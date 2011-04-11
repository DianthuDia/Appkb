#pragma once

#include "Resource.h"
#include "init/typedef.h"

// ※1exeに1フックのみ
class CHook
{
public:
	static bool Begin(const IN INT idHook, bool (*fpOnHook)(IN const WPARAM wp,IN const LPARAM lp));
	static VOID End();
private:
	static INT m_idHook;	// フックモード
	static HHOOK m_hHook;	// フックハンドル
	static bool (*m_fpOnHook)(IN const WPARAM wp,IN const LPARAM lp);	// フック時の処理(return trueで入力を奪い取る)

	static LRESULT CALLBACK HookProc(IN const INT nCode, IN const WPARAM wp, IN const LPARAM lp);
};
