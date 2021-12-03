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

	//-------ȭ���� ����� ���� ��� ���� ����
	m_hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	//m_hBrush = CreateSolidBrush(RGB(76, 181, 179)); //�ϴû�
	m_hBrush = CreateSolidBrush(RGB(0, 0, 0)); //�ϴû�
	//-------ȭ���� ����� ���� ��� ���� ����

	//���� ��� 
	HDC	hdc = GetDC(a_hWnd);  //WM_PAINT�ۿ��� hdc�����¹��
	m_BGImgDC = CreateCompatibleDC(hdc); //MainDC�� ���纻 
	m_hTexImgBMP = (HBITMAP)LoadImage(NULL, _T(".\\Bg\\BG2.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//bmp���� �ε��� �Ѵ�
	SelectObject(m_BGImgDC, m_hTexImgBMP); //���纻 DC�� �ε��� HBITMAP�� �����ؼ� ����
	ReleaseDC(a_hWnd, hdc);		//���� Main HDC�� ����

	BITMAP	bm;
	GetObject(m_hTexImgBMP, sizeof(BITMAP), &bm);	//��Ʈ�� ���� ���
	m_TexImgWidth = bm.bmWidth; //BMP���� ���� ������ ������
	m_TexImgHeight = bm.bmHeight; //BMP���� ���� ������ ������
	//���� ���

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
		//----DC ȭ�� �����
		m_hOldBrush = (HBRUSH)SelectObject(a_hdc, m_hBrush);
		m_hOldPen = (HPEN)SelectObject(a_hdc, m_hPen);
		Rectangle(a_hdc, 0, 0, a_RT.right, a_RT.bottom);
		SelectObject(a_hdc, m_hOldBrush);
		SelectObject(a_hdc, m_hOldPen);
		//----DC ȭ�� �����

		GetClientRect(a_hWnd, &a_RT); //DC ������ ������...
		//--------------------- �⺻GDI��� ��� �׸���
		if (g_hBackImgDC != NULL)
		{
			StretchBlt(a_hdc, 0, 0, a_RT.right, a_RT.bottom,
				g_hBackImgDC, 0, 0, g_BackImgWidth, g_BackImgHeight,
				SRCCOPY);

		}//if (g_hBackImgDC != NULL)
		//--------------------- �⺻GDI��� ��� �׸���
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
