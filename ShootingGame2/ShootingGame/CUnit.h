#pragma once
#include "CAnimation.h"


class CUnit
{

public:
	CharType m_CharType;	//캐릭터종류가구별
	CAnimation *m_RefAni;	//캐릭터 타입에 따라 애니메이션 데이터를 바꿔 끼는곳 레퍼런스만 주소만 바꿔주는 상황

	//애니미에션 관련변수
	Image	*m_SocketImg;	//애니 소켓처럼 사용할 포인터
	AniState m_CurAniState; //현재 애니메이션 상태


	int		m_NowImgCount;	//애니 소켓처럼 사용할 이미지 카운트
	float		m_EachAniDelay; //플레임 간격시간
	float		m_AniTickCount; //다음 플레인까지 시간 Add
	int		m_CurAniInx;    //진행 Ani Idex
	//애니미에션 관련변수
	int		m_ImgSizeX;
	int		m_ImgSizeY;
	int		m_HalfWidth = 15;
	int		m_HalfHeight = 15;

public:
	CUnit();
	~CUnit();

	virtual void Init_Unit(HWND a_hWnd);
	virtual void Update_Unit(float a_DeltaTime);
	virtual void Render_Unit(HDC a_hDc);
	virtual void Destroy_Unit();

	void SetAni_Rsc(CharType a_CharType);
	void LoadUnitSize();
	bool ChangeState(AniState newState);
	void AniFrameUpdate(double a_Deltatime);
};

