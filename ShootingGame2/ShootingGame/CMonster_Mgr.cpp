#include "stdafx.h"
#include "CMonster_Mgr.h"
#include "CHero.h" //플레이어의 정보 충돌때문에
#include "GlovalValue.h"
#include "CItem_Mgr.h"
#include "CShield.h"


CMonster::CMonster()
{
	m_isActive = false; //false로 초기화 

	m_MaxHP = 200.0f; 
	m_MonHp = 200.0f;

	m_Speed = 150.0f; //몬스터속도
	m_HalfColl = 20;  //몬스터의 반경거리 

}

CMonster::~CMonster()
{


}

void CMonster::Init_Unit()
{


}

void CMonster::Update_Unit(float a_DeltaTime, CHero & a_Hero)
{
	Vector2D a_CacVec = a_Hero.m_CurPos - m_CurPos;
	//실드 반경
	/*if (0.0f < g_Shield.m_SdOnTime)
	{
		if (a_CacVec.Magnitude() < g_Shield.m_SdHalfSize)
		{
			a_DeltaTime = a_DeltaTime * 0.05f;
		}
	}*/


	//MonSter AI
	if (a_Hero.m_HalfColl + m_HalfColl < a_CacVec.Magnitude()) //충돌 반경의 
	{
		
		
		
		//추적
		m_DirVec = a_CacVec; //몬스터의 방향 벡터
		m_DirVec.Normalize();
		m_CurPos = m_CurPos + (m_DirVec * (a_DeltaTime * m_Speed));



	}
	//MonSter AI

	//---------------------몬스터 공격처리 부분
	static float m_AttackTick = 0.0f;
	m_AttackTick = m_AttackTick - a_DeltaTime;
	if (a_CacVec.Magnitude() < (a_Hero.m_HalfColl + m_HalfColl + 10.0f))
	{
		if (m_AttackTick < 0.0f)		//공격 범위 안에 들어오면 즉시공격
		{
			//몬스터가 주인공 공격
			a_Hero.TakeDamage(10);

			m_AttackTick = 1.0f; //공속
		}
	}
	//---------------------몬스터 공격처리 부분
	if (0.0f < a_CacVec.x)
	{
		ChangeState(Right_Walk);
	}
	else
	{
		ChangeState(Left_Walk);
	}
	//----------애니메이션 플레임 계산
	CUnit::Update_Unit(a_DeltaTime);
}

void CMonster::Render_Unit(HDC a_hDC, HBRUSH & a_R_brsh)
{
	if (m_SocketImg == NULL)
		return;

	//----hp bar
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hDC, a_R_brsh);
	static float a_CacMXX = 0.0f;
	static float a_CacMYY = (int)(m_HalfHeight * 0.8f); //머리위 높이값 높이비율
	static float a_HpBSize = 50;
	static float a_CurHpSize = 0;
	a_CacMXX = a_HpBSize / 2.0f;
	a_CurHpSize = a_HpBSize * ((float)m_MonHp / (float)m_MaxHP);

	a_CacMYY = m_HalfHeight * 1.2f; //((int)m_HalfHeight * 1.1f)  //크기에 따라 에너지바 바뀐다

	Rectangle(a_hDC, m_CurPos.x - a_CacMXX, m_CurPos.y - a_CacMYY,
		m_CurPos.x - a_CacMXX + a_CurHpSize,
		m_CurPos.y - (a_CacMYY + 10.0f));
	SelectObject(a_hDC, h_Old_Brush);

	//-----hp bar


	Graphics graphics(a_hDC);
	graphics.DrawImage(m_SocketImg, m_CurPos.x - m_HalfWidth,
		m_CurPos.y - (int)(m_HalfHeight * 1.2f),
		(float)m_ImgSizeX, (float)m_ImgSizeY);

}

void CMonster::Destroy_Unit()
{


}

void CMonster::Reset_Unit()
{
	m_isActive = false; //false로 초기화 

	m_MaxHP = 200.0f;
	m_MonHp = 200.0f;

	m_Speed = 150.0f; //몬스터속도
	m_HalfColl = 20;  //몬스터의 반경거리 


}

void CMonster::Spawn(float a_XX, float a_YY)
{
	//난이도에 따라 이속변경
	m_Speed = 150.0f + ((g_DiffLevel - 1) * 30.0f);

	m_CurPos.x = a_XX;
	m_CurPos.y = a_YY;

	m_isActive = true;

	m_MonHp = m_MaxHP;

	SetAni_Rsc(m_CharType);
	

}

void CMonster::LoadUnitSize()
{
	

}

void CMonster::TakeDamage(float a_Value)
{

	m_MonHp = m_MonHp - a_Value;

	if (m_MonHp <= 0.0f)
	{
		g_Hero.m_KillCount++;
		g_ItemMgr.SpawnItem(m_CurPos);
		m_isActive = false; //사망
	}
}

////////////////////////////////////////////////////////

CMonster_Mgr::CMonster_Mgr()
{


}


CMonster_Mgr::~CMonster_Mgr()
{


}

void CMonster_Mgr::MonMgr_Init()
{
	//Image * a_ImgeNode = NULL;

	//a_ImgeNode = Image::FromFile(_T(".\\Reso\\Mon\\Mon1\\Right_Walk\\right01.png"));
	//m_ImgList.push_back(a_ImgeNode);

	//몬스터 메모리풀로 미리만들어 놓기 
	CMonster* a_Node = NULL;

;

	for (int i = 0; i < 20; i++)
	{
		//	a_Node->Init_Unit();
		a_Node = new CMonster();
		m_MonList.push_back(a_Node);
	}
	//몬스터 메모리풀로 미리만들어 놓기 

	m_R_brsh = CreateSolidBrush(RGB(255, 0, 0)); //에너지바 

}

void CMonster_Mgr::MonMgr_Update(float a_DeltaTime, HWND a_hWnd, CHero & a_Hero)
{
	//---------- 주기적인 Monster Spawn   
	SpawnMonster(a_DeltaTime, a_hWnd);
	//---------- 주기적인 Monster Spawn  

	//-----------Monster AI
	//몬스터 끼리 겹치지 않게 하기 관련 변수...
	static Vector2D a_CacVec;
	static float a_CacSDist;
	static float a_CacMargin = 0.0f;
	static float a_RadiusHap;
	static Vector2D a_CacMovePos;
	static Vector2D a_CacSNormal;
	static float a_CacShiftLen = 0.0f;

	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == false)
			continue;

		if (g_GameState == GAME_PILSALSTART)
			continue;

		m_MonList[ii]->Update_Unit(a_DeltaTime, a_Hero);

		//몬스터 끼리 겹치지 않게 하기...
		for (int xx = 0; xx < m_MonList.size(); xx++)
		{
			if (m_MonList[ii] == m_MonList[xx])
				continue;

			if (m_MonList[xx]->m_isActive == false)
				continue;

			a_CacVec = m_MonList[ii]->m_CurPos - m_MonList[xx]->m_CurPos;
			//피타고라스로 사용해서 거리를 알수있다
			a_CacSDist = a_CacVec.Magnitude();
			//서로충돌 판별 1번구와 2번구의 거리를 
			a_RadiusHap = m_MonList[ii]->m_HalfColl + 4 + m_MonList[xx]->m_HalfColl + 4; //(내반경 + 적반경) 변수 재활용

			a_CacMovePos = m_MonList[ii]->m_CurPos;

			if (a_CacSDist < a_RadiusHap) //겹친 상태
			{
				//여백
				a_CacMargin = a_RadiusHap - a_CacSDist;
				a_CacSNormal = a_CacVec; //밀려야할 방향
				a_CacSNormal.Normalize();

				a_CacShiftLen = a_CacMargin;
				if (a_RadiusHap < a_CacShiftLen) //안전장치 시간간격도 반지름보다 커지면 안된다. 
				{
					a_CacShiftLen = a_RadiusHap;
				}

				a_CacMovePos = a_CacMovePos + (a_CacSNormal * a_CacShiftLen);

			}//if (a_CacSDist < a_RadiusHap)

			m_MonList[ii]->m_CurPos = a_CacMovePos;
		}
		//몬스터 끼리 겹치지 않게 하기...

		//------- 주인공과의 충돌처리
		a_CacVec = m_MonList[ii]->m_CurPos - a_Hero.m_CurPos;
		a_CacSDist = a_CacVec.Magnitude();
		a_RadiusHap = m_MonList[ii]->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(내반경 + 적반경) 변수 재활용

		a_CacMovePos = m_MonList[ii]->m_CurPos;

		if (a_CacSDist < a_RadiusHap)
		{
			a_CacMargin = a_RadiusHap - a_CacSDist;
			a_CacSNormal = a_CacVec; //밀려야할 방향
			a_CacSNormal.Normalize();

			a_CacShiftLen = a_CacMargin;
			if (a_RadiusHap < a_CacShiftLen) //안전장치 시간간격도 반지름보다 커지면 안된다. 
			{
				a_CacShiftLen = a_RadiusHap;
			}

			a_CacMovePos = a_CacMovePos + (a_CacSNormal * a_CacShiftLen);

		}//if (a_CacSDist < a_RadiusHap)

		m_MonList[ii]->m_CurPos = a_CacMovePos;
		//------- 주인공과의 충돌처리

	}//for (int ii = 0; ii < m_MonList.size(); ii++)
	//-----------Monster AI

}

void CMonster_Mgr::MonMgr_Render(HDC a_hDC)
{
	//몬스터 이미지 그리기
	for (int i = 0; i < m_MonList.size(); i++)
	{
		if (m_MonList[i]->m_isActive == false)
			continue;

		m_MonList[i]->Render_Unit(a_hDC, m_R_brsh);
	}
	//몬스터 이미지 그리기

}

void CMonster_Mgr::MonMgr_Destroy()
{
	


	//몬스터 메모리풀 제거하기... 
	for (int aii = 0; aii < m_MonList.size(); aii++)
	{
		if (m_MonList[aii] != NULL)
		{
			m_MonList[aii]->Destroy_Unit();

			delete m_MonList[aii];
			m_MonList[aii] = NULL;
		}
	}
	m_MonList.clear();
	//몬스터 메모리풀 제거하기... 

	if (m_R_brsh != NULL)
	{
		DeleteObject(m_R_brsh);//brush object 제거
		m_R_brsh = NULL;
	}


}

void CMonster_Mgr::MonMgr_Reset()
{
	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		m_MonList[ii]->m_isActive = false;
	}

//	g_MonCount = 0;

	

}

void CMonster_Mgr::SpawnMonster(float a_DeltaTime, HWND a_hWnd)
{
	//--- 몬스터 Active 감시 및 마리수 카운트 
	/*static int g_MonCount = 0;*/
	
	g_MonCount = 0;
	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == true)
		{
		
			g_MonCount++;
		}
	}
	//--- 몬스터 Active 감시 및 마리수 카운트 

	//---------- 주기적인 Monster Spawn         //몬스터 랜덤 생성
	static float a_SpawnTime = 0.0f;
	a_SpawnTime = a_SpawnTime - a_DeltaTime;
	if (a_SpawnTime < 0.0f)
	{
		m_SpawnLim = 6 + (g_DiffLevel - 2);
		if (m_SpawnLim < 6)
			m_SpawnLim = 6;

		if (10 < m_SpawnLim)
			m_SpawnLim = 10;

		for (int ii = 0; ii < m_MonList.size(); ii++)
		{
			if (m_SpawnLim <= g_MonCount)
				break;

			if (m_MonList[ii]->m_isActive == false)
			{
				////----------------------Random 하게 스폰 좌표 생성하는 부분 
				////세로 - [0] x축 -150.0f ~ -50.0f  Y축 -150.0f ~ (float)m_cRT.bottom + 150.0f
				////       [1] x축 -50.0f ~ (int)m_cRT.right + 50.0f  Y축 -150.0f ~ -50.0f
				////세로 - [2] x축 (int)m_cRT.right + 50.0f ~ (int)m_cRT.right + 150.0f  Y축 -150.0f ~ (float)m_cRT.bottom + 150.0f
				////       [3] x축 -50.0f ~ (int)m_cRT.right + 50.0f  Y축 (float)m_cRT.bottom + 50.0f ~ (float)m_cRT.bottom + 150.0f
				////양옆 //위 아래 4곳중 한곳 랜덤 그중에서 랜덤으로 걸리게 하는 방법도 있다.

				static bool a_TicToc = true;
				//한번은 x축으로 
				//한번은 y축으로

				GetClientRect(a_hWnd, &m_cRT); // 클라이언트 화면의 크기를 받는다

				float a_XX = 0.0f;
				float a_YY = 0.0f;
				if (a_TicToc == true)
				{
					a_XX = (float)((rand() % 200) - 100);
					float a_PushVal = 50.0f;
					int a_YLenVal = (int)m_cRT.bottom + 100;

					if (a_XX < 0.0f)
					{
						a_XX = a_XX - a_PushVal;
					}
					else
					{
						a_XX = a_XX + (float)m_cRT.right + a_PushVal;
					}

					a_YY = (float)((rand() % a_YLenVal) + (100 / 2));

					a_TicToc = false;
				}
				else
				{
					a_YY = (float)((rand() % 200) - 100);
					float a_PushVal = 50.0f;
					int a_XLenVal = (int)m_cRT.right + 100;

					if (a_YY < 0.0f)
					{
						a_YY = a_YY - a_PushVal;
					}
					else
					{
						a_YY = a_YY + (float)m_cRT.bottom + a_PushVal;
					}

					a_XX = (float)((rand() % a_XLenVal) - (100 / 2));

					a_TicToc = true;
				}
				////----------------------Random 하게 스폰 좌표 생성하는 부분 
				m_MonList[ii]->m_CharType = GetSpMonType();
				m_MonList[ii]->Spawn(a_XX, a_YY);

				break;

			}//if (m_MonList[ii]->m_isActive == false)
		}//for (int ii = 0; ii < m_MonList.size(); ii++)
		//중점간의 거리가 반지름 + 반지름 보다 합보다 작거나같으면 충돌 
		a_SpawnTime = GetSpTimeLevel();
	}
	//---------- 주기적인 Monster Spawn  

}

void CMonster_Mgr::ReSrcClear()
{


}

CharType CMonster_Mgr::GetSpMonType()
{
	CharType a_SpType = Enemy02;

	if (g_DiffLevel <= 1)
	{
		a_SpType = Enemy01;
	}
	else if (g_DiffLevel == 2)
	{
		a_SpType = Enemy02;
	}
	else if (g_DiffLevel == 3)
	{
		a_SpType = Enemy03;
	}
	else if (g_DiffLevel == 4)
	{
		a_SpType = Enemy04;
	}
	else if (g_DiffLevel == 5)
	{
		a_SpType = Enemy05;
	}
	else if (g_DiffLevel == 6)
	{
		a_SpType = Enemy06;
	}
	else
	{
		a_SpType = Enemy02;
	}


	return a_SpType;
}

float CMonster_Mgr::GetSpTimeLevel()
{
	float a_SpTime = 2.0f;

	if (g_DiffLevel <= 1)
	{
		a_SpTime = (float)((rand() % 3) + 2); //다음스폰시간랜덤
	}
	else if (g_DiffLevel == 2)
	{
		a_SpTime = (float)((rand() % 3) + 1);
	}
	else if (g_DiffLevel == 3)
	{
		a_SpTime = (float)((rand() % 2) + 1);
	}
	else if (g_DiffLevel == 4)
	{
		a_SpTime = 1.0f;
	}
	else if (g_DiffLevel == 5)
	{
		a_SpTime = 0.5f;
	}
	else
	{
		a_SpTime = 0.3f;
	}

	return a_SpTime;
}


CMonster_Mgr g_Mon_Mgr;