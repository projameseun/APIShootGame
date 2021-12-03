#pragma once
#include "Vector2D.h"
#include "CUnit.h"



class CHero : public CUnit
{
	

	HBRUSH	m_R_brsh;
	HGDIOBJ	m_R_Old_brsh;

	INT		m_ImgSizeX;	//이미지 가로사이즈/	i
	INT    m_ImgSizeY;				//이미지 세로 사이즈
	int		m_HalfWidth = 15; //기본이미지 가로 반사이즈
	int		m_HalfHeight = 15; //기본 이미지 세로 반사이즈 

	

	HWND	m_hWnd;
	float	m_AttackSpeed = 0.1f;	//공속
	float	m_BLCycle = 0.0f;

	

public:
	CHero *m_Hero;
	int		m_CurHP;
	int		m_MaxHP;
	float	m_Speed = 500.0f;
	//--------능력치
	float m_CurAttack = 10.0f;	//주인공의 공격력
	int   m_KillCount = 0;		//킬수
	int	  m_SkillCount = 5;		//남은 스킬수
	int   m_ShieldCount = 5;    //남은 보호막 수 
	int   m_MyMoney = 100;		//유저의 골드 
	//--------능력치

	float m_STDelay = 0.5f;	//게임 리스타트시에 궁극기 딜레이주기 

public:
	Vector2D m_CurPos;
	float	 m_HalfColl = 20.0f; //주인공의 충돌 반경

	int m_GunCount = 0;
	int m_PilsaCount = 0; //필살기썻을때

public:
	CHero();
	~CHero();

public:
	virtual void Hero_Init(HWND a_hWnd);
	virtual void Hero_ReSetPos(); //스타트 지점에 위치 시키기 함수
	virtual void Hero_Update(HDC a_hdc,float a_DeltaTime, RECT &a_RT);
	virtual void Hero_Render(HDC a_hdc, double a_DeltaTime);
	virtual void Hero_Destroy();

	void HeroLimitMove(RECT &a_RT);
	void TakeDamage(float a_Damage = 10.0f);
	void Hero_ReSet();

	static void BuyHP();
	static void BuySkill();
	static void BuyShield();

};


extern CHero g_Hero;
