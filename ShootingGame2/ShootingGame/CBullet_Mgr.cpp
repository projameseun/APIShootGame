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
	//m_BulletCurAniInx = 0;     //진행 Ani Index
	//m_BulletAniTickCount = 0;     //다음 플레임까지 시간 Add
	//m_BulletEachAniDelay = 0.2f;  //플레임 간격 시간m_BulletSocketImg = NULL;

	m_BLActive = false;

	m_LifeTime = 4.0f;
	m_MoveSpeed = 700.0f; //500픽셀 / 1초

	m_HalfColl = 20.0f;	//충돌반경
	
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
		return false; //일정 시간뒤에 제거해준다
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

	//플레이어위치
	
	

	CUnit::AniFrameUpdate(a_DeltaTime);
	return true;
}

void CBullet::BulletRender(HDC a_hDC)
{
	//---------------------- 말 그리기
	
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

	//총알 메모리풀로 미리 맏늘어 놓기

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
		//남은총알제거
		for (int i = 0; i < m_BullList.size(); i++)
		{
			m_BullList[i]->m_BLActive = false;
		}
		//남은총알제거
	}
	if (g_GameState != GAME_BOSTART)
	{
		//----------------모드 총알 이동관련 업데이트 처리
		static Vector2D a_CacBVec;
		static float a_Damage = 10.0f;
		for (int aii = 0; aii < m_BullList.size(); aii++)
		{
			if (m_BullList[aii]->m_BLActive == false)
				continue;

			m_BullList[aii]->BulletUpdate(a_DeltaTime, a_hWnd);


			//---------------총알이 몬스터에 맞았으면 제거해준다 
			for (int i = 0; i < a_MonMgr->m_MonList.size(); i++)
			{
				if (a_MonMgr->m_MonList[i]->m_isActive == false)
					continue;

				a_CacBVec = a_MonMgr->m_MonList[i]->m_CurPos - m_BullList[aii]->m_CurPos;

				if (a_CacBVec.Magnitude() < (a_MonMgr->m_MonList[i]->m_HalfColl + m_BullList[aii]->m_HalfColl))
				{
					a_Damage = 30.0f;

					a_MonMgr->m_MonList[i]->TakeDamage(a_Damage);

					m_BullList[aii]->m_BLActive = false; //총알제거
					break;
				}
			}//for (int i = 0; i < a_MonMgr->m_MonList.size(); i++)
			//---------------총알이 몬스터에 맞았으면 제거해준다 



		}//for (int i = 0; i < m_BullList.size(); i++)

		//----------------모드 총알 이동관련 업데이트 처리
	}

	if (g_GameState == GAME_BOSTART)
	{
		//----------------모드 총알 이동관련 업데이트 처리
		static Vector2D a_CacBVec2;
		static float a_Damage = 10.0f;
		for (int aii = 0; aii < m_BullList.size(); aii++)
		{
			if (m_BullList[aii]->m_BLActive == false)
				continue;

			m_BullList[aii]->BulletUpdate(a_DeltaTime, a_hWnd);


			//---------------총알이 몬스터에 맞았으면 제거해준다 
			
				
			
			a_CacBVec2 = a_Hero->m_CurPos - m_BullList[aii]->m_CurPos;

				if (a_CacBVec2.Magnitude() < (a_Hero->m_HalfColl + m_BullList[aii]->m_HalfColl))
				{
					a_Damage = 50.0f;

					a_Hero->TakeDamage(a_Damage);

					m_BullList[aii]->m_BLActive = false; //총알제거
					break;
				}
		
			//---------------총알이 몬스터에 맞았으면 제거해준다 



		}//for (int i = 0; i < m_BullList.size(); i++)

		//----------------모드 총알 이동관련 업데이트 처리
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
	//총알 메모리풀 제거하기
	for (int i = 0; i < m_BullList.size(); i++)
	{
		if (m_BullList[i] != NULL)
		{
			delete m_BullList[i];
			m_BullList[i] = NULL;
		}
	}

	m_BullList.clear();
	//총알 메모리풀 제거하기

	g_Bullet.BulletDestroy();

}

void CBullet_Mgr::SpawnBullet(Vector2D a_StartV, Vector2D a_TargetV ,float a_DeltaTime)
{
	CBullet *a_BNode = NULL;

	float a_XX = 0.0f;
	float a_YY = 0.0f;


	//메모리풀 
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


		
	
		a_BNode->m_CurPos.x = a_StartV.x; //주인공 현재위치
		a_BNode->m_CurPos.y = a_StartV.y;

		a_BNode->m_DirVec = a_TargetV - a_StartV;
		a_BNode->m_DirVec.Normalize();
		a_BNode->m_CurPos = a_BNode->m_CurPos + a_BNode->m_DirVec * 20.0f; //주인공에셔 약간의 여백을줌
		a_BNode->m_BLActive = true;
		a_BNode->m_LifeTime = 4.0f;
	
	
}

void CBullet_Mgr::ReSrcClear()
{
	//남은총알제거
	for (int i = 0; i < m_BullList.size(); i++)
	{
		m_BullList[i]->m_BLActive = false;
	}
	//남은총알제거

}


CBullet_Mgr g_Bullet_Mgr;

CBullet g_Bullet;

//BulletAniState g_BulletState;