#pragma once
#include "Vector2D.h"
#include "CUnit.h"
#include "CAnimation.h"


class CMonster_Mgr;

class CHero;

class CBullet : public CUnit
{
public:



	bool		m_BLActive;	//총알의 액티브 상태

	float		m_LifeTime;	//총알의 라이프타임(총알을 몇초동안 날아가게 할것인가)
	Vector2D	m_CurPos;	//총알의 현재위치
	Vector2D	m_DirVec;	//총알의 날아가는 방향벡터
	float		m_MoveSpeed;	//총알의 이동속도

	float		m_HalfColl;	//충돌 반경

	//Image* m_BulletSocketImg;				//애니 소켓처럼 사용할 포인터
	INT	   m_BulletImgSizeX;				//이미지 가로 사이즈
	INT    m_BulletImgSizeY;				//이미지 세로 사이즈
	int		m_HalfWidth = 15; //기본이미지 가로 반사이즈
	int		m_HalfHeight = 15; //기본 이미지 세로 반사이즈 



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

	
	//vector<CBullet*> m_BullList;	//총알 풀 방식
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


