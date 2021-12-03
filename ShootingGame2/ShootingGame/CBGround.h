#pragma once
class CBGround
{
private:

	//----------------화면을 특정한 색으로 지우기
	HPEN	m_hPen;
	HPEN	m_hOldPen;
	HBRUSH	m_hBrush;
	HBRUSH	m_hOldBrush;
	//----------------화면을 특정한 색으로 지우기
	////-------- BackImage 로딩 변수
	HDC        g_hBackImgDC;        //이미지 저장용 DC
	HBITMAP g_hBackImgBMP;        //이미지 로딩용 임시 BMP
	int        g_BackImgWidth;        //이미지의 가로 크기
	int        g_BackImgHeight;    //이미지의 세로 크기
	////-------- BackImage 로딩 변수

	//-------이미지 변수
	HDC		m_BGImgDC;
	HBITMAP	m_hTexImgBMP;	//로딩된 bmp 파일의핸들
	int		m_TexImgWidth;
	int		m_TexImgHeight;
	//-------이미지 변수

	
public:
	CBGround();
	~CBGround();

public:
	void BG_Init(HWND a_hWnd);		//초기화함수
	void BG_Update(RECT &a_RT);		//게임의 연산 담당부분
	void BG_Render(HDC a_hdc, RECT &a_RT, HWND a_hWnd);   //게임의 그리기 부분
	void BG_Destroy();
};

extern CBGround g_BGround;

