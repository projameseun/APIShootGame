#pragma once
#include "CAnimation.h"


class CMyMain
{
	ULONG_PTR m_gdiplusToken = NULL;

	//BackDC 생성용변수 
	HDC	m_hBackDC = NULL;
	HBITMAP m_hBackBitmap = NULL;
	//BackDC 생성용변수 
	HWND	m_hWnd = NULL;
	RECT m_Rect;


	//-------- 델타 타임을 얻기 위한 변수
	double m_DeltaTime;
	DWORD m_LastTime = 0;
	DWORD m_CurTime = 0;
	//-------- 델타 타임을 얻기 위한 변수


	//--------소리을 위한 변수들 
	DWORD Sound1, Sound2;

	int m_Count; //test
	int m_EndCount; //game over
	int m_StartCount; //game over
	//--------소리을 위한 변수들 

public:
	vector<CAnimation*> m_CharAniList;
public:
	CMyMain();
	~CMyMain();

public:
	void MainInit(HWND hWnd);
	void MainUpdate(HWND hWnd);
	void MainRender(HWND hWnd);
	void MainDestroy();

	//void ReSetGame();    
	//게임 초기화 
	static void NextLevel();	//다음단계
	static void ReSetGame();	//게임초기화 
	void BossRest();
};

extern CMyMain g_CMyMain;

