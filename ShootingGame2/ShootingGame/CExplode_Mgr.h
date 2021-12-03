#pragma once
#include "CExplode.h"

class CExplode_Mgr 
{


	HWND m_hWnd;
	//vector<Image*> m_ImgList;       //ĳ���� �� �ִϾ��� �̹��� �ε� ����
	CExplode m_Explode;       //Player �ϳ�
//	float	   m_RandTic;           //�ֱ������� ������ �ӵ��� ���� 
public:
	CExplode_Mgr();
	~CExplode_Mgr();

public:
	void CEM_Init(HWND a_hWnd);		//�ʱ�ȭ �Լ�
	void CEM_ReSetPos();
	void CEM_Update(double a_DeltaTime, RECT* a_rt = NULL, bool a_isRaceStart = false);	//������ ���� ���κ�
	void CEM_Render(HDC a_hdc);	//������ �׸��� �κ�
	void CEM_Destroy();
};

extern CExplode_Mgr g_ExplodeMgr;

