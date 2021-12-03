#include "stdafx.h"
#include "CItem_Mgr.h"
#include "CHero.h"
#include "CAnimation.h"
#include "CHero.h"
#include "CSound.h"
#include "GlovalValue.h"

CItem::CItem()
{

	m_IT_Type = IT_Gold;
	m_Duration = 10.0f;
	m_HalfWidth = 0.0f;
	m_HalfHeight = 0.0f;
	//m_ItemImg = NULL;

}

CItem::~CItem()
{
}


CItem_Mgr::CItem_Mgr()
{


}



CItem_Mgr::~CItem_Mgr()
{
}



bool CItem::ItemUpdate(float a_DeltaTime)
{
	m_Duration = m_Duration - a_DeltaTime;
	if (m_Duration < 0.0f)
	{
		return false; //�����ð��ڿ� �������ش�
	}

	a_CacIvec = g_Hero.m_CurPos - m_CurPos;
	if (a_CacIvec.Magnitude() < (g_Hero.m_HalfColl + m_HalfWidth)) //������ ������
	{
		g_Sound.UpdateWav(CoinSound);
		if (m_IT_Type == IT_Potion)
		{
			g_Hero.m_CurHP += 20;
			if (g_Hero.m_MaxHP < g_Hero.m_CurHP)
			{
				g_Hero.m_CurHP = g_Hero.m_MaxHP;
			}

		}//if (m_IT_Type == IT_Potion)
		else if (m_IT_Type == IT_Gold)
		{
			g_Hero.m_MyMoney += 100;
		}//else if (m_IT_Type == IT_Gold)
		else if (m_IT_Type == IT_Silver)
		{
			g_Hero.m_MyMoney += 50;
		}//else if (m_IT_Type == IT_Silver)
		return false;
	}//	if (a_CacIvec.Magnitude() < (g_Hero.m_HalfColl + m_HalfWidth))
	//ChangeState(Idle);
	CUnit::Update_Unit(a_DeltaTime);
	g_Sound.ResetWav(CoinSound);
	return true;
}

void CItem::ItemRender(HDC a_hDC)
{
	if (m_SocketImg == NULL)
		return;

	/*static float a_HalfXX = 10.0f;
	static float a_HalfYY = 10.0f;

	a_HalfXX = (float)(int)(m_ItemImg->GetWidth() * 0.5f);
	a_HalfYY = (float)(int)(m_ItemImg->GetHeight() * 0.5f);*/

	Graphics graphics(a_hDC);
	graphics.DrawImage(m_SocketImg, m_CurPos.x - m_HalfWidth, m_CurPos.y - m_HalfHeight,
		(float)m_SocketImg->GetWidth(), (float)m_SocketImg->GetHeight());

}



void CItem_Mgr::ItemMgr_Init()
{
	//--------������ �̹��� �ε��ϱ�
	Image *a_ImgNode = NULL;
	for (int aii = 0; aii < (int)IT_Length; aii++)
	{
		a_ImgNode = NULL;
		if (aii == (int)IT_Gold)
		{
			a_ImgNode = Image::FromFile(_T(".\\Reso\\Coin\\Gold\\Gold01.png"));
		}
		else if (aii == (int)IT_Silver)
		{
			a_ImgNode = Image::FromFile(_T(".\\Reso\\Coin\\Silver\\Silver01.png"));
		}
		else if (aii == (int)IT_Dead)
		{
			a_ImgNode = Image::FromFile(_T(".\\Reso\\Coin\\DeadCoin\\Dead01.png"));
		}
		else if (aii == (int)IT_Potion)
		{
			a_ImgNode = Image::FromFile(_T(".\\Reso\\Potion\\potion.png"));
		}
		m_ImgList.push_back(a_ImgNode);
	}//for (int aii = 0; aii < (int)IT_Length; aii++)

}

void CItem_Mgr::ItemMgr_Update(float a_DeltaTime)
{
	//CAni_ChangeState(Idle);
	//CAni_AniFrameUpdate(a_DeltaTime);
	//-----------------�߰��� ���ǿ� �ɸ��� ��� �����۵��� �����ϴ¹��
	if (!m_ItemList.empty())
	{
		for (m_Iiter = m_ItemList.begin(); m_Iiter != m_ItemList.end();)
		{
			if ((*m_Iiter)->ItemUpdate(a_DeltaTime) == false)
			{
				if ((*m_Iiter) != NULL)
				{
					delete (*m_Iiter);
					(*m_Iiter) = NULL;
				}

				m_Iiter = m_ItemList.erase(m_Iiter); //erase() ���� it�� �������� ����Ű�� �ǹǷ� it�� ������Ű�� �ʴ´�.
			}//if ((*m_Iiter)->ItemUpdate(a_DeltaTime) == false)
			else
			{
				++m_Iiter;
			}
		}//	for (m_Iiter = m_ItemList.begin(); m_Iiter != m_ItemList.end();)
	}//if (!m_ItemList.empty())
	//-----------------�߰��� ���ǿ� �ɸ��� ��� �����۵��� �����ϴ¹��

	

}

void CItem_Mgr::ItemMgr_Render(HDC a_MainDC)
{
	//--------������ �׷��ֱ�
	if (!m_ItemList.empty())
	{
		for (m_Iiter = m_ItemList.begin(); m_Iiter != m_ItemList.end(); m_Iiter++)
		{
			if ((*m_Iiter != NULL))
			{
				(*m_Iiter)->ItemRender(a_MainDC);
			}
		}//for (m_Iiter = m_ItemList.begin(); m_Iiter != m_ItemList.end(); m_Iiter++)
	}
	//--------������ �׷��ֱ�

}

void CItem_Mgr::ItemMgr_Destroy()
{
	//------------������ �̹��� �����ϱ�
	for (int i = 0; i < (int)IT_Length; i++)
	{
		if (m_ImgList[i] != NULL)
		{
			delete m_ImgList[i];
			m_ImgList[i] = NULL;
		}
	}

	m_ImgList.clear();
	//------------������ �̹��� �����ϱ�

	ReSrcClear();
}

void CItem_Mgr::SpawnItem(Vector2D a_StartV)
{
	int a_CacRand = rand() % 11;
	static CItem *a_INode = NULL;
	a_INode = NULL;

	if (a_CacRand == 0)
	{
		a_INode = new CItem();
		a_INode->m_IT_Type = IT_Potion;
	/*	a_INode->m_CharType = Potion;
		a_INode->SetAni_Rsc(Potion);*/
		
		//CAni_ChangeState(Idle);
		
	}
	else if (1 <= a_CacRand && a_CacRand <= 2)
	{
		a_INode = new CItem();
		a_INode->m_IT_Type - IT_Gold;
		a_INode->m_CharType = Gold;
		a_INode->SetAni_Rsc(Gold);
		
	}
	else if (8 <= a_CacRand && a_CacRand <= 9)
	{
		a_INode = new CItem();
		a_INode->m_IT_Type = IT_Silver;
		a_INode->m_CharType = Silver;
		a_INode->SetAni_Rsc(Silver);

	}
	else if (a_CacRand == 10)
	{
		a_INode = new CItem();
		a_INode->m_IT_Type = IT_Dead;
		a_INode->m_CharType = DeadCoin;
		a_INode->SetAni_Rsc(DeadCoin);
	
	}
	else
	{
		a_INode = new CItem();
		a_INode->m_IT_Type = IT_Potion;
		a_INode->m_CharType = Potion;
		a_INode->SetAni_Rsc(Potion);

	}

	if (a_INode != NULL)
	{
		a_INode->m_CurPos.x = a_StartV.x;
		a_INode->m_CurPos.y = a_StartV.y;
		if (m_ImgList[(int)a_INode->m_IT_Type] != NULL)
		{
			a_INode->m_HalfWidth = m_ImgList[(int)a_INode->m_IT_Type]->GetWidth() / 2;
			a_INode->m_HalfHeight = m_ImgList[(int)a_INode->m_IT_Type]->GetHeight() / 2;
			a_INode->m_SocketImg = m_ImgList[(int)a_INode->m_IT_Type];
			
		}//	if (m_ImgList[(int)a_INode->m_IT_Type] != NULL)

		m_ItemList.push_back(a_INode);
	}//if (a_INode != NULL)

}

void CItem_Mgr::ReSrcClear()
{
	//--------------�ʵ���� ������ �����ϱ�
	if (!m_ItemList.empty())
	{
		for (m_Iiter = m_ItemList.begin(); m_Iiter != m_ItemList.end(); m_Iiter++)
		{
			if ((*m_Iiter) != NULL)
			{
				delete (*m_Iiter);
				(*m_Iiter) = NULL;
			}
		}//for (m_Iiter = m_ItemList.begin(); m_Iiter != m_ItemList.end(); m_Iiter++)

		m_ItemList.clear();
	}//	if (!m_ItemList.empty())
	//--------------�ʵ���� ������ �����ϱ�
}


CItem_Mgr	g_ItemMgr;