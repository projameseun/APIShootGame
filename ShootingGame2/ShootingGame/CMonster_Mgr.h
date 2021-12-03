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

class CHero; //�浹�ҷ���
//--------------CMonster
class CMonster : public CUnit
{
public:
	bool	m_isActive;
	float	m_MaxHP = 100.0f;
	float	m_MonHp = 100.0f;

	//-----���� ��ǥ ���� ������....
	Vector2D	m_CurPos;
	float		m_Speed = 150.0f;
	Vector2D	m_DirVec;
	float		m_HalfColl = 17; //������ �浹�ݰ�
	//-----���� ��ǥ ���� ������....


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
	//��������
	HBRUSH	m_R_brsh;  
	HGDIOBJ	m_R_Old_brsh;
	//��������
public:
	//vector<Image*>	m_ImgList;	//���� �̹��� ����Ʈ
	vector<CMonster*> m_MonList; //�޸� Ǯ��� 
	RECT	m_cRT;					//���� ����

	int		m_SpawnLim = 6;		//������ �����ϴ� ���� ������ ����
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
	void ReSrcClear();	//���带 �Ѿ�� �ʵ忡 �������� �ִ� ��� ���� ����
	
	CharType GetSpMonType();  //���̵��� ���� ������ ���� ������ �����Y�� �Լ�
	float   GetSpTimeLevel(); //���̵��� ���� ���� �����ֱ⸦ �������ִ� �Լ�

};
//--------------CMonster_Mgr

extern CMonster_Mgr g_Mon_Mgr;