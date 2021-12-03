#include "stdafx.h"
#include "CCharacter.h"
#include "GlovalValue.h"
#include <time.h>
#include "CSound.h"
#include "CAnimation.h"
#include "CHero.h"
#include "CBullet_Mgr.h"
#include "CCharacter_Mgr.h"

//---------------음악을 사용할 헤더추가
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <Digitalv.h>
//---------------음악을 사용할 헤더추가

//--------------------- GDI+ 사용을 위한 헤더 추가


CCharacter::CCharacter()
{
	


}


CCharacter::~CCharacter()
{
}

void CCharacter::CChar_Init(Image * a_LoadImg)
{

}

void CCharacter::CChar_ReSetPos(int a_TrackNb, LONG a_XX, LONG a_YY)
{
	/*m_TrackNumber = a_TrackNb;*/

	m_CurPos.x = a_XX;
	m_CurPos.y = a_YY;

	m_CacAddPosX = (float)m_CurPos.x;
	m_CacAddPosY = (float)m_CurPos.y;

	ChangeState(Idle);

	m_R_brsh = CreateSolidBrush(RGB(255, 0, 0)); //에너지바 
}

void CCharacter::CChar_Update(HDC a_hdc,double a_DeltaTime, RECT * a_rt, bool a_isRaceStart)
{
	if (a_rt == NULL)
		return;
	

	
	if (a_isRaceStart == true)  //start 일때만 이동 
	{
		
		static float CountTime = 0;
		CountTime += a_DeltaTime;
	

		static float InvestCount = 0;
		InvestCount += a_DeltaTime;

		if (InvestCount >= 1.0f)
		{
			if (InvestCount > -1)
			{
				m_InVestCount++;
				if (m_InVestCount >= 88)
				{
					//음악재시작
					g_Sound.ResetWav(InvestSound);
					m_InVestCount = 0;
				}
			}

			InvestCount = 0;
		}//if (InvestCount >= 1.0)

		g_Sound.UpdateWav(InvestSound);


		if (GetAsyncKeyState(VK_LEFT) & 0x8000) //left키를 누르고잇는동안
		{
			g_Sound.UpdateWav(Walk);
			ChangeState(Left_Walk);

			m_CacAddPosX = m_CacAddPosX--;
			m_CurPos.x = (LONG)m_CacAddPosX;

			if (m_CacAddPosX <= 30)
			{

				g_GameState = GAME_REALCOUNT;
				g_Sound.ResetWav(InvestSound);

			}

			if (CountTime >= 1.0f)
			{
				if (CountTime > -1)
				{
					m_WalkCount++;

					if (m_WalkCount >=2)
					{

						m_WalkCount = 0;
						mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					}

				}
				CountTime = 0;
			}

			
			
			
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			//PlaySound(TEXT(Sound_Walk), NULL, SND_ASYNC | SND_LOOP);
			g_Sound.UpdateWav(Walk);
			if (m_CacAddPosX >= 1300.0f && m_CacAddPosY <= 200.0f)
			{
				g_Sound.UpdateWav(4); //fire
				//fire sound
				g_Sound.ResetWav(InvestSound);
				g_GameState = GAME_DEAD;
			
			}
			ChangeState(Right_Walk);
			m_CacAddPosX = m_CacAddPosX++;
			m_CurPos.x = (LONG)m_CacAddPosX;

			if (CountTime >= 1.0f)
			{
				if (CountTime > -1)
				{
					m_WalkCount++;

					if (m_WalkCount >= 2)
					{

						m_WalkCount = 0;
						mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					}

				}
				CountTime = 0;
			}

			
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			g_Sound.UpdateWav(Walk);
			//PlaySound(TEXT(Sound_Walk), NULL, SND_ASYNC | SND_LOOP);
			ChangeState(Back_Walk);
			m_CacAddPosY = m_CacAddPosY--;
			m_CurPos.y = (LONG)m_CacAddPosY;
		
			if (CountTime >= 1.0f)
			{
				if (CountTime > -1)
				{
					m_WalkCount++;

					if (m_WalkCount >= 2)
					{

						m_WalkCount = 0;
						mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					}

				}
				CountTime = 0;
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			g_Sound.UpdateWav(Walk);
			//PlaySound(TEXT(Sound_Walk), NULL, SND_ASYNC | SND_LOOP);
			ChangeState(Front_Walk);
			m_CacAddPosY = m_CacAddPosY++;
			m_CurPos.y = (LONG)m_CacAddPosY;
		
			if (CountTime >= 1.0f)
			{
				if (CountTime > -1)
				{
					m_WalkCount++;

					if (m_WalkCount >= 2)
					{

						m_WalkCount = 0;
						mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					}

				}
				CountTime = 0;
			}
		}

	//	g_Sound.ResetWav(2);
	//	PlaySound(NULL, 0, 0);  //소리 죽이기 
	}

	
	

		//------------------- 애니메이션 플레임 계산 부분 
		CUnit::Update_Unit(a_DeltaTime);
		//------------------- 애니메이션 플레임 계산 부분 

	
}

void CCharacter::CChar_RealUpdate(HDC a_hdc, double a_DeltaTime, RECT * a_rt, bool a_isRealStart)
{
	if (a_rt == NULL)
		return;



	//real start 이동 부분
	if (a_isRealStart == true)  //start 일때만 이동 
	{

		static float CountTime = 0;
		CountTime += a_DeltaTime;

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) //진짜 그림 나오게하기
		{
			g_GameState = GAME_MOUSESTART;
			g_Hero.Hero_ReSetPos();
		}


		if (GetAsyncKeyState(VK_LEFT) & 0x8000) //left키를 누르고잇는동안
		{
			g_Sound.UpdateWav(Walk);
			ChangeState(Left_Walk);

			m_CacAddPosX = m_CacAddPosX--;
			m_CurPos.x = (LONG)m_CacAddPosX;



			if (CountTime >= 1.0f)
			{
				if (CountTime > -1)
				{
					m_WalkCount++;

					if (m_WalkCount >= 2)
					{

						m_WalkCount = 0;
						mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					}

				}
				CountTime = 0;
			}




		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			//PlaySound(TEXT(Sound_Walk), NULL, SND_ASYNC | SND_LOOP);
			g_Sound.UpdateWav(Walk);

			ChangeState(Right_Walk);
			m_CacAddPosX = m_CacAddPosX++;
			m_CurPos.x = (LONG)m_CacAddPosX;

			if (CountTime >= 1.0f)
			{
				if (CountTime > -1)
				{
					m_WalkCount++;

					if (m_WalkCount >= 2)
					{

						m_WalkCount = 0;
						mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					}

				}
				CountTime = 0;
			}


		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			g_Sound.UpdateWav(Walk);
			//PlaySound(TEXT(Sound_Walk), NULL, SND_ASYNC | SND_LOOP);
			ChangeState(Back_Walk);
			m_CacAddPosY = m_CacAddPosY--;
			m_CurPos.y = (LONG)m_CacAddPosY;

			if (CountTime >= 1.0f)
			{
				if (CountTime > -1)
				{
					m_WalkCount++;

					if (m_WalkCount >= 2)
					{

						m_WalkCount = 0;
						mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					}

				}
				CountTime = 0;
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			g_Sound.UpdateWav(Walk);
			//PlaySound(TEXT(Sound_Walk), NULL, SND_ASYNC | SND_LOOP);
		ChangeState(Front_Walk);
			m_CacAddPosY = m_CacAddPosY++;
			m_CurPos.y = (LONG)m_CacAddPosY;

			if (CountTime >= 1.0f)
			{
				if (CountTime > -1)
				{
					m_WalkCount++;

					if (m_WalkCount >= 2)
					{

						m_WalkCount = 0;
						mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					}

				}
				CountTime = 0;
			}
		}

		//	g_Sound.ResetWav(2);
		//	PlaySound(NULL, 0, 0);  //소리 죽이기 
	}
	//real start  이동부분


	//------------------- 애니메이션 플레임 계산 부분 
	CUnit::Update_Unit(a_DeltaTime);
	//------------------- 애니메이션 플레임 계산 부분

}

void CCharacter::CChar_Render(HDC a_hdc, double a_DeltaTime)
{
	if (m_SocketImg == NULL)  //애니 소켓에 뭔가 꼽혀 있는지 확인해 보는 안전장치
		return;

	//---------------------- 말 그리기
	m_ImgSizeX = (INT)(m_SocketImg->GetWidth());
	m_ImgSizeY = (INT)(m_SocketImg->GetHeight());

////죽엇을때 표현 
//	if (Idle)
//	{
//		m_CurPos.x = 0;
//	}
//

	Graphics graphics(a_hdc);  // Bitblt에서 사용하던 그 g_hBackdc를 넣으면 됨.

	graphics.DrawImage(m_SocketImg,
		Rect(m_CurPos.x, m_CurPos.y, m_ImgSizeX, m_ImgSizeY),
		0, 0, m_SocketImg->GetWidth(), m_SocketImg->GetHeight(),
		UnitPixel);

	static TCHAR a_Str[128];


	/*	m_CurTime = timeGetTime();
		m_DeltaTime = ((m_CurTime - m_LastTime) * 0.001);
		m_LastTime = m_CurTime;*/
	
	//test 
	if (g_GameState == GAME_DEAD)
	{
		static float CountTime = 0;
		CountTime += a_DeltaTime;
		if (CountTime >= 1.0f)
		{
			if (CountTime > -1)
			{
				m_Count++;

				if (m_Count >= 3)
				{
					ChangeState(Dead);
					g_Sound.UpdateWav(3); //deadsound
				}
				if (m_Count >= 11)
				{
					
					g_GameState = GAME_END;

					m_Count = 0;
					

				}
			}
			CountTime = 0;
		}
	}

}

void CCharacter::CChar_Destroy()
{
	if (m_R_brsh != NULL)
	{
		DeleteObject(m_R_brsh);//brush object 제거
		m_R_brsh = NULL;
	}

}

void CCharacter::Boss_ReSetPos(int a_TrackNb, LONG a_XX, LONG a_YY)
{
	m_CurPos.x = a_XX;
	m_CurPos.y = a_YY;

	m_BossCurPos.x= (float)m_CurPos.x;
	m_BossCurPos.y = (float)m_CurPos.y;

	ChangeState(Idle);

	
}

void CCharacter::Boss_Update(HDC a_hdc, double a_DeltaTime,CHero &a_Hero)
{
	Vector2D a_CacVec = a_Hero.m_CurPos - m_BossCurPos;

	

	//MonSter AI
	if (a_Hero.m_HalfColl + m_HalfColl < a_CacVec.Magnitude()) //충돌 반경의 
	{
		//추적
		m_DirVec = a_CacVec; //몬스터의 방향 벡터
		m_DirVec.Normalize();
		m_BossCurPos = m_BossCurPos + (m_DirVec * (a_DeltaTime * m_Speed));
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
			a_Hero.TakeDamage(30);

			m_AttackTick = 1.0f; //공속
		}
	}
	//---------------------몬스터 공격처리 부분

	//---------------------애니 메이션 플레임 계산 부분
	if (0.0f < a_CacVec.x)
	{
		ChangeState(Right_Walk);
	}
	else
	{
		ChangeState(Left_Walk);
	}

	//----총알 발사 업데이트
	m_BLCycle = m_BLCycle + a_DeltaTime;
	if (m_AttackSpeed < m_BLCycle)
		m_BLCycle = 100.0f;

	static float BossAttackCount = 0;

	BossAttackCount += a_DeltaTime;

	if (BossAttackCount >= 1.0f)
	{
		m_BossAtCount++;
		if (m_BossAtCount >= 1.0f)
		{

			if (m_AttackSpeed < m_BLCycle)
			{
				POINT a_NewMMXZ;
				//GetCursorPos(&a_NewMMXZ);              //현재 마우스 좌표를 얻어오는 함수 
				//ScreenToClient(m_hWnd, &a_NewMMXZ);    // 클라이언트 화면 좌표로 변경해 주는 함수
				Vector2D a_TargetV;
				a_TargetV.x = a_Hero.m_CurPos.x;		//마우스의 좌표
				a_TargetV.y = a_Hero.m_CurPos.y;

				g_Bullet_Mgr.SpawnBullet(m_BossCurPos, a_TargetV, a_DeltaTime);

				m_BLCycle = 0.0f;

			}
			m_BossAtCount = 0;
		}

		BossAttackCount = 0;
	}
	////----총알 발사 업데이트


		///////////보스 필살기
	static float BossPilDelay = 0;
	static float BossPilCount = 0;

	BossPilCount += a_DeltaTime;
	BossPilDelay += a_DeltaTime;
	if (BossPilCount >= 1.0f)
	{
		m_BossPiCount++;
	
		if (m_BossPiCount >= 3.0f)
		{

		
			//사운드부분
			CBullet *a_BNode = NULL;
			float Radius = 100.0f;
			float Angle = 0.0f;
			static Vector2D a_CacStartV;
			static Vector2D a_TargetV;
			//12등분 16등분
			for (Angle = 0; Angle < (2.0f * 3.14592f); Angle += (3.14592f / 12))  //3.15 180도  24등분하면 더 많이나감
			{
				a_CacStartV = m_BossCurPos;

				a_TargetV.x = a_CacStartV.x + (Radius * cos(Angle));  //15 30 45 +15씩 360도 될때가지 
				a_TargetV.y = a_CacStartV.y + (Radius * sin(Angle));


				g_Bullet_Mgr.SpawnBullet(a_CacStartV, a_TargetV, a_DeltaTime);
			}

			if (BossPilDelay >= 5.0f)

			{
				m_BossPiCount = 0;
				BossPilDelay = 0;
			}
		}//	if (m_BossPiCount >= 2.0f)
		
		
		BossPilCount = 0;
	
	}//if (BossPilCount >= 1.0f)
	
	//--------------------------------궁극기

	////////////////보스필살기




	//----------애니메이션 플레임 계산
	CUnit::Update_Unit(a_DeltaTime);
	//----------애니메이션 플레임 계산

}

void CCharacter::Boss_Render(HDC a_hdc, double a_DeltaTime)
{
	if (m_SocketImg == NULL)
		return;

	//----hp bar
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hdc, m_R_brsh);
	static float a_CacMXX = 0.0f;
	static float a_CacMYY = (int)(m_HalfHeight * 0.8f); //머리위 높이값 높이비율
	static float a_HpBSize = 50;
	static float a_CurHpSize = 0;
	a_CacMXX = a_HpBSize / 2.0f;
	a_CurHpSize = a_HpBSize * ((float)m_BossCurHP / (float)m_BossMaxHP);

	a_CacMYY = m_HalfHeight * 0.9f; //((int)m_HalfHeight * 1.1f)

	Rectangle(a_hdc, m_BossCurPos.x - a_CacMXX, m_BossCurPos.y - a_CacMYY,
		m_BossCurPos.x - a_CacMXX + a_CurHpSize,
		m_BossCurPos.y - (a_CacMYY + 10.0f));
	SelectObject(a_hdc, h_Old_Brush);

	//-----hp bar


	Graphics graphics(a_hdc);
	graphics.DrawImage(m_SocketImg,
		m_BossCurPos.x - m_HalfWidth,
		m_BossCurPos.y - (int)(m_HalfHeight * 1.2f),
		(float)m_ImgSizeX, (float)m_ImgSizeY);



}

