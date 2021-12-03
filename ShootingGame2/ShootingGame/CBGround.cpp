#include "stdafx.h"
#include "CBGround.h"
#include "GlovalValue.h"

CBGround::CBGround()
{
}


CBGround::~CBGround()
{
}

void CBGround::BG_Init(HWND a_hWnd)
{

	//-------화면을 지우기 위한 펜과 블러쉬 생성
	m_hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	//m_hBrush = CreateSolidBrush(RGB(76, 181, 179)); //하늘색
	m_hBrush = CreateSolidBrush(RGB(0, 0, 0)); //하늘색
	//-------화면을 지우기 위한 펜과 블러쉬 생성

	//실제 배경 
	HDC	hdc = GetDC(a_hWnd);  //WM_PAINT밖에서 hdc얻어오는방법
	m_BGImgDC = CreateCompatibleDC(hdc); //MainDC의 복사본 
	m_hTexImgBMP = (HBITMAP)LoadImage(NULL, _T(".\\Bg\\BG2.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//bmp파일 로딩을 한다
	SelectObject(m_BGImgDC, m_hTexImgBMP); //복사본 DC에 로딩된 HBITMAP을 선택해서 복사
	ReleaseDC(a_hWnd, hdc);		//얻어온 Main HDC를 해제

	BITMAP	bm;
	GetObject(m_hTexImgBMP, sizeof(BITMAP), &bm);	//비트맵 정보 얻기
	m_TexImgWidth = bm.bmWidth; //BMP원본 가로 사이즈 얻어오기
	m_TexImgHeight = bm.bmHeight; //BMP원본 세로 사이즈 얻어오기
	//실제 배경

	if (m_hTexImgBMP != NULL)
	{
		DeleteObject(m_hTexImgBMP);
		g_hBackImgBMP = NULL;
	}




}

void CBGround::BG_Update(RECT & a_RT)
{
	

}

void CBGround::BG_Render(HDC a_hdc, RECT & a_RT, HWND a_hWnd)
{

	

	if (g_GameState == GAME_REALSTART || g_GameState == GAME_MOUSESTART || 
		g_GameState == GAME_PILSALSTART || g_GameState == GAME_EXPLODE || g_GameState == GAME_BOSS
		|| g_GameState == GAME_BOSTART)
	{
		StretchBlt(a_hdc, 0, 0, a_RT.right, a_RT.bottom, m_BGImgDC,
			0, 0, m_TexImgWidth, m_TexImgHeight, SRCCOPY);
	}

	else 
	{
		//----DC 화면 지우기
		m_hOldBrush = (HBRUSH)SelectObject(a_hdc, m_hBrush);
		m_hOldPen = (HPEN)SelectObject(a_hdc, m_hPen);
		Rectangle(a_hdc, 0, 0, a_RT.right, a_RT.bottom);
		SelectObject(a_hdc, m_hOldBrush);
		SelectObject(a_hdc, m_hOldPen);
		//----DC 화면 지우기

		GetClientRect(a_hWnd, &a_RT); //DC 사이즈 얻어오기...
		//--------------------- 기본GDI방식 배경 그리기
		if (g_hBackImgDC != NULL)
		{
			StretchBlt(a_hdc, 0, 0, a_RT.right, a_RT.bottom,
				g_hBackImgDC, 0, 0, g_BackImgWidth, g_BackImgHeight,
				SRCCOPY);

		}//if (g_hBackImgDC != NULL)
		//--------------------- 기본GDI방식 배경 그리기
	}

}



void CBGround::BG_Destroy()
{
	if (m_hPen != NULL)
	{
		DeleteObject(m_hPen);
		m_hPen = NULL;
	}

	if (m_hOldPen != NULL)
	{
		DeleteObject(m_hOldPen);
		m_hOldPen = NULL;
	}


	if (m_hBrush != NULL)
	{
		DeleteObject(m_hBrush);
		m_hBrush = NULL;
	}


	if (m_hOldBrush != NULL)
	{
		DeleteObject(m_hOldBrush);
		m_hOldBrush = NULL;
	}
	
	if (m_BGImgDC != NULL)
	{
		DeleteDC(m_BGImgDC);
		m_BGImgDC = NULL;
	}

	if (m_hTexImgBMP != NULL)
	{
		DeleteObject(m_hTexImgBMP);
		m_hTexImgBMP = NULL;
	}

}

CBGround g_BGround;
