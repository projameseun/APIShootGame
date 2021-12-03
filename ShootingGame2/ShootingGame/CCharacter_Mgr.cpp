#include "stdafx.h"
#include "CCharacter_Mgr.h"
#include "CAnimation.h"
#include "CHero.h"

CCharacter_Mgr::CCharacter_Mgr()
{
	

}


CCharacter_Mgr::~CCharacter_Mgr()
{
}



void CCharacter_Mgr::CM_Init(HWND a_hWnd)
{
	m_hWnd = a_hWnd;
	m_Girl = Image::FromFile(_T(".\\Reso\\Girl\\idle01.png"));
	m_CharList.SetAni_Rsc(Player);

	CM_ReSetPos(); //시작 위치로 좌표 이동

	
}

void CCharacter_Mgr::CM_ReSetPos()
{
	RECT a_Rect;
	GetClientRect(m_hWnd, &a_Rect); // 클라이언트 화면의 크기를 받는다
	//----- 캐릭터 초기화 부분
	int a_PosX = (int)((float)a_Rect.right * 0.5f);
	int a_PosY = (int)((float)a_Rect.bottom * 0.5f);
	//int a_YTab = a_Rect.bottom / 7;
	
		m_CharList.CChar_ReSetPos(0, a_PosX, a_PosY );
	
	//----- 캐릭터 초기화 부분

}

void CCharacter_Mgr::CM_Update(HDC a_hdc,double a_DeltaTime, RECT * a_rt, bool a_isRaceStart)
{

	m_CharList.CChar_Update(a_hdc,a_DeltaTime, a_rt,a_isRaceStart);
}

void CCharacter_Mgr::CM_RealUpdate(HDC a_hdc, double a_DeltaTime, RECT * a_rt, bool a_isRealStart)
{
	m_CharList.CChar_RealUpdate(a_hdc, a_DeltaTime, a_rt, a_isRealStart);

}

void CCharacter_Mgr::CM_Render(HDC a_hdc,double a_DeltaTime)
{

	Graphics graphics(a_hdc);
	if (m_Girl != NULL)
	{
		graphics.DrawImage(m_Girl, 1300.0f, 200.0f, (float)m_Girl->GetWidth(), (float)m_Girl->GetHeight());
	}

		m_CharList.CChar_Render(a_hdc,a_DeltaTime); //--------------캐릭터 그리는 부분 
	

}



void CCharacter_Mgr::CM_Destroy()
{
	if (m_Girl != NULL)
	{
		delete m_Girl;
		m_Girl = NULL;
	}

}

void CCharacter_Mgr::BossM_ReSetPos(float a_DeltaTime, HWND a_hWnd)
{
	

		static bool a_TicToc = true;
		//한번은 x축으로 
		//한번은 y축으로

		GetClientRect(a_hWnd, &m_bRT); // 클라이언트 화면의 크기를 받는다

		float a_XX = 0.0f;
		float a_YY = 0.0f;
		if (a_TicToc == true)
		{
			a_XX = (float)((rand() % 200) - 100);
			float a_PushVal = 50.0f;
			int a_YLenVal = (int)m_bRT.bottom + 100;

			if (a_XX < 0.0f)
			{
				a_XX = a_XX - a_PushVal;
			}
			else
			{
				a_XX = a_XX + (float)m_bRT.right + a_PushVal;
			}

			a_YY = (float)((rand() % a_YLenVal) + (100 / 2));

			a_TicToc = false;
		}
		else
		{
			a_YY = (float)((rand() % 200) - 100);
			float a_PushVal = 50.0f;
			int a_XLenVal = (int)m_bRT.right + 100;

			if (a_YY < 0.0f)
			{
				a_YY = a_YY - a_PushVal;
			}
			else
			{
				a_YY = a_YY + (float)m_bRT.bottom + a_PushVal;
			}

			a_XX = (float)((rand() % a_XLenVal) - (100 / 2));

			a_TicToc = true;
		}
	

	
	
		m_CharList.Boss_ReSetPos(0, a_XX, a_YY);

	
}

void CCharacter_Mgr::BossM_Update(HDC a_hdc, double a_DeltaTime,CHero &a_Hero )
{
	m_CharList.Boss_Update(a_hdc, a_DeltaTime,a_Hero);

}

void CCharacter_Mgr::BossM_Render(HDC a_hdc, double a_DeltaTime)
{
	m_CharList.Boss_Render(a_hdc, a_DeltaTime);

}

CCharacter_Mgr  g_Char_Mgr;
