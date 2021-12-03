#pragma once
#include "Vector2D.h"
#include "CUnit.h"
#include "CAnimation.h"


class CMonster_Mgr;

class CHero;

class CBullet : public CUnit
{
public:



	bool		m_BLActive;	//�Ѿ��� ��Ƽ�� ����

	float		m_LifeTime;	//�Ѿ��� ������Ÿ��(�Ѿ��� ���ʵ��� ���ư��� �Ұ��ΰ�)
	Vector2D	m_CurPos;	//�Ѿ��� ������ġ
	Vector2D	m_DirVec;	//�Ѿ��� ���ư��� ���⺤��
	float		m_MoveSpeed;	//�Ѿ��� �̵��ӵ�

	float		m_HalfColl;	//�浹 �ݰ�

	//Image* m_BulletSocketImg;				//�ִ� ����ó�� ����� ������
	INT	   m_BulletImgSizeX;				//�̹��� ���� ������
	INT    m_BulletImgSizeY;				//�̹��� ���� ������
	int		m_HalfWidth = 15; //�⺻�̹��� ���� �ݻ�����
	int		m_HalfHeight = 15; //�⺻ �̹��� ���� �ݻ����� 



public:
	CBullet();
	~CBullet();

	void	BulletInit(Image* a_LoadImg = NULL);
	bool	BulletUpdate(float a_DeltaTime,HWND a_hWnd);
	void	BulletRender(HDC a_hDC);
	void    BulletSpawn(float a_XX, float a_YY, int num);
	void    BulletDestroy();

	
};//class CBullet

class CBullet_Mgr
{
public:

	
	//vector<CBullet*> m_BullList;	//�Ѿ� Ǯ ���
	//vector<Image*> m_BullImgList;

	HWND m_hWnd;
	vector<CBullet*> m_BullList;
	float DelTime = 0;

public:
	CBullet_Mgr();
	~CBullet_Mgr();

public:
	void BLMgr_Init(HWND a_hWnd);
	void BLMgr_Update(HDC a_hdc, float a_DeltaTime, HWND a_hWnd, CMonster_Mgr *a_Mon_Mgr = NULL, CHero *a_Hero = NULL);
	void BLMgr_Render(HDC a_hDC, double a_DeltaiTime);
	void BLMgr_Destroy();

	void SpawnBullet(Vector2D a_StartV, Vector2D a_TargetV, float a_DeltaTime);

	void ReSrcClear();
};

extern CBullet_Mgr g_Bullet_Mgr;
extern CBullet g_Bullet;


