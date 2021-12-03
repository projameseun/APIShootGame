#include "stdafx.h"
#include "CHeroEx.h"
#include "CAnimation.h"
#include "CHero.h"
CHeroEx::CHeroEx()
{
}


CHeroEx::~CHeroEx()
{
}

void CHeroEx::Load_PExplode(HWND hWnd)
{
	SetAni_Rsc(PlayerExplode);

}

void CHeroEx::PExplodeUpdate(float a_DelTatime, CHero & a_Hero)
{
	ChangeState(EX_Walk);
	CUnit::Update_Unit(a_DelTatime);

}

void CHeroEx::PExplodeRender(HDC a_hdc, Graphics & graphics, CHero & a_Hero, float a_DeltaTime
							,bool a_ExStart)
{
	if (m_SocketImg == NULL)
		return;

	if (a_ExStart == true)
	{
		m_ImgSizeX = (INT)(m_SocketImg->GetWidth());
		m_ImgSizeY = (INT)(m_SocketImg->GetHeight());




		graphics.DrawImage(m_SocketImg,
			Rect(a_Hero.m_CurPos.x - m_HalfWidth,
				a_Hero.m_CurPos.y - (int)(m_HalfHeight * 1.2f),
				(float)m_ImgSizeX, (float)m_ImgSizeY), 0, 0,
			m_SocketImg->GetWidth(), m_SocketImg->GetHeight(),
			UnitPixel);
	}

}

void CHeroEx::PExplodeDestroy()
{


}

CHeroEx g_HeroEx;
