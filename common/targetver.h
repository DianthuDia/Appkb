#pragma once
// ���Ŏw�肳�ꂽ��`�̑O�ɑΏۃv���b�g�t�H�[�����w�肵�Ȃ���΂Ȃ�Ȃ��ꍇ�A�ȉ��̒�`��ύX���Ă��������B
// �قȂ�v���b�g�t�H�[���ɑΉ�����l�Ɋւ���ŐV���ɂ��ẮAMSDN ���Q�Ƃ��Ă��������B
#define _WIN32_IE			0x0200	// 95,NT �ł̃f�t�HIE

#ifdef _UNICODE
	#define WINVER			0x0400
	#define _WIN32_WINNT	0x0400	// NT����
#else //!_UNICODE
	#define WINVER			0x0400
	#define _WIN32_WINDOWS	0x0400	// 95����
#endif	// !_UNICODE
