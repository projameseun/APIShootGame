#pragma once
#include "CCharacter.h"

//class CAnimation;
class CHero;
class CCharacter_Mgr 
{
	

//	vector<Image*> m_ImgList;       //캐릭터 별 애니없는 이미지 로딩 변수
public:
	CCharacter m_CharList;       //가짜 player dead 부분
	HWND m_hWnd;
	RECT m_bRT;
	Image *m_Girl;
public:
	CCharacter_Mgr();
	~CCharacter_Mgr();

public:
	void CM_Init(HWND a_hWnd);		//초기화 함수
	void CM_ReSetPos();
	void CM_Update(HDC a_hdc,double a_DeltaTime, RECT* a_rt = NULL, bool a_isRaceStart = false);	//게임의 연산 담당부분
	void CM_Render(HDC a_hdc,double a_DeltaTime);	//게임의 그리기 부분
	void CM_RealUpdate(HDC a_hdc, double a_DeltaTime, RECT* a_rt = NULL, bool a_isRealStart = false);

	void CM_Destroy();


	void BossM_ReSetPos(float a_DeltaTime, HWND a_hWnd);
	void BossM_Update(HDC a_hdc, double a_DeltaTime,CHero &a_Hero);	//게임의 연산 담당부분
	void BossM_Render(HDC a_hdc, double a_DeltaTime);	//게임의 그리기 부분
	

};

extern CCharacter_Mgr  g_Char_Mgr;