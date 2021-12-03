#include "stdafx.h"
#include "CExplode.h"
#include "GlovalValue.h"


CExplode::CExplode()
{
	


}


CExplode::~CExplode()
{
}

void CExplode::CEX_Init(Image * a_LoadImg)
{
	if (m_SocketImg == NULL)
	{
		m_SocketImg = a_LoadImg;
	}

}

void CExplode::CEX_ReSetPos(int a_TrackNb, LONG a_XX, LONG a_YY)
{
	m_TrackNumber = a_TrackNb;

	m_ExCurPos.x = a_XX;
	m_ExCurPos.y = a_YY;

	m_CacAddPosX = m_ExCurPos.x;
	m_CacAddPosY = m_ExCurPos.y;


	ChangeState(Idle);

}

void CExplode::CEX_Update(double a_DeltaTime, RECT * a_rt, bool a_isDeadStart)
{
	if (a_rt == NULL)
		return;

	m_ExCurPos.x = m_CacAddPosX;
	m_ExCurPos.y = m_CacAddPosY;

	ChangeState(Dead_Walk);
	//------------------- �ִϸ��̼� �÷��� ��� �κ� 
	CUnit::Update_Unit(a_DeltaTime);
	//------------------- �ִϸ��̼� �÷��� ��� �κ� 


}

void CExplode::CEX_Render(HDC a_hdc)
{
	if (m_SocketImg == NULL)  //�ִ� ���Ͽ� ���� ���� �ִ��� Ȯ���� ���� ������ġ
		return;

	//---------------------- �� �׸���
	m_ImgSizeX = (INT)(m_SocketImg->GetWidth());
	m_ImgSizeY = (INT)(m_SocketImg->GetHeight());

	////�׾����� ǥ�� 
	//	if (Idle)
	//	{
	//		m_CurPos.x = 0;
	//	}
	//

	Graphics graphics(a_hdc);  // Bitblt���� ����ϴ� �� g_hBackdc�� ������ ��.

	graphics.DrawImage(m_SocketImg,
		Rect(0, 0, m_ImgSizeX, m_ImgSizeY),
		0, 0, m_SocketImg->GetWidth(), m_SocketImg->GetHeight(),
		UnitPixel);


}

void CExplode::CEX_Destroy()
{
	
}


