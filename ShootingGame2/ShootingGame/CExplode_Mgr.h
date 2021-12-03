#pragma once
#include "CExplode.h"

class CExplode_Mgr 
{


	HWND m_hWnd;
	//vector<Image*> m_ImgList;       //캐릭터 별 애니없는 이미지 로딩 변수
	CExplode m_Explode;       //Player 하나
//	float	   m_RandTic;           //주기적으로 말들의 속도를 변경 
public:
	CExplode_Mgr();
	~CExplode_Mgr();

public:
	void CEM_Init(HWND a_hWnd);		//초기화 함수
	void CEM_ReSetPos();
	void CEM_Update(double a_DeltaTime, RECT* a_rt = NULL, bool a_isRaceStart = false);	//게임의 연산 담당부분
	void CEM_Render(HDC a_hdc);	//게임의 그리기 부분
	void CEM_Destroy();
};

extern CExplode_Mgr g_ExplodeMgr;

