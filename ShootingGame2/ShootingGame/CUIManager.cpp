#include "stdafx.h"
#include "CUIManager.h"
#include "GlovalValue.h"
#include "CSound.h"
#include "CCharacter_Mgr.h"
#include "CHero.h"
#include "CMyMain.h"

CButton::CButton()
{
	m_isBtnDown = false;
	m_BtnUpImg = NULL;
	m_BtnDownImg = NULL;

	m_LT_Pos.x = 100.0f;
	m_LT_Pos.y = 100.0f;
	m_WH_Size.x = 10.0f;
	m_WH_Size.y = 10.0f;

	m_DownCM = { 0.72f, 0.0f ,0.0f, 0.0f, 0.0f,
				0.0f, 0.64f ,0.0f, 0.0f, 0.0f,
				0.0f, 0.0f ,0.48f, 0.0f, 0.0f,
				0.0f, 0.0f ,0.0f, 1.0f, 0.0f,
				0.0f, 0.0f ,0.0f, 0.0f, 1.0f, };

}

CButton::~CButton()
{


}

void CButton::SetBtnRect(float a_LeftPos, float a_TopPos, float a_WSize, float a_HSize)
{
	m_LT_Pos.x = a_LeftPos;
	m_LT_Pos.y = a_TopPos;
	if (0.0f < a_WSize && 0.0f < a_HSize)
	{
		m_WH_Size.x = a_WSize;
		m_WH_Size.y = a_HSize;
	}


}

void CButton::Load_Rsc(const TCHAR * a_BtnUpStr, const TCHAR * a_BtnDownStr)
{
	m_isBtnDown = false;

	m_BtnUpImg = Image::FromFile(a_BtnUpStr);
	if (m_BtnUpImg != NULL)
	{
		m_WH_Size.x = m_BtnUpImg->GetWidth() / 2;
		m_WH_Size.y = m_BtnUpImg->GetHeight() / 2;
	}

	if (a_BtnDownStr == NULL)
		return;

	m_BtnDownImg = Image::FromFile(a_BtnDownStr);
}

void CButton::BtnRender(HDC a_hDC)
{
	Graphics graphics(a_hDC);
	if (m_isBtnDown == true)
	{
		if (m_BtnDownImg != NULL)
		{
			graphics.DrawImage(m_BtnDownImg,
				Rect(m_LT_Pos.x, m_LT_Pos.y, m_WH_Size.x, m_WH_Size.y),
				0, 0, m_BtnDownImg->GetWidth(), m_BtnDownImg->GetHeight(), UnitPixel);
		}//if (m_BtnDownImg != NULL)
		else
		{
			if (m_BtnUpImg != NULL)
			{
				ImageAttributes a_DownAB;
				a_DownAB.SetColorMatrix(&m_DownCM);
				graphics.DrawImage(m_BtnUpImg,
					Rect(m_LT_Pos.x, m_LT_Pos.y, m_WH_Size.x, m_WH_Size.y),
					0, 0, m_BtnUpImg->GetWidth(), m_BtnUpImg->GetHeight(), UnitPixel);
			}//if (m_BtnUpImg != NULL)
		}//	if (m_BtnDownImg == NULL)
	}//	if (m_isBtnDown == true)
	else
	{
		if (m_BtnUpImg != NULL)
		{
			graphics.DrawImage(m_BtnUpImg,
				Rect(m_LT_Pos.x, m_LT_Pos.y, m_WH_Size.x, m_WH_Size.y),
				0, 0, m_BtnUpImg->GetWidth(), m_BtnUpImg->GetHeight(), UnitPixel);
		}
	}//if (m_isBtnDown == false)

}

void CButton::Destroy()
{
	if (m_BtnUpImg != NULL)
	{
		delete m_BtnUpImg;
		m_BtnUpImg = NULL;
	}
	if (m_BtnDownImg != NULL)
	{
		delete m_BtnDownImg;
		m_BtnDownImg = NULL;
	}

}

void CButton::LBtnDown(Vector2D a_MosPos)
{
	if (m_LT_Pos.x <= a_MosPos.x && a_MosPos.x <= m_LT_Pos.x + m_WH_Size.x
		&& m_LT_Pos.y <= a_MosPos.y && a_MosPos.y <= m_LT_Pos.y + m_WH_Size.y)
	{
		m_isBtnDown = true;

		/*if (num == 0)
		{
		
		}*/
	}



}

bool CButton::LBtnUp()
{
	if (m_isBtnDown == true)
	{
		m_isBtnDown = false;

		if (ClickCallback != NULL)
			ClickCallback();
		return true;

	}

	m_isBtnDown = false;
	return false;
}

void CButton::OnClick_AddListener(function<void(void)> Callback)
{

	ClickCallback = Callback;

}





//button
///////////////////////////////////////////////

CUIManager::CUIManager()
{
}


CUIManager::~CUIManager()
{
}

void CUIManager::UIMgrInit(HDC a_hdc, RECT &a_RT)
{
	m_Font_200_Gulim = CreateFont(200, 0, 0, 0, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	m_Font_50_Batang = CreateFont(50, 0, 0, 0, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("바탕"));

	m_Font_100_Batang = CreateFont(100, 0, 0, 0, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("바탕"));
	m_Font_40_Batang = CreateFont(40, 0, 0, 0, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("바탕"));

	m_Font_30_Gulim = CreateFont(30, 0, 0, 0, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));

	m_Font_Default = CreateFont(20,0,0,0,0,0,0,0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));

	//--------icon 변ㅅ들 
	m_Font_26Godic = CreateFont(26, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));

	hFont_100 = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));

	hFont_50 = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("바탕"));

	//--------icon 변ㅅ들 
	m_GUIBack = Image::FromFile(_T(".\\Reso\\UI\\Tui1.png"));
	m_HP_Icon = Image::FromFile(_T(".\\Reso\\UI\\HP.png"));



	StoreInit(a_hdc,a_RT);
}

void CUIManager::UIMgrUpdate(double a_DeltaTime, HWND a_hWnd,void(*NextLevelFunc)(), void(*ReSetGameFunc)())
{
	m_DeltaTime = a_DeltaTime;
	
	if (GetFocus() == NULL)	//현재 윈도우가 활성화 되어 있지 않으면 주인공 컨트롤 제외
		return;

	static bool isSPDown = true;
	if (GAME_MOUSESTART == g_GameState)
	{
		static float CountTime = 0;
		CountTime += a_DeltaTime;
		if (CountTime >= 1)
		{
			if (CountTime > -1)
			{
				g_TimeOut--;
				if (g_TimeOut <= 0)
				{
					g_TimeOut = 30;
					g_DiffLevel++;
					g_GameState = GAME_INVEN;
					g_Sound.ResetWav(GameStart);
				}
			}
			CountTime = 0;
		}
	}

	else if (g_GameState == GAME_INVEN)
	{
		if ((GetAsyncKeyState('N') & 0x8000))
		{
			if (isSPDown == true)
			{
				if (NextLevelFunc != NULL)
				{
					NextLevelFunc(); //다음단계진행
				}

				isSPDown = false;
			}
		}
		else
		{
			isSPDown = true;
		}

		//----------mouse LbuttonDown 처리
		static bool isMsLDown = true;
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))
		{
			if (isMsLDown == true)
			{
				LBtnDown(a_hWnd);
				isMsLDown = false;
			}//if (isMsLDown == true)
		}
		else
		{
			if (isMsLDown == false)
			{
				LBtnUp();
				isMsLDown = true;

			}//if (isMsLDown == false)
		}
	}//else if (g_GameState == GAME_LEVEL)
	else if (g_GameState == GAME_END)
	{
		if ((GetAsyncKeyState('R') & 0x8000))
		{
			if (isSPDown == true)
			{
				if (ReSetGameFunc != NULL)
				{
					ReSetGameFunc(); //다음단계
				}
				isSPDown = false;
			}
		}
		else
		{
			isSPDown = true;
		}
	}

	else if (GAME_BOSTART == g_GameState)
	{
		static float BossTime = 0;
		BossTime += a_DeltaTime;
		if (BossTime >= 1.0f)
		{
			if (g_TimeOut > 0)
			{
				g_TimeOut--;
				if (g_TimeOut <= 0)
				{
					g_TimeOut = 30;
					
					g_GameState = GAME_ENDING;
					g_Sound.ResetWav(GameStart);
				}
			}
			BossTime = 0;
		}
	}
	else if (GAME_ENDING == g_GameState)
	{
		g_Sound.UpdateWav(EndingSound); //ending
		static float EndingCount = 0;
		EndingCount += a_DeltaTime;
		if (EndingCount >= 1.0f)
		{
			m_EndingCount++;
			if (m_EndingCount >=14)
			{

				g_Sound.ResetWav(EndingSound);
				m_EndingCount = 0;
				g_CMyMain.ReSetGame();
			}
			EndingCount = 0;
		}

		
	}
}

void CUIManager::UIMgrRender(HDC a_hdc, RECT & a_RT, float a_Deltatime)
{
	Graphics graphics(a_hdc);

	switch (g_GameState)
	{
	case	GAME_READY:
		GameReady_Render(a_hdc, a_RT);
		break;
	case	GAME_INVEN:
		GameInven_Render(a_hdc, a_RT,a_Deltatime);
		break;
	case	GAME_END:
		GameEnd_Render(a_hdc, a_RT);
		break;
	case GAME_REALCOUNT:
		GameStart_Render(a_hdc, a_RT);
		break;
	case GAME_MOUSESTART:
		UserInfoPanel(a_hdc,graphics,a_RT,a_Deltatime);
		break;
	case GAME_EXPLODE:
		UserInfoPanel(a_hdc, graphics, a_RT, a_Deltatime);
		break;
	case GAME_BOSS:
		UserInfoPanel(a_hdc, graphics, a_RT, a_Deltatime);
		break;
	case GAME_BOSTART:
		UserInfoPanel(a_hdc, graphics, a_RT, a_Deltatime);
		break;

	case GAME_ENDING:
		GameEnding_Render(a_hdc, a_RT);
		break;
	}		

}

void CUIManager::UIMgrDestroy()
{
	if (hFont_100 != NULL)
	{
		DeleteObject(hFont_100);
		hFont_100 = NULL;
	}

	if (hFont_50 != NULL)
	{
		DeleteObject(hFont_50);
		hFont_50 = NULL;
	}

	if (m_Font_26Godic != NULL)
	{
		DeleteObject(m_Font_26Godic);
		m_Font_26Godic = NULL;
	}


	if (m_Font_200_Gulim != NULL)
	{
		DeleteObject(m_Font_200_Gulim);
		m_Font_200_Gulim = NULL;
	}

	if (m_Font_50_Batang != NULL)
	{
		DeleteObject(m_Font_50_Batang);
		m_Font_50_Batang = NULL;
	}

	if (m_Font_100_Batang != NULL)
	{
		DeleteObject(m_Font_100_Batang);
		m_Font_100_Batang = NULL;
	}

	if (m_Font_40_Batang != NULL)
	{
		DeleteObject(m_Font_40_Batang);
		m_Font_40_Batang = NULL;
	}

	if (m_Font_30_Gulim != NULL)
	{
		DeleteObject(m_Font_30_Gulim);
		m_Font_30_Gulim = NULL;
	}

	if (m_Font_Default != NULL)
	{
		DeleteObject(m_Font_Default);
		m_Font_Default = NULL;
	}


	if (m_pBtnDownImg != NULL)
	{
		delete m_pBtnDownImg;
		m_pBtnDownImg = NULL;
	}

	if (m_pBtnUpImg != NULL)
	{
		delete m_pBtnUpImg;
		m_pBtnUpImg = NULL;
	}

	if (m_GUIBack != NULL)
	{
		delete m_GUIBack;
		m_GUIBack = NULL;
	}

	if (m_HP_Icon != NULL)
	{
		delete m_HP_Icon;
		m_HP_Icon = NULL;
	}

	
}

void CUIManager::GameReady_Render(HDC a_hdc, RECT & a_RT)
{


	Graphics graphics(a_hdc);
	SelectObject(a_hdc, m_Font_50_Batang);
	static bool blink = false; //깜박임 용도
	static float a_TimeTic = 0;
	a_TimeTic = a_TimeTic + m_DeltaTime;
	if (1.0f <= a_TimeTic)
	{
		blink = !blink;
		a_TimeTic = 0.0f;
	}
	if (blink)
		SetTextColor(a_hdc, RGB(255, 0, 0));
	else
		SetTextColor(a_hdc, RGB(0, 0, 0));


	TextOut(a_hdc, (a_RT.right / 2), (a_RT.bottom /2) - 200,
		_T("병 맛 게 임"),
		(int)_tcslen(_T("병 맛 게 임")));

	if (blink)
		SetTextColor(a_hdc, RGB(255, 247, 15)); //Yellow
	else
		SetTextColor(a_hdc, RGB(0, 0, 0));

	TextOut(a_hdc, (a_RT.right / 2), (a_RT.bottom * 0.7f),
		_T("[시작하려면 [Space]키를 누르세요]"),
		(int)_tcslen(_T("[시작하려면 [Space]키를 누르세요]")));



	SelectObject(a_hdc, m_Font_Default);
	if (blink)
		SetTextColor(a_hdc, RGB(255, 255, 000)); //Yellow
	else
		SetTextColor(a_hdc, RGB(0, 0, 0));

	TextOut(a_hdc, (a_RT.right -90.0f), (a_RT.bottom -40.0f),
		_T("제작자: ProJames"),
		(int)_tcslen(_T("제작자: ProJames")));

	SelectObject(a_hdc, a_hOldFont);
	//SetTextColor(a_hdc, RGB(0, 0, 0));  // 원래대로...

}

void CUIManager::GameInven_Render(HDC a_hdc, RECT & a_RT, float a_Deltatime)
{
	
	Graphics graphics(a_hdc);
	static bool blink = false; //깜박임 용도
	static float a_TimeTic = 0;
	static TCHAR a_StrBuff[128];

	SetBkMode(a_hdc, TRANSPARENT);  // 텍스쳐 배경을 뺀다.
	SetTextAlign(a_hdc, TA_CENTER); // 글씨 정렬함수 중앙정렬
	m_OldFont = (HFONT)SelectObject(a_hdc, hFont_100);
	SetTextColor(a_hdc, RGB(128, 128, 128));
	_stprintf_s(a_StrBuff, _T("%d 단계 Clear"), g_DiffLevel - 1);
	TextOut(a_hdc, (a_RT.right / 2), 110, a_StrBuff, (int)_tcslen(a_StrBuff));

	SelectObject(a_hdc, hFont_50);

	SetTextColor(a_hdc, RGB(100, 50, 34));
	_stprintf_s(a_StrBuff, _T("Kill : %d"), g_Hero.m_KillCount);
	TextOut(a_hdc, (a_RT.right / 2) - 10, 270, a_StrBuff, (int)_tcslen(a_StrBuff));

	_stprintf_s(a_StrBuff, _T("다음단계 : %d 단계"), g_DiffLevel);
	TextOut(a_hdc, (a_RT.right / 2) - 10, 320, a_StrBuff, (int)_tcslen(a_StrBuff));

	a_TimeTic = a_TimeTic + m_DeltaTime;
	if (1.0f <= a_TimeTic)
	{
		blink = !blink;
		a_TimeTic = 0.0f;
	}
	if (blink)
		SetTextColor(a_hdc, RGB(0, 99, 177));
	else
		SetTextColor(a_hdc, RGB(0, 0, 0));

	_tcscpy_s(a_StrBuff, _T("[다음 단계 시작은 [N]키를 누르세요]"));
	TextOut(a_hdc, (a_RT.right / 2), (a_RT.bottom * 0.7f),
		a_StrBuff, (int)_tcslen(a_StrBuff));

	SelectObject(a_hdc, m_OldFont);      // 원래대로...
	SetTextColor(a_hdc, RGB(0, 0, 0));   // 원래대로...
	SetTextAlign(a_hdc, TA_LEFT);  // 원래대로...
	SetBkMode(a_hdc, OPAQUE);   // 원래대로...

	StoreRender(a_hdc, graphics, a_RT, a_Deltatime);
}//void CUIManager::GameInven_Render(HDC a_hdc, RECT & a_RT)

void CUIManager::GameEnd_Render(HDC a_hdc, RECT & a_RT)
{
	static HFONT a_hOldFont = NULL;

	SetTextColor(a_hdc, RGB(255, 0, 0));
	a_hOldFont = (HFONT)SelectObject(a_hdc, m_Font_100_Batang);
	TextOut(a_hdc, (a_RT.right / 2), (a_RT.bottom / 2) - 200, _T("GAME OVER"),
		(int)_tcslen(_T("GAME OVER")));

	SelectObject(a_hdc, m_Font_40_Batang);
	static bool blink = false; //깜박임 용도
	static float a_TimeTic = 0;
	a_TimeTic = a_TimeTic + m_DeltaTime;
	if (1.0f <= a_TimeTic)
	{
		blink = !blink;
		a_TimeTic = 0.0f;
	}
	if (blink)
	{
		SetTextColor(a_hdc, RGB(0, 99, 177));
	}
	else
	{
		SetTextColor(a_hdc, RGB(0, 0, 0));
	}
	TextOut(a_hdc, (a_RT.right / 2), (a_RT.bottom / 2) + 150,
		_T("[다시 시작하려면 [R]키를 누르세요]"),
		(int)_tcslen(_T("[다시 시작하려면 [R]키를 누르세요]")));
	//SelectObject(a_hdc, a_hOldFont);


	SelectObject(a_hdc, a_hOldFont);
	SetTextColor(a_hdc, RGB(0, 0, 0));   // 원래대로...
	SetTextAlign(a_hdc, TA_LEFT);  // 원래대로...
	SetBkMode(a_hdc, OPAQUE);   // 원래대로...

	

}

void CUIManager::GameStart_Render(HDC a_hdc, RECT & a_RT)
{

	static HFONT a_hOldFont = NULL;

	SetTextColor(a_hdc, RGB(255,0, 0));
	a_hOldFont = (HFONT)SelectObject(a_hdc, m_Font_Default);

	g_Sound.UpdateWav(7);
	g_Sound.UpdateWav(8);
	TextOut(a_hdc, (a_RT.right / 2), (a_RT.bottom / 2) - 100, _T("지금부터 게임을 시작하겠습니다."),
		(int)_tcslen(_T("지금부터 게임을 시작하겠습니다.")));


	static float a_TimeTic = 0;
	a_TimeTic = a_TimeTic + m_DeltaTime;
	static TCHAR a_TmStr[128];
	


	SetTextColor(a_hdc, RGB(255, 0, 0));
	a_hOldFont = (HFONT)SelectObject(a_hdc, m_Font_200_Gulim);

	_stprintf_s(a_TmStr, _T("%d"), m_TPCount);
	TextOut(a_hdc, (a_RT.right / 2), (a_RT.bottom / 2) - 300, a_TmStr, (int)_tcslen(a_TmStr));

	if (a_TimeTic >= 1.0f)
	{
		//금부터 진짜 게임을 시작하겠습니다.
		
		g_Sound.ResetWav(7);
		if (a_TimeTic > -1)
		{
			m_TPCount--;
			if (m_TPCount <= 0)
			{
			
				
				g_GameState = GAME_REALSTART;
				g_Char_Mgr.CM_ReSetPos();
		
				g_Sound.ResetWav(7);
				g_Sound.ResetWav(8);

				SelectObject(a_hdc, a_hOldFont);

				m_TPCount = 5;
		
			}
		
		
		}

		a_TimeTic = 0.0f;
	}
	//SelectObject(a_hdc, a_hOldFont);



	SelectObject(a_hdc, a_hOldFont);

}

void CUIManager::GameEnding_Render(HDC a_hdc, RECT & a_RT)
{

	SetTextColor(a_hdc, RGB(255, 255, 0));
	SetBkMode(a_hdc, TRANSPARENT);      // 텍스쳐 배경을 뺀다.
	a_hOldFont = (HFONT)SelectObject(a_hdc,m_Font_100_Batang);
	TextOut(a_hdc, (a_RT.right / 2), (a_RT.bottom / 2) - 100, _T("이용해주셔서 감사합니다."),
		(int)_tcslen(_T("이용해주셔서 감사합니다.")));

	SelectObject(a_hdc, a_hOldFont);
}


void CUIManager::UserInfoPanel(HDC a_MainDC, Graphics & graphics, RECT & a_RT,float a_Deltatime)
{


	if (m_GUIBack != NULL)
	{
		graphics.DrawImage(m_GUIBack, 5.0f, 5.0f, (float)m_GUIBack->GetWidth(), (float)m_GUIBack->GetHeight());
	}

	//----- 주인공 Hp 표시와 Kill 수 표시
	m_OldFont = (HFONT)SelectObject(a_MainDC, m_Font_26Godic);
	SetTextColor(a_MainDC, RGB(186, 255, 149));
	//SetTextAlign(a_MainDC, TA_CENTER); // 글씨 정렬함수 중앙정렬
	SetTextAlign(a_MainDC, TA_LEFT);
	SetBkMode(a_MainDC, TRANSPARENT);      // 텍스쳐 배경을 뺀다.

	//---- HP Bar Render
	if (m_HP_Icon != NULL)
	{
		graphics.DrawImage(m_HP_Icon, 15.0f, 12.0f, (float)m_HP_Icon->GetWidth(), (float)m_HP_Icon->GetHeight());

		graphics.DrawImage(m_HP_Icon, RectF(15.0f, 12.0f, (float)m_HP_Icon->GetWidth(), (float)m_HP_Icon->GetHeight() / 2),
			0.0f, 0.0f, (float)m_HP_Icon->GetWidth(), (float)m_HP_Icon->GetHeight() / 2, Gdiplus::UnitPixel);
	}

	_stprintf_s(m_StrBuff, L" : Hp %d / %d", (int)g_Hero.m_CurHP, (int)g_Hero.m_MaxHP);
	TextOut(a_MainDC, 42, 10, m_StrBuff, (int)_tcslen(m_StrBuff));
	////---- HP Bar Render



	SetTextColor(a_MainDC, RGB(255, 149, 149));
	_stprintf_s(m_StrBuff, L"Kill : %d", g_Hero.m_KillCount);
	TextOut(a_MainDC, 15, 38, m_StrBuff, (int)_tcslen(m_StrBuff));

	SetTextColor(a_MainDC, RGB(149, 231, 255));
	_stprintf_s(m_StrBuff, L"Skill : %d  Shield : %d", g_Hero.m_SkillCount, g_Hero.m_ShieldCount);
	TextOut(a_MainDC, 15, 66, m_StrBuff, (int)_tcslen(m_StrBuff));

	SetTextColor(a_MainDC, RGB(255, 226, 149));
	_stprintf_s(m_StrBuff, L"Money : %d", g_Hero.m_MyMoney);
	TextOut(a_MainDC, 15, 94, m_StrBuff, (int)_tcslen(m_StrBuff));



	SetBkMode(a_MainDC, OPAQUE);        //텍스트 배경 원래대로...
	SetTextColor(a_MainDC, RGB(0, 0, 0));

	SetTextAlign(a_MainDC, TA_CENTER);  // 글씨 정렬함수 중앙정렬
	if (g_GameState != GAME_BOSS && g_GameState != GAME_BOSTART)
	{
		_stprintf_s(m_StrBuff, _T("<%d 단계> TimeOut : %d"), g_DiffLevel, g_TimeOut);
		TextOut(a_MainDC, (a_RT.right / 2) - 10, 13, m_StrBuff, (int)_tcslen(m_StrBuff));
	}
	static float BossCount = 0;

	if (g_GameState == GAME_BOSS || g_GameState == GAME_BOSTART)
	{
		

	_stprintf_s(m_StrBuff, _T("<보스 출현 끝까지 살아남아라> TimeOut:%d "), g_TimeOut);
	TextOut(a_MainDC, (a_RT.right / 2) , 13, m_StrBuff, (int)_tcslen(m_StrBuff));
		if (g_GameState == GAME_BOSS)
		{
			BossCount += a_Deltatime;
			if(BossCount >= 1.0f)
			{
				m_BossCount--;
				if (m_BossCount <= 0 )
				{
					g_GameState = GAME_BOSTART;
					g_CMyMain.BossRest();
					m_BossCount = 5;
				}
				BossCount = 0;
			}
			TextOut(a_MainDC, (a_RT.right / 2) , (a_RT.bottom / 2) - 100, _T("그만좀 날려라 ㅡ...ㅡ"),
			(int)_tcslen(_T("그만좀 날려라 ㅡ...ㅡ")));

		}
	}



	SetTextAlign(a_MainDC, TA_CENTER);  // 글씨 정렬함수 중앙정렬
	SetTextAlign(a_MainDC, TA_LEFT);    // 원래대로...

	SelectObject(a_MainDC, m_OldFont);


}

void CUIManager::StoreInit(HDC a_hdc, RECT &a_RT)
{
	//--------------Shop 초기화
	m_ShopOnOff = true;
	m_ShopBase = NULL;
	m_AlphaCM = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	m_HumanF = NULL;

	for (int aa = 0; aa < 3; aa++)
	{
		m_ShopBG[aa] = NULL;
		m_Image[aa] = NULL;
		m_CoinImg[aa] = NULL;
	}
	//--------------Shop 초기화

	//--------------Shop Image 로딩
	//m_ShopBase = Image::FromFile(_T(".\\Resource\\RscTrunk\\WhiteBG.png"));

	m_HumanF = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));

	m_CloseBtn.Load_Rsc(_T(".\\Reso\\RscTrunk\\btn_close_f.png"), _T(".\\Reso\\RscTrunk\\btn_close_n.png"));
	//OnClick_AddListener
	//이벤트 함수 등록.... 람다식으로...
	CButton* a_RefBtn = &m_CloseBtn;
	m_CloseBtn.OnClick_AddListener([this, a_RefBtn]()
	{
		m_ShopOnOff = false;
	});

	//--------------- [0]
	m_ShopBG[0] = Image::FromFile(_T(".\\Reso\\RscTrunk\\itemshop_frame_n.png"));
	m_Image[0] = Image::FromFile(_T(".\\Reso\\RscTrunk\\item_life.png"));//
	m_CoinImg[0] = Image::FromFile(_T(".\\Reso\\RscTrunk\\itemshop_coin.png"));
	m_AddBtn[0].Load_Rsc(_T(".\\Reso\\RscTrunk\\itemshop_btn_green_f.png"), _T(".\\Reso\\RscTrunk\\itemshop_btn_green_n.png"));
	if (m_AddBtn[0].m_BtnUpImg != NULL)
	{
		m_AddBtn[0].m_WH_Size.x = ((float)m_AddBtn[0].m_BtnUpImg->GetWidth() / 1.7f);
		m_AddBtn[0].m_WH_Size.y = m_AddBtn[0].m_BtnUpImg->GetHeight() / 2;
	}

	m_AddBtn[0].OnClick_AddListener(CHero::BuyHP);
	//if (m_AddBtn[0].OnClick_AddListener)
	//{
	//	TextOut(a_hdc, (a_RT.left / 2), a_RT.bottom - 100,
	//		_T("HP가 모두 회복되었습니다"),
	//		(int)_tcslen(_T("HP가 모두 회복되었습니다")));
	//}
	//--------------- [0]

	//--------------- [1]
	m_ShopBG[1] = Image::FromFile(_T(".\\Reso\\RscTrunk\\itemshop_frame_n.png"));
	m_Image[1] = Image::FromFile(_T(".\\Reso\\RscTrunk\\item_bomb.png"));//
	m_CoinImg[1] = Image::FromFile(_T(".\\Reso\\RscTrunk\\itemshop_coin.png"));

	m_AddBtn[1].Load_Rsc(_T(".\\Reso\\RscTrunk\\itemshop_btn_green_f.png"), _T(".\\Reso\\RscTrunk\\itemshop_btn_green_n.png"));
	if (m_AddBtn[1].m_BtnUpImg != NULL)
	{
		m_AddBtn[1].m_WH_Size.x = ((float)m_AddBtn[1].m_BtnUpImg->GetWidth() / 1.7f);
		m_AddBtn[1].m_WH_Size.y = m_AddBtn[1].m_BtnUpImg->GetHeight() / 2;
	}
	m_AddBtn[1].OnClick_AddListener(CHero::BuySkill);
	//--------------- [1]

	//--------------- [2]
	m_ShopBG[2] = Image::FromFile(_T(".\\Reso\\RscTrunk\\itemshop_frame_n.png"));
	m_Image[2] = Image::FromFile(_T(".\\Reso\\RscTrunk\\item_shield.png"));//
	m_CoinImg[2] = Image::FromFile(_T(".\\Reso\\RscTrunk\\itemshop_coin.png"));

	m_AddBtn[2].Load_Rsc(_T(".\\Reso\\RscTrunk\\itemshop_btn_green_f.png"), _T(".\\Reso\\RscTrunk\\itemshop_btn_green_n.png"));
	if (m_AddBtn[2].m_BtnUpImg != NULL)
	{
		m_AddBtn[2].m_WH_Size.x = ((float)m_AddBtn[2].m_BtnUpImg->GetWidth() / 1.7f);
		m_AddBtn[2].m_WH_Size.y = m_AddBtn[2].m_BtnUpImg->GetHeight() / 2;
	}
	m_AddBtn[2].OnClick_AddListener(CHero::BuyShield);
	//--------------- [2]

	//--------------Shop Image 로딩

}

void CUIManager::StoreRender(HDC a_MainDC, Graphics & graphics, RECT & a_RT, float a_Deltatime)
{
	if (m_ShopOnOff == false)
		return;

	if (m_ShopBase != NULL)
	{
		ImageAttributes AlphaAB;
		AlphaAB.SetColorMatrix(&m_AlphaCM);
		graphics.DrawImage(m_ShopBase, Rect(0.0f, 0.0f, a_RT.right, a_RT.bottom),
			0, 0, m_ShopBase->GetWidth(), m_ShopBase->GetHeight(), UnitPixel, &AlphaAB);
	}

	m_OldFont = (HFONT)SelectObject(a_MainDC, m_Font_26Godic);

	SetTextColor(a_MainDC, RGB(186, 255, 149));
	//SetTextAlign(a_MainDC, TA_CENTER); // 글씨 정렬함수 중앙정렬

	UserInfoPanel(a_MainDC, graphics, a_RT, a_Deltatime); //유저 정보 그리기 

	SetBkMode(a_MainDC, TRANSPARENT);    // 텍스쳐 배경을 뺀다.

	static float m_SpXX;
	static float m_SpYY;
	static float m_Paddle = 50.0f;
	static float m_Dx = 200.0f;
	static float m_Dy = 350.0f;
	m_SpXX = a_RT.right / 2 - 350.0f;;
	m_SpYY = a_RT.bottom / 4 - 50.0f;

	SetTextColor(a_MainDC, RGB(255, 255, 255));

	static float a_CacSpXX = 0.0f;
	static float a_CacSpYY = 0.0f;

	static float a_ItmSpXX = 0.0f;
	static float a_ItmSpYY = 0.0f;

	static float a_BtnSpXX = 0.0f;
	static float a_BtnSpYY = 0.0f;

	for (int i = 0; i < 3; i++)
	{
		a_CacSpXX = m_SpXX + (i * (m_Dx + m_Paddle));
		a_CacSpYY = m_SpYY;

		graphics.DrawImage(m_ShopBG[i], Rect(a_CacSpXX, a_CacSpYY, m_Dx, m_Dy),
			0, 0, m_ShopBG[i]->GetWidth(), m_ShopBG[i]->GetHeight(), UnitPixel);

		a_ItmSpXX = a_CacSpXX + (m_Dx / 2) - (m_Image[i]->GetWidth() / 4);
		a_ItmSpYY = a_CacSpYY + 30;

		graphics.DrawImage(m_Image[i], Rect(a_ItmSpXX, a_ItmSpYY, (m_Image[i]->GetWidth() / 2), (m_Image[i]->GetHeight() / 2)),
			0, 0, m_Image[i]->GetWidth(), m_Image[i]->GetHeight(), UnitPixel);

		//---설명
		if (i == 0)
		{
			TextOutA(a_MainDC, a_CacSpXX + 70.0f, a_CacSpYY + 110.0f, "HP 100%", (int)strlen("HP 100%"));
		}
		else if (i == 1)
		{
			TextOutA(a_MainDC, a_CacSpXX + 70.0f, a_CacSpYY + 110.0f, "SKill+1", (int)strlen("SKill+1"));
		}
		else if (i == 2)
		{
			TextOutA(a_MainDC, a_CacSpXX + 70.0f, a_CacSpYY + 110.0f, "Shild+1", (int)strlen("Shild+1"));
		}
		//---설명

		//---가격
		graphics.DrawImage(m_CoinImg[i], Rect(a_CacSpXX + 30.0f, a_CacSpYY + 165.0f,
			(m_CoinImg[i]->GetWidth() * 0.9f), (m_CoinImg[i]->GetHeight() * 0.9f)),
			0, 0, m_CoinImg[i]->GetWidth(), m_CoinImg[i]->GetHeight(), UnitPixel);

		SelectObject(a_MainDC, m_HumanF);
		if (i == 0)
		{
			TextOutA(a_MainDC, a_CacSpXX + 100.0f, a_CacSpYY + 160.0f, "100", (int)strlen("100"));
		}
		else if (i == 1)
		{
			TextOutA(a_MainDC, a_CacSpXX + 100.0f, a_CacSpYY + 160.0f, "150", (int)strlen("150"));
		}
		else if (i == 2)
		{
			TextOutA(a_MainDC, a_CacSpXX + 100.0f, a_CacSpYY + 160.0f, "200", (int)strlen("200"));
		}
		SelectObject(a_MainDC, m_Font_26Godic);
		//---가격

		//---버튼 그리기
		if (m_AddBtn[i].m_BtnUpImg != NULL)
		{
			a_BtnSpXX = a_CacSpXX + (m_Dx / 2) - ((m_AddBtn[i].m_BtnUpImg->GetWidth() / 1.72f) / 2.0f);
			a_BtnSpYY = a_CacSpYY + (m_Dy - 100);

			m_AddBtn[i].SetBtnRect(a_BtnSpXX, a_BtnSpYY); //버튼 위치 다시 대입
			m_AddBtn[i].BtnRender(a_MainDC);

			TextOutA(a_MainDC, a_BtnSpXX + 53, a_BtnSpYY + 16, "ADD+", (int)strlen("ADD+"));
		}
		//---버튼 그리기
	}//for (int i = 0; i < 3; i++)
	static float Count = 0;
	
	if (g_ClickState == GAME_LEFT)
	{
		Count += a_Deltatime;
		if (Count >= 1.0f)
		{
			m_Count--;
			Count = 0;
		}
		m_OldFont = (HFONT)SelectObject(a_MainDC, m_Font_40_Batang);
		if (100 <= g_Hero.m_MyMoney || m_Count >= 0)
		{

			SetTextColor(a_MainDC, RGB(255, 0, 0));
			TextOut(a_MainDC, (a_RT.right / 2) - 200, a_RT.bottom - 100,
				_T("HP가 모두 회복되었습니다"),
				(int)_tcslen(_T("HP가 모두 회복되었습니다")));
			//Sleep(2000);
			if (m_Count == 0)
			{
				m_Count = 3;
				g_ClickState = GAME_RIGHT;
			}
		}//if (100 <= g_Hero.m_MyMoney)

		
	}
	

	m_CloseBtn.SetBtnRect(a_RT.right - 100, 15); //버튼 위치 다시 대입
	m_CloseBtn.BtnRender(a_MainDC);

	
	
		SetTextColor(a_MainDC, RGB(0, 0, 0));
		SetBkMode(a_MainDC, OPAQUE);            // 텍스트 배경 원래대로...
		//SetTextAlign(a_MainDC, TA_LEFT);        // 원래대로...
		SelectObject(a_MainDC, m_OldFont);
	
	


}

void CUIManager::StoreDestroy()
{
	//--------------Shop 리소스 제거
	if (m_ShopBase != NULL)
	{
		delete m_ShopBase;
		m_ShopBase = NULL;
	}

	m_CloseBtn.Destroy();

	for (int aa = 0; aa < 3; aa++)
	{
		m_AddBtn[aa].Destroy();

		if (m_ShopBG[aa] != NULL)
		{
			delete m_ShopBG[aa];
			m_ShopBG[aa] = NULL;
		}

		if (m_Image[aa] != NULL)
		{
			delete m_Image[aa];
			m_Image[aa] = NULL;
		}

		if (m_CoinImg[aa] != NULL)
		{
			delete m_CoinImg[aa];
			m_CoinImg[aa] = NULL;
		}
	}

	if (m_HumanF != NULL)
	{
		DeleteObject(m_HumanF);
		m_HumanF = NULL;
	}
	//--------------Shop 리소스 제거

}

void CUIManager::LBtnDown(HWND a_hWnd)
{
	if (m_ShopOnOff == false)
		return;

	POINT a_NewMMXZ;
	GetCursorPos(&a_NewMMXZ);              //현재 마우스 좌표를 얻어오는 함수 
	ScreenToClient(a_hWnd, &a_NewMMXZ);    // 클라이언트 화면 좌표로 변경해 주는 함수
	Vector2D a_TargetV;
	a_TargetV.x = (float)a_NewMMXZ.x;       //마우스의 좌표
	a_TargetV.y = (float)a_NewMMXZ.y;

	static RECT a_cRT;
	GetClientRect(a_hWnd, &a_cRT);
	m_CloseBtn.SetBtnRect(a_cRT.right - 100, 15); //버튼 위치 다시 대입
	m_CloseBtn.LBtnDown(a_TargetV);

	static float a_CacSpXX = 0.0f;
	static float a_CacSpYY = 0.0f;

	static float a_BtnSpXX = 0.0f;
	static float a_BtnSpYY = 0.0f;

	float m_SpXX;
	float m_SpYY;
	float m_Paddle = 50.0f;
	float m_Dx = 200.0f;
	float m_Dy = 350.0f;
	m_SpXX = a_cRT.right / 2 - 350.0f;;
	m_SpYY = a_cRT.bottom / 4 - 50.0f;

	for (int i = 0; i < 3; i++)
	{
		a_CacSpXX = m_SpXX + (i * (m_Dx + m_Paddle));
		a_CacSpYY = m_SpYY;

		a_BtnSpXX = a_CacSpXX + (m_Dx / 2) - ((m_AddBtn[i].m_BtnUpImg->GetWidth() / 1.72f) / 2.0f);
		a_BtnSpYY = a_CacSpYY + (m_Dy - 100);

		m_AddBtn[i].SetBtnRect(a_BtnSpXX, a_BtnSpYY); //버튼 위치 다시 대입
	

		m_AddBtn[i].LBtnDown(a_TargetV);

		if (m_AddBtn[0].m_isBtnDown == true)
			g_ClickState = GAME_LEFT;


	}

}

void CUIManager::LBtnUp()
{
	m_CloseBtn.LBtnUp();
	for (int i = 0; i < 3; i++)
	{
		m_AddBtn[i].LBtnUp();
		
	}

}



CUIManager g_UI_Mgr;

