#pragma once
#include "CAnimation.h"


class CMyMain
{
	ULONG_PTR m_gdiplusToken = NULL;

	//BackDC �����뺯�� 
	HDC	m_hBackDC = NULL;
	HBITMAP m_hBackBitmap = NULL;
	//BackDC �����뺯�� 
	HWND	m_hWnd = NULL;
	RECT m_Rect;


	//-------- ��Ÿ Ÿ���� ��� ���� ����
	double m_DeltaTime;
	DWORD m_LastTime = 0;
	DWORD m_CurTime = 0;
	//-------- ��Ÿ Ÿ���� ��� ���� ����


	//--------�Ҹ��� ���� ������ 
	DWORD Sound1, Sound2;

	int m_Count; //test
	int m_EndCount; //game over
	int m_StartCount; //game over
	//--------�Ҹ��� ���� ������ 

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
	//���� �ʱ�ȭ 
	static void NextLevel();	//�����ܰ�
	static void ReSetGame();	//�����ʱ�ȭ 
	void BossRest();
};

extern CMyMain g_CMyMain;

