#pragma once

#include "Resource.h"
#include "init/typedef.h"

// ��1exe��1�t�b�N�̂�
class CHook
{
public:
	static bool Begin(const IN INT idHook, bool (*fpOnHook)(IN const WPARAM wp,IN const LPARAM lp));
	static VOID End();
private:
	static INT m_idHook;	// �t�b�N���[�h
	static HHOOK m_hHook;	// �t�b�N�n���h��
	static bool (*m_fpOnHook)(IN const WPARAM wp,IN const LPARAM lp);	// �t�b�N���̏���(return true�œ��͂�D�����)

	static LRESULT CALLBACK HookProc(IN const INT nCode, IN const WPARAM wp, IN const LPARAM lp);
};
