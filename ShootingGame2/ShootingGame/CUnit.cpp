#include "stdafx.h"
#include "CUnit.h"
#include "CMyMain.h"


CUnit::CUnit()
{
	m_SocketImg = NULL;
	m_RefAni = NULL;

	m_CurAniState = None;
	m_NowImgCount = 0;
	m_CurAniInx = 0;
	m_AniTickCount = 0;
	m_EachAniDelay = 0.2f;

}


CUnit::~CUnit()
{
}

void CUnit::Init_Unit(HWND a_hWnd)
{


}

void CUnit::Update_Unit(float a_DeltaTime)
{

	//------------애니메이션 플레임 계산부분
	AniFrameUpdate(a_DeltaTime);
	//------------애니메이션 플레임 계산부분

}

void CUnit::Render_Unit(HDC a_hDc)
{


}

void CUnit::Destroy_Unit()
{


}

void CUnit::SetAni_Rsc(CharType a_CharType) 
{
	if (a_CharType <= CT_None || CT_Length <= a_CharType)
		return;

	m_CharType = a_CharType;

	if (a_CharType < g_CMyMain.m_CharAniList.size())
		m_RefAni = g_CMyMain.m_CharAniList[(int)a_CharType];

	if (m_CharType == Bullet)
	{
		ChangeState(Right_Walk);
	}
	else if (m_CharType == Explode)
	{
		ChangeState(Dead_Walk);
	}
	else if (m_CharType == Potion || m_CharType == Gold || m_CharType == Silver
		|| m_CharType == DeadCoin)
	{
		ChangeState(Coin_Walk);
	}

	else if (m_CharType == PlayerExplode)
	{
		ChangeState(EX_Walk);
	}
	else
	{
		ChangeState(Idle);
	}
	
	//if(m_CharType != Coin_Walk)

	LoadUnitSize();
	


}

void CUnit::LoadUnitSize()
{

	if (m_SocketImg != NULL)
	{
		m_ImgSizeX = m_SocketImg->GetWidth();
		m_ImgSizeY = m_SocketImg->GetHeight();

		m_HalfWidth = m_ImgSizeX / 2;
		m_HalfHeight = m_ImgSizeY / 2;
	}

}

bool CUnit::ChangeState(AniState newState)
{
	if (m_CurAniState == newState)
		return false;

	if (newState <= None || AniLength <= newState)
		return false;

	if (m_RefAni == NULL)
		return false;

	if (m_RefAni->m_AniMoList[(int)newState]->m_ImgList.size() <= 0)
		return false;

	m_NowImgCount = m_RefAni->m_AniMoList[(int)newState]->m_ImgList.size();
	m_CurAniInx = 0;
	m_AniTickCount = 0;

	if (newState == Idle)
	{
		m_EachAniDelay = 0.12f;
	}
	else if (newState == Dead)
	{
		m_EachAniDelay = 0.65f;
	}
	else if (newState == Coin_Walk)
	{
		m_EachAniDelay = 0.05f;
		
	}
	
	else if (newState == EX_Walk)
		m_EachAniDelay = 0.12f;
	else
	{
		m_EachAniDelay = 0.12f;
	}

	m_SocketImg = m_RefAni->m_AniMoList[(int)newState]->m_ImgList[0]; //첫 이미지 대입

	m_CurAniState = newState;

	return true;
}

void CUnit::AniFrameUpdate(double a_Deltatime)
{
	//------------------- 애니메이션 플레임 계산 부분 
	if (m_CurAniState == None)
		return;

	if (m_NowImgCount <= 0)  //애니 소켓에 뭔가 꼽혀 있는지 확인해 보는 안전장치
		return;

	m_AniTickCount = m_AniTickCount + a_Deltatime;
	if (m_EachAniDelay < m_AniTickCount)  //다음 플레임
	{
		m_CurAniInx++;
		if (m_NowImgCount <= m_CurAniInx) //마지막 플레임일 때
		{
			m_CurAniInx = 0;
		}

		m_SocketImg = m_RefAni->m_AniMoList[(int)m_CurAniState]->m_ImgList[m_CurAniInx];

		m_AniTickCount = 0;
	}
	//------------------- 애니메이션 플레임 계산 부분 

}
