#pragma once
#include "Vector2D.h"
#include <list>
#include <vector>
using namespace std;

//---------------GDI Plus
#include	<ole2.h>
#include	<gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;
//---------------GDI Plus

#include "CUnit.h"

enum ItemType
{
	IT_Gold = 0,
	IT_Silver,
	IT_Dead,
	IT_Potion,
	IT_Length,
};

//--------------------------CItem class
class CItem : public CUnit
{
public:
	ItemType	m_IT_Type;
	float		m_Duration;
	Vector2D	m_CurPos;
	float		m_HalfWidth;
	float		m_HalfHeight;
	Vector2D	a_CacIvec;
	//Image*		m_ItemImg;

public:
	CItem();
	~CItem();

public:
	bool ItemUpdate(float a_DeltaTime);
	void ItemRender(HDC a_hDC);
};
//--------------------------CItem class

class CItem_Mgr 
{
public:
	//=======Item List
	list <CItem*> m_ItemList;
	list <CItem*>::iterator m_Iiter;
	//=======Item List

	//vector<CItem*> m_CItem;
	vector<Image*>	m_ImgList;	//아이템 이미지 리스트

	void	ItemMgr_Init();						//초기화함수
	void	ItemMgr_Update(float a_DeltaTime);	//아이템 연산담당부분
	void	ItemMgr_Render(HDC a_MainDC);		//아이템 그리기 부분
	void    ItemMgr_Destroy();					//아이템 리소스 삭제부분

	void    SpawnItem(Vector2D a_StartV);		//아이템스폰
	void    ReSrcClear();						//라운드를 넘어갈때 필드에 뿌려져 있는것을 초기화
public:
	CItem_Mgr();
	~CItem_Mgr();
};

extern	CItem_Mgr	g_ItemMgr;