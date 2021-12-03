#pragma once
#include "Vector2D.h"
#include "CUnit.h"

class CHero;
class CCharacter : public CUnit
{

	HWND	m_hWnd;
public:
	int		m_BossCurHP = 1000.0f;
	int		m_BossMaxHP = 1000.0f;
	//----------캐릭터 이동 계산용 변수
	POINT   m_CurPos;               //현재 위치
	float m_CacAddPosX;          
	float m_CacAddPosY;
	//----------캐릭터 이동 계산용 변수
	Vector2D m_BossCurPos;

	int m_Count = 0;
	int m_WalkCount = 0;
	int m_InVestCount = 0;

	float		m_Speed = 150.0f;
	Vector2D	m_DirVec;
	float	 m_HalfColl = 20.0f; //주인공의 충돌 반경
	
	float	m_AttackSpeed = 0.1f;	//공속
	float	m_BLCycle = 0.0f;

	float	m_BossAtCount = 0;
	float   m_BossPiCount = 0;

private:
	HBRUSH	m_R_brsh;
	HGDIOBJ	m_R_Old_brsh;
public:
	CCharacter();
	~CCharacter();


public:
	void CChar_Init(Image* a_LoadImg = NULL);
	void CChar_ReSetPos(int a_TrackNb, LONG a_XX, LONG a_YY); //스타트 지점에 위치 시키기 함수
	void CChar_Update(HDC a_hdc ,double a_DeltaTime, RECT* a_rt = NULL, bool a_isRaceStart = false);
	void CChar_RealUpdate(HDC a_hdc, double a_DeltaTime, RECT* a_rt = NULL, bool a_isRealStart = false);
	void CChar_Render(HDC a_hdc,double a_DeltaTime);
	void CChar_Destroy();

	void Boss_ReSetPos(int a_TrackNb, LONG a_XX, LONG a_YY); //스타트 지점에 위치 시키기 함수
	void Boss_Update(HDC a_hdc, double a_DeltaTime, CHero &a_Hero);
	void Boss_Render(HDC a_hdc, double a_DeltaTime);
};

