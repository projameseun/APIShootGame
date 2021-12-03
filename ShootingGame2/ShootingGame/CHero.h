#pragma once
#include "Vector2D.h"
#include "CUnit.h"



class CHero : public CUnit
{
	

	HBRUSH	m_R_brsh;
	HGDIOBJ	m_R_Old_brsh;

	INT		m_ImgSizeX;	//�̹��� ���λ�����/	i
	INT    m_ImgSizeY;				//�̹��� ���� ������
	int		m_HalfWidth = 15; //�⺻�̹��� ���� �ݻ�����
	int		m_HalfHeight = 15; //�⺻ �̹��� ���� �ݻ����� 

	

	HWND	m_hWnd;
	float	m_AttackSpeed = 0.1f;	//����
	float	m_BLCycle = 0.0f;

	

public:
	CHero *m_Hero;
	int		m_CurHP;
	int		m_MaxHP;
	float	m_Speed = 500.0f;
	//--------�ɷ�ġ
	float m_CurAttack = 10.0f;	//���ΰ��� ���ݷ�
	int   m_KillCount = 0;		//ų��
	int	  m_SkillCount = 5;		//���� ��ų��
	int   m_ShieldCount = 5;    //���� ��ȣ�� �� 
	int   m_MyMoney = 100;		//������ ��� 
	//--------�ɷ�ġ

	float m_STDelay = 0.5f;	//���� ����ŸƮ�ÿ� �ñر� �������ֱ� 

public:
	Vector2D m_CurPos;
	float	 m_HalfColl = 20.0f; //���ΰ��� �浹 �ݰ�

	int m_GunCount = 0;
	int m_PilsaCount = 0; //�ʻ�⛧����

public:
	CHero();
	~CHero();

public:
	virtual void Hero_Init(HWND a_hWnd);
	virtual void Hero_ReSetPos(); //��ŸƮ ������ ��ġ ��Ű�� �Լ�
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
