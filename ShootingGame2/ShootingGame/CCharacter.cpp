#include "stdafx.h"
#include "CCharacter.h"
#include "GlovalValue.h"
#include <time.h>
#include "CSound.h"
#include "CAnimation.h"
#include "CHero.h"
#include "CBullet_Mgr.h"
#include "CCharacter_Mgr.h"

//---------------������ ����� ����߰�
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <Digitalv.h>
//---------------������ ����� ����߰�

//--------------------- GDI+ ����� ���� ��� �߰�


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

	m_R_brsh = CreateSolidBrush(RGB(255, 0, 0)); //�������� 
}

void CCharacter::CChar_Update(HDC a_hdc,double a_DeltaTime, RECT * a_rt, bool a_isRaceStart)
{
	if (a_rt == NULL)
		return;
	

	
	if (a_isRaceStart == true)  //start �϶��� �̵� 
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
					//���������
					g_Sound.ResetWav(InvestSound);
					m_InVestCount = 0;
				}
			}

			InvestCount = 0;
		}//if (InvestCount >= 1.0)

		g_Sound.UpdateWav(InvestSound);


		if (GetAsyncKeyState(VK_LEFT) & 0x8000) //leftŰ�� �������մµ���
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
	//	PlaySound(NULL, 0, 0);  //�Ҹ� ���̱� 
	}

	
	

		//------------------- �ִϸ��̼� �÷��� ��� �κ� 
		CUnit::Update_Unit(a_DeltaTime);
		//------------------- �ִϸ��̼� �÷��� ��� �κ� 

	
}

void CCharacter::CChar_RealUpdate(HDC a_hdc, double a_DeltaTime, RECT * a_rt, bool a_isRealStart)
{
	if (a_rt == NULL)
		return;



	//real start �̵� �κ�
	if (a_isRealStart == true)  //start �϶��� �̵� 
	{

		static float CountTime = 0;
		CountTime += a_DeltaTime;

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) //��¥ �׸� �������ϱ�
		{
			g_GameState = GAME_MOUSESTART;
			g_Hero.Hero_ReSetPos();
		}


		if (GetAsyncKeyState(VK_LEFT) & 0x8000) //leftŰ�� �������մµ���
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
		//	PlaySound(NULL, 0, 0);  //�Ҹ� ���̱� 
	}
	//real start  �̵��κ�


	//------------------- �ִϸ��̼� �÷��� ��� �κ� 
	CUnit::Update_Unit(a_DeltaTime);
	//------------------- �ִϸ��̼� �÷��� ��� �κ�

}

void CCharacter::CChar_Render(HDC a_hdc, double a_DeltaTime)
{
	if (m_SocketImg == NULL)  //�ִ� ���Ͽ� ���� ���� �ִ��� Ȯ���� ���� ������ġ
		return;

	//---------------------- �� �׸���
	m_ImgSizeX = (INT)(m_SocketImg->GetWidth());
	m_ImgSizeY = (INT)(m_SocketImg->GetHeight());

////�׾����� ǥ�� 
//	if (Idle)
//	{
//		m_CurPos.x = 0;
//	}
//

	Graphics graphics(a_hdc);  // Bitblt���� ����ϴ� �� g_hBackdc�� ������ ��.

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
		DeleteObject(m_R_brsh);//brush object ����
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
	if (a_Hero.m_HalfColl + m_HalfColl < a_CacVec.Magnitude()) //�浹 �ݰ��� 
	{
		//����
		m_DirVec = a_CacVec; //������ ���� ����
		m_DirVec.Normalize();
		m_BossCurPos = m_BossCurPos + (m_DirVec * (a_DeltaTime * m_Speed));
	}
	//MonSter AI

		//---------------------���� ����ó�� �κ�
	static float m_AttackTick = 0.0f;
	m_AttackTick = m_AttackTick - a_DeltaTime;
	if (a_CacVec.Magnitude() < (a_Hero.m_HalfColl + m_HalfColl + 10.0f))
	{
		if (m_AttackTick < 0.0f)		//���� ���� �ȿ� ������ ��ð���
		{
			//���Ͱ� ���ΰ� ����
			a_Hero.TakeDamage(30);

			m_AttackTick = 1.0f; //����
		}
	}
	//---------------------���� ����ó�� �κ�

	//---------------------�ִ� ���̼� �÷��� ��� �κ�
	if (0.0f < a_CacVec.x)
	{
		ChangeState(Right_Walk);
	}
	else
	{
		ChangeState(Left_Walk);
	}

	//----�Ѿ� �߻� ������Ʈ
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
				//GetCursorPos(&a_NewMMXZ);              //���� ���콺 ��ǥ�� ������ �Լ� 
				//ScreenToClient(m_hWnd, &a_NewMMXZ);    // Ŭ���̾�Ʈ ȭ�� ��ǥ�� ������ �ִ� �Լ�
				Vector2D a_TargetV;
				a_TargetV.x = a_Hero.m_CurPos.x;		//���콺�� ��ǥ
				a_TargetV.y = a_Hero.m_CurPos.y;

				g_Bullet_Mgr.SpawnBullet(m_BossCurPos, a_TargetV, a_DeltaTime);

				m_BLCycle = 0.0f;

			}
			m_BossAtCount = 0;
		}

		BossAttackCount = 0;
	}
	////----�Ѿ� �߻� ������Ʈ


		///////////���� �ʻ��
	static float BossPilDelay = 0;
	static float BossPilCount = 0;

	BossPilCount += a_DeltaTime;
	BossPilDelay += a_DeltaTime;
	if (BossPilCount >= 1.0f)
	{
		m_BossPiCount++;
	
		if (m_BossPiCount >= 3.0f)
		{

		
			//����κ�
			CBullet *a_BNode = NULL;
			float Radius = 100.0f;
			float Angle = 0.0f;
			static Vector2D a_CacStartV;
			static Vector2D a_TargetV;
			//12��� 16���
			for (Angle = 0; Angle < (2.0f * 3.14592f); Angle += (3.14592f / 12))  //3.15 180��  24����ϸ� �� ���̳���
			{
				a_CacStartV = m_BossCurPos;

				a_TargetV.x = a_CacStartV.x + (Radius * cos(Angle));  //15 30 45 +15�� 360�� �ɶ����� 
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
	
	//--------------------------------�ñر�

	////////////////�����ʻ��




	//----------�ִϸ��̼� �÷��� ���
	CUnit::Update_Unit(a_DeltaTime);
	//----------�ִϸ��̼� �÷��� ���

}

void CCharacter::Boss_Render(HDC a_hdc, double a_DeltaTime)
{
	if (m_SocketImg == NULL)
		return;

	//----hp bar
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hdc, m_R_brsh);
	static float a_CacMXX = 0.0f;
	static float a_CacMYY = (int)(m_HalfHeight * 0.8f); //�Ӹ��� ���̰� ���̺���
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

