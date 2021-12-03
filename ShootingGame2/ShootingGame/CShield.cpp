#include "stdafx.h"
#include "CShield.h"
#include "CHero.h"
#include "CHeroEx.h"
#include "GlovalValue.h"
#include "CSound.h"
#include "CMonster_Mgr.h"

CShield::CShield()
{
}


CShield::~CShield()
{
}

void CShield::Shield_Init()
{
	shFont_50 = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	
}

void CShield::Load_Shield(HWND hWnd)
{
	SetAni_Rsc(Shield);

}

void CShield::ShieldUpdate(float a_DelTatime,CHero &a_Hero)
{

	static float ExCount = 0;

	//=================쉴드 스킬 발동
	static bool isSdDown = true;
	if (g_GameState == GAME_EXPLODE)
	{
		
			g_Sound.ResetWav(Fly);
		ExCount += a_DelTatime;
		if (ExCount >= 1.0f)
		{
			
			if (ExCount > -1)
			{
				m_ExCount++;
				if (m_ExCount >= 1.9f)
				{
					g_Sound.ResetWav(PlayerExSound); //리셋
					m_ExCount = 0;
					g_GameState = GAME_END;
					m_SdOnTime = 0;
					a_Hero.m_Speed = 300.0f;
					g_Hero.Hero_ReSet();
					g_Mon_Mgr.MonMgr_Reset();


				}
			}

			ExCount = 0;
		}

		g_Sound.UpdateWav(PlayerExSound); //폭팔소리
		
	}
	if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000))
	{
		//m_SdOnTime = 0;
	
		ChangeState(Idle);
		a_Hero.m_Speed = 0.0f;
		if (isSdDown == true)
		{

			//쉳르 발동
			if (0 < a_Hero.m_ShieldCount)
			{
				if (m_SdOnTime <= 0.0f)
				{
					m_SdOnTime = m_SdDuration;
					a_Hero.m_ShieldCount--;
					if (a_Hero.m_ShieldCount < 0)
					{
						a_Hero.m_ShieldCount = 0;
					}
				}//if (m_SdOnTime <= 0.0f)
			}//if (0 < m_ShieldCount)  //쉴드 발동
			isSdDown = false;
		}//if (isSdDown == true)

	}//if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000))
	else
	{
		isSdDown = true;
		
	}
	//=================쉴드 스킬 발동

//	CUnit::Update_Unit(a_DelTatime);

}

void CShield::ShieldRender(HDC a_hdc,Graphics & graphics,CHero &a_Hero,float a_DeltaTime)
{



	static bool blink = false; //깜박임 용도
	static float a_TimeTic = 0;
	static TCHAR a_StrBuff[128];
	
	//-------쉴드 그리기
	if (m_SocketImg == NULL)
		return;

	if (0.0f < m_SdOnTime)
	{
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))
		{
			g_GameState = GAME_EXPLODE;
			 
		}
	//실드 상태에서 왼쪽버튼 눌렀을때 이벤트발생
		bool isExStart = (g_GameState == GAME_EXPLODE) ? true : false;
		g_HeroEx.PExplodeRender(a_hdc, graphics, g_Hero, a_DeltaTime, isExStart);
		
		m_SdOnTime = m_SdOnTime - a_DeltaTime;
		static float a_EffTime = 0.0f;
		static float a_CacSize = 0.0f;
		static Vector2D a_SdCen;

		if (g_GameState == GAME_END)
		{
			a_EffTime = 0;
		
		}

		if ((m_SdDuration - 0.2f) <= m_SdOnTime)
		{
			a_EffTime = (m_SdDuration - m_SdOnTime) / 0.2f;
		}
		else if (m_SdOnTime <= 0.2f) //실드가 끝날때부분
		{
			a_EffTime = m_SdOnTime / 0.2f;
			a_Hero.m_Speed = 300.0f;
		}
		else
		{
			a_EffTime = 1.0f;
		}

		a_CacSize = 500.0f * a_EffTime; //1.0f 
		m_SdHalfSize = a_CacSize / 2.0f;

		
		graphics.DrawImage(m_SocketImg,
			Rect(a_Hero.m_CurPos.x - m_SdHalfSize + 1.0f, a_Hero.m_CurPos.y - m_SdHalfSize,
				a_CacSize, a_CacSize),
			0, 0, m_SocketImg->GetWidth(), m_SocketImg->GetHeight(), UnitPixel);

		/*Graphics graphics(a_hDC);
	graphics.DrawImage(m_ItemImg, m_CurPos.x - m_HalfWidth, m_CurPos.y - m_HalfHeight,
		(float)m_ItemImg->GetWidth(), (float)m_ItemImg->GetHeight());
			*/

		sh_OldFont = (HFONT)SelectObject(a_hdc, shFont_50);
		a_TimeTic = a_TimeTic + a_DeltaTime;
		if (1.0f <= a_TimeTic)
		{
			blink = !blink;
			a_TimeTic = 0.0f;
		}
		if (blink)
			SetTextColor(a_hdc, RGB(255, 0, 0));
		else
			SetTextColor(a_hdc, RGB(255, 255, 0));
		_tcscpy_s(a_StrBuff, _T("실드를 사용해서 움직일수 없습니다."));
		TextOut(a_hdc, a_Hero.m_CurPos.x, a_Hero.m_CurPos.y + 100, a_StrBuff, (int)_tcslen(a_StrBuff));

	}
	//-------쉴드 그리기
	SelectObject(a_hdc, sh_OldFont);

}

void CShield::ShieldDestroy()
{
	if (shFont_50 != NULL)
	{
		DeleteObject(shFont_50);
		shFont_50 = NULL;
	}	

	if (sh_OldFont != NULL)
	{
		DeleteObject(sh_OldFont);
		sh_OldFont = NULL;
	}

}


CShield g_Shield;