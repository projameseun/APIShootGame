#include "stdafx.h"
#include "CBullet_Mgr.h"
#include "CMonster_Mgr.h"
#include "CSound.h"
#include "GlovalValue.h"
#include "CHero.h"

CBullet::CBullet()
{
	//m_BulletSocketImg = NULL;

	//for (int ii = 0; ii < Bullet_AniLength; ii++)
	//{
	//	BulletMotion* a_Node = new BulletMotion();
	//	m_BulletMoList.push_back(a_Node);
	//}

	//m_BulletCurAniState = Bullet_None;
	//m_BulletNowImgCount = 0;
	//m_BulletCurAniInx = 0;     //���� Ani Index
	//m_BulletAniTickCount = 0;     //���� �÷��ӱ��� �ð� Add
	//m_BulletEachAniDelay = 0.2f;  //�÷��� ���� �ð�m_BulletSocketImg = NULL;

	m_BLActive = false;

	m_LifeTime = 4.0f;
	m_MoveSpeed = 700.0f; //500�ȼ� / 1��

	m_HalfColl = 20.0f;	//�浹�ݰ�
	
}

CBullet::~CBullet()
{
}

void CBullet::BulletInit(Image * a_LoadImg)
{
}

bool CBullet::BulletUpdate(float a_DeltaTime,HWND a_hWnd)
{
		m_LifeTime -= a_DeltaTime;
	if (m_LifeTime < 0.0f)
	{
		m_BLActive = false;
		return false; //���� �ð��ڿ� �������ش�
	}

	static Vector2D  m_ZeroVec;
	m_ZeroVec.x = 0.0f;
	m_ZeroVec.y = 0.0f;
	float a_Angle = GetAngle(m_ZeroVec, m_DirVec);
	if (50.0f < a_Angle && a_Angle < 130.0f)
	{
		ChangeState(Right_Walk);
	}
	else if (230.0f < a_Angle && a_Angle < 310.0f)
	{
		ChangeState(Left_Walk);
	}
	
	m_CurPos = m_CurPos + (m_DirVec * (a_DeltaTime * m_MoveSpeed));

	//�÷��̾���ġ
	
	

	CUnit::AniFrameUpdate(a_DeltaTime);
	return true;
}

void CBullet::BulletRender(HDC a_hDC)
{
	//---------------------- �� �׸���
	
		m_BulletImgSizeX = (INT)(m_SocketImg->GetWidth());
		m_BulletImgSizeY = (INT)(m_SocketImg->GetHeight());



		Graphics graphics(a_hDC);
		graphics.DrawImage(m_SocketImg,
			Rect(m_CurPos.x - m_HalfWidth,
				m_CurPos.y - (int)(m_HalfHeight * 1.5f),
				(float)m_BulletImgSizeX, (float)m_BulletImgSizeY), 0, 0,
			m_SocketImg->GetWidth(), m_SocketImg->GetHeight(),
			UnitPixel);
	

}

void CBullet::BulletSpawn(float a_XX, float a_YY,int num)
{



}

void CBullet::BulletDestroy()
{
	

}



CBullet_Mgr::CBullet_Mgr()
{

}


CBullet_Mgr::~CBullet_Mgr()
{
}

void CBullet_Mgr::BLMgr_Init(HWND a_hWnd)
{
	//m_hWnd = a_hWnd;

	//�Ѿ� �޸�Ǯ�� �̸� ���þ� ����

	CBullet * a_BLNode = NULL;
	for (int i = 0; i < 200; i++)
	{
		a_BLNode = new CBullet();
		m_BullList.push_back(a_BLNode);
		
	}
	
}

void CBullet_Mgr::BLMgr_Update(HDC a_hdc, float a_DeltaTime, HWND a_hWnd, CMonster_Mgr *a_MonMgr ,CHero *a_Hero)
{
	if (g_GameState == GAME_BOSS)
	{
		//�����Ѿ�����
		for (int i = 0; i < m_BullList.size(); i++)
		{
			m_BullList[i]->m_BLActive = false;
		}
		//�����Ѿ�����
	}
	if (g_GameState != GAME_BOSTART)
	{
		//----------------��� �Ѿ� �̵����� ������Ʈ ó��
		static Vector2D a_CacBVec;
		static float a_Damage = 10.0f;
		for (int aii = 0; aii < m_BullList.size(); aii++)
		{
			if (m_BullList[aii]->m_BLActive == false)
				continue;

			m_BullList[aii]->BulletUpdate(a_DeltaTime, a_hWnd);


			//---------------�Ѿ��� ���Ϳ� �¾����� �������ش� 
			for (int i = 0; i < a_MonMgr->m_MonList.size(); i++)
			{
				if (a_MonMgr->m_MonList[i]->m_isActive == false)
					continue;

				a_CacBVec = a_MonMgr->m_MonList[i]->m_CurPos - m_BullList[aii]->m_CurPos;

				if (a_CacBVec.Magnitude() < (a_MonMgr->m_MonList[i]->m_HalfColl + m_BullList[aii]->m_HalfColl))
				{
					a_Damage = 30.0f;

					a_MonMgr->m_MonList[i]->TakeDamage(a_Damage);

					m_BullList[aii]->m_BLActive = false; //�Ѿ�����
					break;
				}
			}//for (int i = 0; i < a_MonMgr->m_MonList.size(); i++)
			//---------------�Ѿ��� ���Ϳ� �¾����� �������ش� 



		}//for (int i = 0; i < m_BullList.size(); i++)

		//----------------��� �Ѿ� �̵����� ������Ʈ ó��
	}

	if (g_GameState == GAME_BOSTART)
	{
		//----------------��� �Ѿ� �̵����� ������Ʈ ó��
		static Vector2D a_CacBVec2;
		static float a_Damage = 10.0f;
		for (int aii = 0; aii < m_BullList.size(); aii++)
		{
			if (m_BullList[aii]->m_BLActive == false)
				continue;

			m_BullList[aii]->BulletUpdate(a_DeltaTime, a_hWnd);


			//---------------�Ѿ��� ���Ϳ� �¾����� �������ش� 
			
				
			
			a_CacBVec2 = a_Hero->m_CurPos - m_BullList[aii]->m_CurPos;

				if (a_CacBVec2.Magnitude() < (a_Hero->m_HalfColl + m_BullList[aii]->m_HalfColl))
				{
					a_Damage = 50.0f;

					a_Hero->TakeDamage(a_Damage);

					m_BullList[aii]->m_BLActive = false; //�Ѿ�����
					break;
				}
		
			//---------------�Ѿ��� ���Ϳ� �¾����� �������ش� 



		}//for (int i = 0; i < m_BullList.size(); i++)

		//----------------��� �Ѿ� �̵����� ������Ʈ ó��
	}
	


	
}

void CBullet_Mgr::BLMgr_Render(HDC a_hDC, double a_DeltiTime)
{
	for (int i = 0; i < m_BullList.size(); i++)
	{
		if (m_BullList[i]->m_BLActive == false)
			continue;

		m_BullList[i]->BulletRender(a_hDC);

	
	}

}

void CBullet_Mgr::BLMgr_Destroy()
{
	//�Ѿ� �޸�Ǯ �����ϱ�
	for (int i = 0; i < m_BullList.size(); i++)
	{
		if (m_BullList[i] != NULL)
		{
			delete m_BullList[i];
			m_BullList[i] = NULL;
		}
	}

	m_BullList.clear();
	//�Ѿ� �޸�Ǯ �����ϱ�

	g_Bullet.BulletDestroy();

}

void CBullet_Mgr::SpawnBullet(Vector2D a_StartV, Vector2D a_TargetV ,float a_DeltaTime)
{
	CBullet *a_BNode = NULL;

	float a_XX = 0.0f;
	float a_YY = 0.0f;


	//�޸�Ǯ 
	for (int i = 0; i < m_BullList.size(); i++)
	{
		if (m_BullList[i]->m_BLActive == false)
		{
			
 			
			a_BNode = m_BullList[i];
			a_BNode->m_CharType = Bullet;
			a_BNode->SetAni_Rsc(Bullet);
			
		
			//a_BNode->m_SocketImg = m_ImgList[i];
			//a_BNode->BulletSpawn(a_XX, a_YY,i);
			break;
		}
	}

	

  	if (a_BNode == NULL)
	{
		
    		a_BNode = new CBullet();
			m_BullList.push_back(a_BNode);
		
		for (int i = 0; i < m_BullList.size(); i++)
		{
			if (m_BullList[i]->m_BLActive == false)
			{
				a_BNode = m_BullList[i];
				a_BNode->m_CharType = Bullet;
				a_BNode->SetAni_Rsc(Bullet);
				break;
			}

		}


	}


		
	
		a_BNode->m_CurPos.x = a_StartV.x; //���ΰ� ������ġ
		a_BNode->m_CurPos.y = a_StartV.y;

		a_BNode->m_DirVec = a_TargetV - a_StartV;
		a_BNode->m_DirVec.Normalize();
		a_BNode->m_CurPos = a_BNode->m_CurPos + a_BNode->m_DirVec * 20.0f; //���ΰ����� �ణ�� ��������
		a_BNode->m_BLActive = true;
		a_BNode->m_LifeTime = 4.0f;
	
	
}

void CBullet_Mgr::ReSrcClear()
{
	//�����Ѿ�����
	for (int i = 0; i < m_BullList.size(); i++)
	{
		m_BullList[i]->m_BLActive = false;
	}
	//�����Ѿ�����

}


CBullet_Mgr g_Bullet_Mgr;

CBullet g_Bullet;

//BulletAniState g_BulletState;