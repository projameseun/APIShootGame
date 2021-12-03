#pragma once
#include "CAnimation.h"


class CUnit
{

public:
	CharType m_CharType;	//ĳ��������������
	CAnimation *m_RefAni;	//ĳ���� Ÿ�Կ� ���� �ִϸ��̼� �����͸� �ٲ� ���°� ���۷����� �ּҸ� �ٲ��ִ� ��Ȳ

	//�ִϹ̿��� ���ú���
	Image	*m_SocketImg;	//�ִ� ����ó�� ����� ������
	AniState m_CurAniState; //���� �ִϸ��̼� ����


	int		m_NowImgCount;	//�ִ� ����ó�� ����� �̹��� ī��Ʈ
	float		m_EachAniDelay; //�÷��� ���ݽð�
	float		m_AniTickCount; //���� �÷��α��� �ð� Add
	int		m_CurAniInx;    //���� Ani Idex
	//�ִϹ̿��� ���ú���
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

