#pragma once
#include "CUnit.h"
#include <vector>

using namespace std;

//----- GDI+ Image ����� ���� ��� �߰�
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image ����� ���� ��� �߰�





class CExplode : public CUnit
{

	int     m_TrackNumber;          //����ȣ
	//----------ĳ���� �̵� ���� ����
	POINT   m_ExCurPos;               //���� ��ġ
	double  m_CacAddPosX;           //double�� �ӵ� ���� ����
	double  m_CacAddPosY;
	//----------ĳ���� �̵� ���� ����

	//Image* m_SocketImg;				//�ִ� ����ó�� ����� ������
	INT	   m_ImgSizeX;				//�̹��� ���� ������
	INT    m_ImgSizeY;				//�̹��� ���� ������

	//---------------- �ִϸ��̼� ���� ���� 
	//EXAniState m_CurEXAniState;           //���� �ִϸ��̼� ����
	//vector<CEXMotion*> m_ExList;

	int		m_NowImgCount;            //�ִ� ����ó�� ����� �̹��� ī��Ʈ
	float	m_EachAniDelay;			  //�÷��� ���� �ð�
	float	m_AniTickCount;           //���� �÷��ӱ��� �ð� Add
	int		m_CurAniInx;              //���� Ani Index
	//---------------- �ִϸ��̼� ���� ���� 
public:
	CExplode();
	~CExplode();

public:
	void CEX_Init(Image* a_LoadImg = NULL);
	void CEX_ReSetPos(int a_TrackNb, LONG a_XX, LONG a_YY); //��ŸƮ ������ ��ġ ��Ű�� �Լ�
	void CEX_Update(double a_DeltaTime, RECT* a_rt = NULL, bool a_isDeadStart = false);
	void CEX_Render(HDC a_hdc);
	void CEX_Destroy();

	//void EXLoadAnimList(int Number = 0);
	//bool EXChangeState(EXAniState newState);
	//void EXAniFrameUpdate(double a_DeltaTime);
};

