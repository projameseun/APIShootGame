#pragma once
#include "CCharacter.h"

//class CAnimation;
class CHero;
class CCharacter_Mgr 
{
	

//	vector<Image*> m_ImgList;       //ĳ���� �� �ִϾ��� �̹��� �ε� ����
public:
	CCharacter m_CharList;       //��¥ player dead �κ�
	HWND m_hWnd;
	RECT m_bRT;
	Image *m_Girl;
public:
	CCharacter_Mgr();
	~CCharacter_Mgr();

public:
	void CM_Init(HWND a_hWnd);		//�ʱ�ȭ �Լ�
	void CM_ReSetPos();
	void CM_Update(HDC a_hdc,double a_DeltaTime, RECT* a_rt = NULL, bool a_isRaceStart = false);	//������ ���� ���κ�
	void CM_Render(HDC a_hdc,double a_DeltaTime);	//������ �׸��� �κ�
	void CM_RealUpdate(HDC a_hdc, double a_DeltaTime, RECT* a_rt = NULL, bool a_isRealStart = false);

	void CM_Destroy();


	void BossM_ReSetPos(float a_DeltaTime, HWND a_hWnd);
	void BossM_Update(HDC a_hdc, double a_DeltaTime,CHero &a_Hero);	//������ ���� ���κ�
	void BossM_Render(HDC a_hdc, double a_DeltaTime);	//������ �׸��� �κ�
	

};

extern CCharacter_Mgr  g_Char_Mgr;