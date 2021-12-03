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
	vector<Image*>	m_ImgList;	//������ �̹��� ����Ʈ

	void	ItemMgr_Init();						//�ʱ�ȭ�Լ�
	void	ItemMgr_Update(float a_DeltaTime);	//������ ������κ�
	void	ItemMgr_Render(HDC a_MainDC);		//������ �׸��� �κ�
	void    ItemMgr_Destroy();					//������ ���ҽ� �����κ�

	void    SpawnItem(Vector2D a_StartV);		//�����۽���
	void    ReSrcClear();						//���带 �Ѿ�� �ʵ忡 �ѷ��� �ִ°��� �ʱ�ȭ
public:
	CItem_Mgr();
	~CItem_Mgr();
};

extern	CItem_Mgr	g_ItemMgr;