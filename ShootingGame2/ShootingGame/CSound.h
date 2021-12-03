#pragma once

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <Digitalv.h>
//---------------������ ����� ����߰�


class CSound
{
	MCI_OPEN_PARMS      mciOpen; //������ �ε�

	MCI_PLAY_PARMS       mciPlay; //������ ���

	MCI_STATUS_PARMS   mciStatus; //������ ����

	UINT wDeviceID = 0;  //����� ��ġ�� 0�̸� ó�����ε�����

	DWORD Result; //�����
	
public:
	CSound();
	~CSound();
	
public:
	DWORD InitWAV(HWND hWnd, LPCTSTR lpszWave);
	void UpdateWav(int Play_Num);
	void ResetWav(int Player_Num);
	void DestroyWav();
};

extern CSound g_Sound;

