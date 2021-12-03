#pragma once
#include "Vector2D.h"
#include <functional> //function
using namespace std;  //function
//--------------------- GDI+ 사용을 위한 헤더 추가
#include <ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//--------------------- GDI+ 사용을 위한 헤더 추가
class CButton
{
public:
	bool		m_isBtnDown;
	Image*		m_BtnUpImg;
	Image*		m_BtnDownImg;

	Vector2D	m_LT_Pos;
	Vector2D	m_WH_Size;

	ColorMatrix m_DownCM; //DOwnImg가 없을대
	function<void(void)>	ClickCallback = NULL; //STL에서 제공해주는 함수 포인터 변수생성

public:
	CButton();
	~CButton();
	void SetBtnRect(float a_LeftPos, float a_TopPos,
		float a_WSize = 0.0f, float a_HSize = 0.0f);

	void Load_Rsc(const TCHAR* a_BtnUpStr, const TCHAR *a_BtnDownStr = NULL);
	void BtnRender(HDC a_hDC);
	void Destroy();

	void LBtnDown(Vector2D a_MosPos);
	bool LBtnUp();
	void OnClick_AddListener(function<void(void)> Callback = NULL); //PointerUp
};

class CUIManager
{
	//icon ui 변수들
	Image * m_GUIBack = NULL;
	Image * m_HP_Icon = NULL;



	TCHAR m_StrBuff[128];
	HFONT m_Font_26Godic = NULL;
	HFONT hFont_100 = NULL;
	HFONT hFont_50 = NULL;

	HFONT m_OldFont;

	//icon ui 변수들
	float m_DeltaTime = 0.0f;
	HFONT a_hOldFont = NULL;
	HFONT m_Font_200_Gulim = NULL;
	HFONT m_Font_50_Batang = NULL;
	HFONT m_Font_RT_Fiophi = NULL;
	HFONT m_Font_100_Batang = NULL;
	HFONT m_Font_40_Batang = NULL;
	HFONT m_Font_30_Gulim = NULL;
	HFONT m_Font_Default = NULL;

	bool   m_bPushBtnDU = false;
	Image *m_pBtnDownImg = NULL;
	Image *m_pBtnUpImg = NULL;

	int m_TPCount = 5; //타이핑카운트
	int m_Count = 3;
	int m_BossCount = 3;
	int m_EndingCount = 0;


public:
	CUIManager();
	~CUIManager();

	//shop
public:
	bool		m_ShopOnOff;

private:
	Image		*m_ShopBase;
	ColorMatrix	m_AlphaCM;

	HFONT		m_HumanF;

	CButton		m_CloseBtn; //닫기 버튼

	Image*		m_ShopBG[3];
	Image*		m_Image[3];
	Image*      m_CoinImg[3];
	CButton     m_AddBtn[3];
	//shop

public:

	void UIMgrInit(HDC a_hdc, RECT &a_RT);
	void UIMgrUpdate(double a_DeltaTime, HWND a_hWnd,void(*NextLevelFunc)() = NULL, 
					void(*ReSetGameFunc)() = NULL);
	void UIMgrRender(HDC a_hdc, RECT& a_RT, float a_Deltatime);
	void UIMgrDestroy();

	void GameReady_Render(HDC a_hdc, RECT &a_RT);
	void GameInven_Render(HDC a_hdc, RECT &a_RT,float a_Deltatime);
	void GameEnd_Render(HDC a_hdc, RECT &a_RT);
	void GameStart_Render(HDC a_hdc, RECT &a_RT);
	void GameEnding_Render(HDC a_hdc, RECT &a_RT);


	void UserInfoPanel(HDC a_MainDC, Graphics &graphics, RECT & a_RT,float m_Deltatime);


	void StoreInit(HDC a_hdc, RECT& a_RT);
	void StoreRender(HDC a_MainDC, Graphics& graphics, RECT& a_RT, float a_Deltatime);
	void StoreDestroy();

	void LBtnDown(HWND a_hWnd);
	void LBtnUp();
};


extern CUIManager g_UI_Mgr;