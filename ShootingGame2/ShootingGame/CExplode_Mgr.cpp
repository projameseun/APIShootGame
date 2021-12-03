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

	CEM_ReSetPos(); //시작 위치로 좌표 이동

}

void CExplode_Mgr::CEM_ReSetPos()
{
	

	RECT a_Rect;
	GetClientRect(m_hWnd, &a_Rect); // 클라이언트 화면의 크기를 받는다
	//----- 캐릭터 초기화 부분
	int a_PosX = 100;
	int a_PosY = 100;
	//int a_YTab = a_Rect.bottom / 7;

	m_Explode.CEX_ReSetPos(0, a_PosX, a_PosY);


	//----- 캐릭터 초기화 부분

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
	m_Explode.CEX_Render(a_hdc); //--------------캐릭터 그리는 부분 

}

void CExplode_Mgr::CEM_Destroy()
{
	//-------- 캐릭터 리소스 제거

	m_Explode.CEX_Destroy();

	//-------- 캐릭터 리소스 제거

	//-------- 이미지 제거
	//for (int ii = 0; ii < m_ImgList.size(); ii++)
	//{
	//	if (m_ImgList[ii] != NULL)
	//	{
	//		delete m_ImgList[ii];
	//		m_ImgList[ii] = NULL;
	//	}
	//}
	//m_ImgList.clear();
	////-------- 이미지 제거


}

CExplode_Mgr g_ExplodeMgr;
