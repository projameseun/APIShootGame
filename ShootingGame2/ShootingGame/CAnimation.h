#pragma once

#include <vector>
using namespace std;

//----- GDI+ Image ����� ���� ��� �߰�
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image ����� ���� ��� �߰�

class CCharacter;
enum CharType
{
	CT_None =0,
	RealPlayer ,
	Player,
	Bullet,
	PlayerExplode,
	Explode,
	Gold,
	Silver,
	DeadCoin,
	Potion,
	Shield,
	Girl,
	Enemy01,
	Enemy02,
	Enemy03,
	Enemy04,
	Enemy05,
	Enemy06,
	Boss,
	CT_Length,

};

enum AniState
{
	None,
	Idle,
	Front_Walk,
	Back_Walk,
	Left_Walk,
	Right_Walk,
	Dead,
	EX_Walk, //�÷��̾����� ���
	Dead_Walk,
	Coin_Walk,
	AniLength,
};

class CAniMotion
{
public:
	vector<Image*> m_ImgList; //�̹��� ����Ʈ
public:
	CAniMotion()
	{

	}
	~CAniMotion()
	{
		//�Ҹ��ڿ��� �̹����� ���α׷� ����ÿ� �˾Ƽ� �������ش� 
		for (int ii = 0; ii < m_ImgList.size(); ii++)
		{
			//--- GDI+ ���� 
			if (m_ImgList[ii] != NULL)
			{
				delete m_ImgList[ii];
				m_ImgList[ii] = NULL;
			}
			//--- GDI+ ���� 
		}//for (int ii = 0; ii < m_ImgList.size(); ii++)

		m_ImgList.clear();

	}
	//��� �Լ� 
	void LoadTexImg(const TCHAR* a_FName)
	{
		//�ش� ��ο��� �̹��� �ҷ�����
		Image* a_pBitmap = Image::FromFile(a_FName);
		m_ImgList.push_back(a_pBitmap);
	}


};

class CAnimation
{
public:
	vector<CAniMotion*> m_AniMoList;

public:
	CAnimation();
	~CAnimation();

public:


	void CAni_LoadAnimList(CharType a_CharType);


};