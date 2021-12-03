#pragma once
#include "CUnit.h"
#include <vector>

using namespace std;

//----- GDI+ Image 사용을 위한 헤더 추가
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image 사용을 위한 헤더 추가





class CExplode : public CUnit
{

	int     m_TrackNumber;          //말번호
	//----------캐릭터 이동 계산용 변수
	POINT   m_ExCurPos;               //현재 위치
	double  m_CacAddPosX;           //double형 속도 계산용 변수
	double  m_CacAddPosY;
	//----------캐릭터 이동 계산용 변수

	//Image* m_SocketImg;				//애니 소켓처럼 사용할 포인터
	INT	   m_ImgSizeX;				//이미지 가로 사이즈
	INT    m_ImgSizeY;				//이미지 세로 사이즈

	//---------------- 애니메이션 관련 변수 
	//EXAniState m_CurEXAniState;           //현재 애니메이션 상태
	//vector<CEXMotion*> m_ExList;

	int		m_NowImgCount;            //애니 소켓처럼 사용할 이미지 카운트
	float	m_EachAniDelay;			  //플레임 간격 시간
	float	m_AniTickCount;           //다음 플레임까지 시간 Add
	int		m_CurAniInx;              //진행 Ani Index
	//---------------- 애니메이션 관련 변수 
public:
	CExplode();
	~CExplode();

public:
	void CEX_Init(Image* a_LoadImg = NULL);
	void CEX_ReSetPos(int a_TrackNb, LONG a_XX, LONG a_YY); //스타트 지점에 위치 시키기 함수
	void CEX_Update(double a_DeltaTime, RECT* a_rt = NULL, bool a_isDeadStart = false);
	void CEX_Render(HDC a_hdc);
	void CEX_Destroy();

	//void EXLoadAnimList(int Number = 0);
	//bool EXChangeState(EXAniState newState);
	//void EXAniFrameUpdate(double a_DeltaTime);
};

