#pragma once

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <Digitalv.h>
//---------------음악을 사용할 헤더추가


class CSound
{
	MCI_OPEN_PARMS      mciOpen; //파일을 로드

	MCI_PLAY_PARMS       mciPlay; //파일을 재생

	MCI_STATUS_PARMS   mciStatus; //파일의 상태

	UINT wDeviceID = 0;  //재생위 위치값 0이면 처음으로돌려줌

	DWORD Result; //결과값
	
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

