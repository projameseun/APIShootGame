#pragma once

#include "Vector2D.h"

#include <vector>
using namespace std;
//---------------GDI Plus
#include	<ole2.h>
#include	<gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;
//---------------GDI Plus
#include "CUnit.h"

class CHero; //충돌할려고
//--------------CMonster
class CMonster : public CUnit
{
public:
	bool	m_isActive;
	float	m_MaxHP = 100.0f;
	float	m_MonHp = 100.0f;

	//-----몬스터 좌표 계산용 변수들....
	Vector2D	m_CurPos;
	float		m_Speed = 150.0f;
	Vector2D	m_DirVec;
	float		m_HalfColl = 17; //몬스터의 충돌반경
	//-----몬스터 좌표 계산용 변수들....


public:
	CMonster();
	~CMonster();

public:
	void Init_Unit();
	void Update_Unit(float a_DeltaTime, CHero& a_Hero);
	void Render_Unit(HDC a_hDC, HBRUSH&a_R_brsh);
	void Destroy_Unit();
	void Reset_Unit();

	void Spawn(float a_XX, float a_YY);
	void LoadUnitSize();
	void TakeDamage(float a_Value = 10.0f);
};
//--------------CMonster

//--------------CMonster_Mgr
class CMonster_Mgr 
{
private:
	//에너지바
	HBRUSH	m_R_brsh;  
	HGDIOBJ	m_R_Old_brsh;
	//에너지바
public:
	//vector<Image*>	m_ImgList;	//몬스터 이미지 리스트
	vector<CMonster*> m_MonList; //메모리 풀방식 
	RECT	m_cRT;					//계산용 변수

	int		m_SpawnLim = 6;		//핃르에 등장하는 몬스터 마리수 제어
	 int	g_MonCount = 0;
public:
	CMonster_Mgr();
	~CMonster_Mgr();

public:
	void MonMgr_Init();
	void MonMgr_Update(float a_DeltaTime, HWND a_hWnd, CHero& a_Hero);
	void MonMgr_Render(HDC a_hDC);
	void MonMgr_Destroy();
	void MonMgr_Reset();

	void SpawnMonster(float a_DeltaTime, HWND a_hWnd);
	void ReSrcClear();	//라운드를 넘어갈때 필드에 ㅈ등장해 있는 모든 몬스터 리셋
	
	CharType GetSpMonType();  //난이도에 따라서 등장할 몬스터 종류를 리턴햊는 함수
	float   GetSpTimeLevel(); //난이도에 따라서 몬스터 스폰주기를 리턴해주는 함수

};
//--------------CMonster_Mgr

extern CMonster_Mgr g_Mon_Mgr;