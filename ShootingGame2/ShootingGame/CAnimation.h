#pragma once

#include <vector>
using namespace std;

//----- GDI+ Image 사용을 위한 헤더 추가
#include <ole2.h>  
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//----- GDI+ Image 사용을 위한 헤더 추가

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
	EX_Walk, //플레이어폭발 장면
	Dead_Walk,
	Coin_Walk,
	AniLength,
};

class CAniMotion
{
public:
	vector<Image*> m_ImgList; //이미지 리스트
public:
	CAniMotion()
	{

	}
	~CAniMotion()
	{
		//소멸자에서 이미지는 프로그램 종료시에 알아서 다지워준다 
		for (int ii = 0; ii < m_ImgList.size(); ii++)
		{
			//--- GDI+ 해제 
			if (m_ImgList[ii] != NULL)
			{
				delete m_ImgList[ii];
				m_ImgList[ii] = NULL;
			}
			//--- GDI+ 해제 
		}//for (int ii = 0; ii < m_ImgList.size(); ii++)

		m_ImgList.clear();

	}
	//모션 함수 
	void LoadTexImg(const TCHAR* a_FName)
	{
		//해당 경로에서 이미지 불러오기
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