#pragma once
class CBGround
{
private:

	//----------------ȭ���� Ư���� ������ �����
	HPEN	m_hPen;
	HPEN	m_hOldPen;
	HBRUSH	m_hBrush;
	HBRUSH	m_hOldBrush;
	//----------------ȭ���� Ư���� ������ �����
	////-------- BackImage �ε� ����
	HDC        g_hBackImgDC;        //�̹��� ����� DC
	HBITMAP g_hBackImgBMP;        //�̹��� �ε��� �ӽ� BMP
	int        g_BackImgWidth;        //�̹����� ���� ũ��
	int        g_BackImgHeight;    //�̹����� ���� ũ��
	////-------- BackImage �ε� ����

	//-------�̹��� ����
	HDC		m_BGImgDC;
	HBITMAP	m_hTexImgBMP;	//�ε��� bmp �������ڵ�
	int		m_TexImgWidth;
	int		m_TexImgHeight;
	//-------�̹��� ����

	
public:
	CBGround();
	~CBGround();

public:
	void BG_Init(HWND a_hWnd);		//�ʱ�ȭ�Լ�
	void BG_Update(RECT &a_RT);		//������ ���� ���κ�
	void BG_Render(HDC a_hdc, RECT &a_RT, HWND a_hWnd);   //������ �׸��� �κ�
	void BG_Destroy();
};

extern CBGround g_BGround;

