#include "stdafx.h"
#include "CHero.h"
#include "GlovalValue.h"
#include <time.h>
#include "CSound.h"
#include "CBullet_Mgr.h"
#include "CMonster_Mgr.h"
#include "CCharacter_Mgr.h"
#include "CShield.h"
#include "CHeroEx.h"

//---------------������ ����� ����߰�


#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <Digitalv.h>
//---------------������ ����� ����߰�

//--------------------- GDI+ ����� ���� ��� �߰�

CHero::CHero()
{
	

	m_CurHP = 300;
	m_MaxHP = 300;

}


CHero::~CHero()
{
}

void CHero::Hero_Init(HWND a_hWnd)
{
	m_hWnd = a_hWnd;

	SetAni_Rsc(RealPlayer);

	if (m_CurAniState == None)
	{
		m_SocketImg = Image::FromFile(_T(".\\Reso\\RealPlayer\\idle01.png"));
	}


	m_R_brsh = CreateSolidBrush(RGB(255, 255, 0));

	//���ΰ� ��ǥ �ʱ�ȭ �κ�
	RECT a_Crt;
	GetClientRect(a_hWnd, &a_Crt);	//Main DC�� ���� ���� ����� ������
	m_CurPos.x = (float)(a_Crt.right / 2);
	m_CurPos.y = (float)(a_Crt.bottom / 2);
	//���ΰ� ��ǥ �ʱ�ȭ �κ�

	Hero_ReSetPos();
	g_Shield.Shield_Init();
	g_Shield.Load_Shield(a_hWnd);

	//�÷��̾� ���� �׸� 
	g_HeroEx.Load_PExplode(a_hWnd);
}

void CHero::Hero_ReSetPos()
{
	//m_TrackNumber = a_TrackNb;

	RECT a_Rect;
	GetClientRect(m_hWnd, &a_Rect); // Ŭ���̾�Ʈ ȭ���� ũ�⸦ �޴´�
	//----- ĳ���� �ʱ�ȭ �κ�
	/*int a_PosX = (int)((float)a_Rect.right * 0.5f);
	int a_PosY = (int)((float)a_Rect.bottom * 0.5f);*/
	//int a_YTab = a_Rect.bottom / 7;
	m_CurPos.x = g_Char_Mgr.m_CharList.m_CurPos.x;
	m_CurPos.y = g_Char_Mgr.m_CharList.m_CurPos.y;


}

void CHero::Hero_Update(HDC a_hdc, float a_DeltaTime, RECT & a_RT)
{
	//�ǵ� �κ� 
	//m_DeltaTime = a_DeltaTime;

	if (GetFocus() == NULL)//���� �����찡 Ȱ��ȭ �Ǿ� ���� ������ ���ΰ� ĭ
		return;

	//------------����Ű ó�����
	static Vector2D a_KDirVec;

	a_KDirVec.x = 0.0f;
	a_KDirVec.y = 0.0f;

	if (g_GameState != GAME_PILSALSTART)
	{
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) ||
			(GetAsyncKeyState('A') & 0x8000))
		{
			a_KDirVec.x -= 1.0f;
			

		}

		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
			(GetAsyncKeyState('D') & 0x8000))
		{
			a_KDirVec.x += 1.0f;
		}

		if ((GetAsyncKeyState(VK_UP) & 0x8000) ||
			(GetAsyncKeyState('W') & 0x8000))
		{
			a_KDirVec.y -= 1.0f;
		}

		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) ||
			(GetAsyncKeyState('S') & 0x8000))
		{
			a_KDirVec.y += 1.0f;
		}

		if (a_KDirVec.x == 0 && a_KDirVec.y == 0)
		{
			//���߿� ������ �ִϻ�����ȯ
			ChangeState(Idle);
		}
		else
		{

			static Vector2D  m_ZeroVec;
			m_ZeroVec.x = 0.0f;
			m_ZeroVec.y = 0.0f;
			float a_Angle = GetAngle(m_ZeroVec, a_KDirVec);
			if (50.0f < a_Angle && a_Angle < 130.0f)
			{
				ChangeState(Idle);
			}
			else if (130.0f <= a_Angle && a_Angle <= 230.0f)
			{
				ChangeState(Idle);
			}
			else if (230.0f < a_Angle && a_Angle < 310.0f)
			{
				ChangeState(Idle);
			}
			else
			{
				ChangeState(Idle);
			}
			a_KDirVec.Normalize(); //���̰� 1�κ���
			m_CurPos = m_CurPos + (a_KDirVec * (a_DeltaTime * m_Speed));


		}
	}//if (g_GameState != GAME_PILSALSTART)

	static bool is_Move = true;
 	if (g_GameState == GAME_PILSALSTART)
	{
		
		static float a_CacLXXXX = 0.0f;
		static float a_CacLYYYY = 0.0f;

		
		if (is_Move == true)
		{
			
				a_KDirVec.x += 1.0f;
				if ((float)(a_RT.right) - 200 <= m_CurPos.x)
				{
					
					is_Move = false;
					//a_CacLXXXX = 25;
				}
			
		
		}
		if (is_Move == false)
		{
			
				a_KDirVec.x -= 1.0f;
				if ((float)(a_RT.left) + 200>= m_CurPos.x)
				{
					
					is_Move = true;
					//a_CacLXXXX = 10;
				}
		}

		a_KDirVec.Normalize(); //���̰� 1�κ���
		m_CurPos = m_CurPos + (a_KDirVec * (a_DeltaTime * m_Speed));
		//HeroLimitMove(a_RT);
			
		
	}



	////�Ѿ� �߻� ������Ʈ
	m_BLCycle = m_BLCycle + a_DeltaTime;
	if (m_AttackSpeed < m_BLCycle)
		m_BLCycle = 100.0f;


	
	static int BossCount = 0;
	if (g_GameState == GAME_END)
		BossCount = 0;

	if (g_GameState != GAME_BOSTART)
	{
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))
		{

			// 8000
			BossCount++;
			if (BossCount >=500)
			{
				BossCount = 0;
				g_GameState = GAME_BOSS;
				//��������
			}
			if (m_AttackSpeed < m_BLCycle)
			{
				POINT a_NewMMXZ;
				GetCursorPos(&a_NewMMXZ);  //f���縶�콺��ǥ

				ScreenToClient(m_hWnd, &a_NewMMXZ); //Ŭ�󸮾�Ʈ ȭ�� ��ǥ��
				//Ŭ���̾���ǥ �ݴ�� ���� 
				Vector2D a_TaragetV;
				a_TaragetV.x = (float)a_NewMMXZ.x; //���콺��ǥ
				a_TaragetV.y = (float)a_NewMMXZ.y;


				g_Sound.UpdateWav(Gun);
				g_Sound.UpdateWav(Fly); //fly

				g_Bullet_Mgr.SpawnBullet(m_CurPos, a_TaragetV, a_DeltaTime);



				m_BLCycle = 0.0f;
			}

			static float GunCount = 0;

			if ((GetAsyncKeyState(MK_LBUTTON) & 0x8000))
			{
				GunCount += a_DeltaTime;
				if (GunCount >= 1.0f)
				{
					if (GunCount > -1)
					{
						m_GunCount++;
						if (m_GunCount >= 4)
						{
							g_Sound.ResetWav(Machine_Gun); //�ӽŰ�
							m_GunCount = 0;
						}
					}
					GunCount = 0;
				}

				g_Sound.UpdateWav(Machine_Gun);
			}

			//g_Sound.ResetWav(10); //
		}
	}//if (g_GameState != GAME_BOSTART)


	////�Ѿ� �߻� ������Ʈ

		//------------------- �ִϸ��̼� �÷��� ��� �κ� 

	//------------------- �ִϸ��̼� �÷��� ��� �κ� 


	//--------------------------------�ñر�
	static bool isSPDown = true;
	static float pilsaCount = 0; //�ʻ�� ī����



	if (g_GameState == GAME_PILSALSTART)
	{
		pilsaCount += a_DeltaTime;

		if (pilsaCount >= 1.0f)
		{
			if (pilsaCount > -1)
			{
				m_PilsaCount++;
				if (m_PilsaCount >= 2)
				{
					//run 
					g_Sound.UpdateWav(Run); //run
				}
				if (m_PilsaCount >= 13)
				{
					g_Sound.UpdateWav(Die01);
				}
				if (m_PilsaCount >= 23)
				{
					g_Sound.UpdateWav(Die02);

					
				}
				if (m_PilsaCount >= 28)
				{
					//���� ���Ϳ� �Ѿ�����
					m_CurHP = 0;
					g_GameState = GAME_END;

					Hero_ReSet();
					g_Mon_Mgr.MonMgr_Reset();
					
					m_PilsaCount = 0;
					
				}
			}

			pilsaCount = 0;
		}//if (pilsaCount >= 1.0f)

	}//	if (g_GameState == GAME_PILSALSTART)



	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && g_GameState != GAME_PILSALSTART)
	{
		g_Sound.UpdateWav(Pilsalgi); //���� �Ҹ� 
		m_Speed = 600.0f;
		g_GameState = GAME_PILSALSTART;
		g_Sound.ResetWav(GameStart);
		
		if (isSPDown == true)
		{
			CBullet *a_BNode = NULL;
			float Radius = 100.0f;
			float Angle = 0.0f;
			static Vector2D a_CacStartV;
			static Vector2D a_TargetV;
			//12��� 16���
			for (Angle = 0; Angle < (2.0f * 3.14592f); Angle += (3.14592f / 12))  //3.15 180��  24����ϸ� �� ���̳���
			{
				a_CacStartV = m_CurPos;

				a_TargetV.x = a_CacStartV.x + (Radius * cos(Angle));  //15 30 45 +15�� 360�� �ɶ����� 
				a_TargetV.y = a_CacStartV.y + (Radius * sin(Angle));


				g_Bullet_Mgr.SpawnBullet(a_CacStartV, a_TargetV, a_DeltaTime);
			}
			isSPDown = false;
		}//if (isSPDown == true)
	}//	if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
	else
	{
		isSPDown = true;
	}
	//--------------------------------�ñر�

	g_Shield.ShieldUpdate(a_DeltaTime,g_Hero);
	g_HeroEx.PExplodeUpdate(a_DeltaTime, g_Hero);

	CUnit::Update_Unit(a_DeltaTime);
}



void CHero::Hero_Render(HDC a_hdc, double a_DeltaTime)
{

	//----hp bar
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hdc, m_R_brsh);
	static float a_CacMXX = 0.0f;
	static float a_CacMYY = (int)(m_HalfHeight * 0.5f); //�Ӹ��� ���̰� ���̺���
	static float a_HpBSize = 50;
	static float a_CurHpSize = 0;
	a_CacMXX = a_HpBSize / 5.0f;
	a_CurHpSize = a_HpBSize * ((float)m_CurHP / (float)m_MaxHP);

	a_CacMYY = m_HalfHeight * 0.9f; //((int)m_HalfHeight * 1.1f)

	Rectangle(a_hdc, m_CurPos.x - a_CacMXX, m_CurPos.y - a_CacMYY,
		m_CurPos.x - a_CacMXX + a_CurHpSize,
		m_CurPos.y - (a_CacMYY + 10.0f));
	SelectObject(a_hdc, h_Old_Brush);

	//-----hp bar



	
	m_ImgSizeX = (INT)(m_SocketImg->GetWidth());
	m_ImgSizeY = (INT)(m_SocketImg->GetHeight());



	Graphics graphics(a_hdc);
	graphics.DrawImage(m_SocketImg,
		Rect(m_CurPos.x - m_HalfWidth,
		m_CurPos.y - (int)(m_HalfHeight * 1.2f),
		(float)m_ImgSizeX, (float)m_ImgSizeY),0,0,
		m_SocketImg->GetWidth(),m_SocketImg->GetHeight(),
		UnitPixel);

	g_Shield.ShieldRender(a_hdc,graphics,g_Hero,a_DeltaTime);



}

void CHero::Hero_Destroy()
{
	/*if (m_HeroSocketImg != NULL)
	{
		delete m_HeroSocketImg;
		m_HeroSocketImg = NULL;
	}
*/
	if (m_Hero != NULL)
	{
		delete m_Hero;
		//DeleteObject(m_Hero);
		m_Hero = NULL;
	}

	if (m_R_brsh != NULL)
	{
		DeleteObject(m_R_brsh);
		m_R_brsh = NULL;
	}

	g_Shield.ShieldDestroy();
	

}

void CHero::HeroLimitMove(RECT & a_RT)
{
	static float a_CacLXXX = 0.0f;
	static float a_CacLYYY = 0.0f;

	a_CacLXXX = 15;
	if (m_CurPos.x < a_CacLXXX)
	{
		m_CurPos.x = a_CacLXXX;
	}

	if ((float)(a_RT.right - a_CacLXXX) < m_CurPos.x)
	{
		m_CurPos.x = (float)(a_RT.right - a_CacLXXX);
	}

	a_CacLYYY = 30;

	if (m_CurPos.y < a_CacLYYY)
	{
		m_CurPos.y = a_CacLYYY;
	}

	if ((float)(a_RT.bottom - a_CacLYYY) < m_CurPos.y)
	{
		m_CurPos.y = (float)(a_RT.bottom - a_CacLYYY);
	}

}

void CHero::TakeDamage(float a_Damage)
{
	m_CurHP = m_CurHP - (int)a_Damage;
	if (m_CurHP <= 0)
	{
		//���� ���Ϳ� �Ѿ�����
		m_CurHP = 0;
		g_GameState = GAME_END;

		Hero_ReSet();
		g_Mon_Mgr.MonMgr_Reset();
	}

}

void CHero::Hero_ReSet()
{

	Hero_ReSetPos();
	m_CurHP = 150;
	m_MaxHP = 150;

	g_Sound.ResetWav(Pilsalgi);
	g_Sound.ResetWav(Run);
	g_Sound.ResetWav(Die01);
	g_Sound.ResetWav(Die02);

}

void CHero::BuyHP()
{

	if (100 <= g_Hero.m_MyMoney)
	{
		if (g_Hero.m_CurHP <= g_Hero.m_MaxHP)
		{
			//static TCHAR Str[128];

		
			g_Hero.m_CurHP = 1.0f;
			g_Hero.m_MaxHP = 1.0f;
			if (g_Hero.m_MaxHP < g_Hero.m_CurHP)
			{
				g_Hero.m_CurHP = g_Hero.m_MaxHP;
			}
			g_Hero.m_MyMoney = g_Hero.m_MyMoney - 100;
		}//if (g_Hero.m_CurHP < g_Hero.m_MaxHP)
	}//if (100 <= g_Hero.m_MyMoney)

}

void CHero::BuySkill()
{
	if (150 <= g_Hero.m_MyMoney)
	{
		g_Hero.m_SkillCount = g_Hero.m_SkillCount + 1;
		g_Hero.m_MyMoney -= 150;
	}

}

void CHero::BuyShield()
{
	if (200 <= g_Hero.m_MyMoney)
	{
		g_Hero.m_ShieldCount = g_Hero.m_ShieldCount + 1;
		g_Hero.m_MyMoney -= 200;
	}


}





CHero g_Hero;