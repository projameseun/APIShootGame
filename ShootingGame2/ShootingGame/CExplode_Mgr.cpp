#include "stdafx.h"
#include "CExplode_Mgr.h"
#include "GlovalValue.h"


CExplode_Mgr::CExplode_Mgr()
{
}


CExplode_Mgr::~CExplode_Mgr()
{
}

void CExplode_Mgr::CEM_Init(HWND a_hWnd)
{
	m_hWnd = a_hWnd;

	m_Explode.SetAni_Rsc(Explode);

	CEM_ReSetPos(); //���� ��ġ�� ��ǥ �̵�

}

void CExplode_Mgr::CEM_ReSetPos()
{
	

	RECT a_Rect;
	GetClientRect(m_hWnd, &a_Rect); // Ŭ���̾�Ʈ ȭ���� ũ�⸦ �޴´�
	//----- ĳ���� �ʱ�ȭ �κ�
	int a_PosX = 100;
	int a_PosY = 100;
	//int a_YTab = a_Rect.bottom / 7;

	m_Explode.CEX_ReSetPos(0, a_PosX, a_PosY);


	//----- ĳ���� �ʱ�ȭ �κ�

}

void CExplode_Mgr::CEM_Update(double a_DeltaTime, RECT * a_rt, bool a_isDeadStart)
{
	if(a_isDeadStart == true)
	m_Explode.CEX_Update(a_DeltaTime, a_rt, a_isDeadStart);

	else
	{
		return;
	}
}

void CExplode_Mgr::CEM_Render(HDC a_hdc)
{
	m_Explode.CEX_Render(a_hdc); //--------------ĳ���� �׸��� �κ� 

}

void CExplode_Mgr::CEM_Destroy()
{
	//-------- ĳ���� ���ҽ� ����

	m_Explode.CEX_Destroy();

	//-------- ĳ���� ���ҽ� ����

	//-------- �̹��� ����
	//for (int ii = 0; ii < m_ImgList.size(); ii++)
	//{
	//	if (m_ImgList[ii] != NULL)
	//	{
	//		delete m_ImgList[ii];
	//		m_ImgList[ii] = NULL;
	//	}
	//}
	//m_ImgList.clear();
	////-------- �̹��� ����


}

CExplode_Mgr g_ExplodeMgr;
