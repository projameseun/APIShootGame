#include "stdafx.h"
#include "CMyMain.h"
#include <time.h>
#include "CBGround.h"
#include "CCharacter_Mgr.h"
#include "GlovalValue.h"
#include "CUIManager.h"
#include "CExplode_Mgr.h"
#include "CSound.h"
#include "CHero.h"
#include "CBullet_Mgr.h"
#include "CMonster_Mgr.h"
#include "CAnimation.h"
#include "CItem_Mgr.h"
#include "CShield.h"
//#include "CAnimation.h"

//---------------������ ����� ����߰�
#define Sound_Opening ".\\Music\\GR.wav"
#define Sound_Walk ".\\Music\\Walk.wav"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <Digitalv.h>
//---------------������ ����� ����߰�

//--------------------- GDI+ ����� ���� ��� �߰�
#include <ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//--------------------- GDI+ ����� ���� ��� �߰�

//--------------------- Window�� �ð����� ������ ���� ��� �߰�
#include <Mmsystem.h>                //timeGetTime(); �Լ� ����� ���ؼ�...
#pragma comment(lib, "winmm.lib")    //timeGetTime(); �Լ� ����� ���ؼ�...
#include <time.h>
#include <math.h>
//--------------------- Window�� �ð����� ������ ���� ��� �߰�



//mci�Լ���
//���
//MCI_PLAY_PARMS mciPlay;
//hWnd = mciOpen.wDeviceID;
//mciSendCommand(hWnd, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
////MCI_NOTIFY:�⺻ , MCI_DGV_PLAY_REPEAT :�ݺ�
//
////�ٽý���
//mciSendCommand(hWnd, MCI_RESUME, 0, NULL);
//
////�Ͻ�����
//msciSendCommand(hWnd, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
//
////����
//mciSendCommand(hWnd, MCI_CLOSE, 0, NULL);
//
//
////���Ǹ��� �Ҹ� ����
//
//Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
//mci�Լ���



CMyMain::CMyMain()
{
}


CMyMain::~CMyMain()
{
}

void CMyMain::MainInit(HWND hWnd)
{
	srand((unsigned)time(NULL));	//�����ʱ�ȭ

	m_LastTime = timeGetTime(); //����ð���������



	//PlaySound(TEXT(Sound_Opening), NULL, SND_ASYNC | SND_LOOP);


	GetWindowRect(hWnd, &m_Rect);  //��������ü������ 
	GetClientRect(hWnd, &m_Rect); //Ŭ���̾�Ʈ ȭ���� ũ�⸦ �޴�

	//---------- GDI+ �ʱ�ȭ (������Ʈ �������ڸ��� �ѹ��� �� �ָ�ȴ�.)
	GdiplusStartupInput gdiplusStartInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartInput, NULL);
	//gdiplusToken <--�������� gdiplusShutdown���� ����ϹǷ� ����
	//---------- GDI+ �ʱ�ȭ

	//---------- �ĸ� BackDC ����
	HDC hdc = GetDC(hWnd); //���� DC��������
	m_hBackDC = CreateCompatibleDC(hdc);  //���� DC�� �ֵ��� ���纻 DC�� �ϳ� �����.
	m_hBackBitmap = CreateCompatibleBitmap(hdc,           //BackDC�� �ٿ��� Bitmap(�̹���)�� �ϳ� ����� �ش�.
		GetSystemMetrics(SM_CXSCREEN),  //����ȭ���� ���� ������
		GetSystemMetrics(SM_CYSCREEN)); //����ȭ���� ���� ������
	SelectObject(m_hBackDC, m_hBackBitmap);

	ReleaseDC(hWnd, hdc);

	//-----------�Ҹ�����
	g_Sound.InitWAV(hWnd, L".\\Music\\GR.wav"); //1
	g_Sound.InitWAV(hWnd, L".\\Music\\Walk.wav"); //2
	g_Sound.InitWAV(hWnd, L".\\Music\\DeadSound.wav"); //3
	g_Sound.InitWAV(hWnd, L".\\Music\\Fire.wav"); //4
	g_Sound.InitWAV(hWnd, L".\\Music\\GameOver.wav"); //5
	g_Sound.InitWAV(hWnd, L".\\Music\\Game_Over_Pen.wav"); //6
	g_Sound.InitWAV(hWnd, L".\\Music\\Keyboard.wav"); //7
	g_Sound.InitWAV(hWnd, L".\\Music\\Mouse.wav"); //8 mouse
	g_Sound.InitWAV(hWnd, L".\\Music\\GameStart.wav"); //9 start
	g_Sound.InitWAV(hWnd, L".\\Music\\Fly.wav"); //10 �ö���
	g_Sound.InitWAV(hWnd, L".\\Music\\Gun.wav"); //11 ��
	g_Sound.InitWAV(hWnd, L".\\Music\\Machine_Gun.wav"); //12 �ӽ���
	g_Sound.InitWAV(hWnd, L".\\Music\\Pilsalgi.wav"); //13 �ʻ��
	g_Sound.InitWAV(hWnd, L".\\Music\\Run.wav"); //14 ��
	g_Sound.InitWAV(hWnd, L".\\Music\\Die01.wav"); //15 ����1
	g_Sound.InitWAV(hWnd, L".\\Music\\Die02.wav"); //16 ����2
	g_Sound.InitWAV(hWnd, L".\\Music\\Investgation.wav"); //17 ����2
	g_Sound.InitWAV(hWnd, L".\\Music\\PlayerEX.wav"); //18 ����
	g_Sound.InitWAV(hWnd, L".\\Music\\Coin.wav"); //19 ����
	g_Sound.InitWAV(hWnd, L".\\Music\\Ending.wav"); //20 ������
	
	//-----------�Ҹ�����
	//---------- �ĸ� BackDC ����


	for (int i = 0; i < CT_Length; i++)
	{
		CAnimation *a_Node = new CAnimation();
		a_Node->CAni_LoadAnimList((CharType)i);
		m_CharAniList.push_back(a_Node);
	}

		//----- UI �ʱ�ȭ �κ�
	g_UI_Mgr.UIMgrInit(m_hBackDC,m_Rect);
	//----- UI �ʱ�ȭ �κ�

	//----------BackGround �ʱ�ȭ
	g_BGround.BG_Init(hWnd);
	//----------BackGround �ʱ�ȭ

	////-----------���� �̹���
	g_ExplodeMgr.CEM_Init(hWnd);
	////-----------���� �̹���

		//-------�Ѿ� �ų��� �ʱ�ȭ
	g_Bullet_Mgr.BLMgr_Init(hWnd);
	//-------�Ѿ� �ų��� �ʱ�ȭ

	//----- ĳ���� �Ŵ��� �ʱ�ȭ
	g_Char_Mgr.CM_Init(hWnd);
	//----- ĳ���� �Ŵ��� �ʱ�ȭ

		//���ΰ� �ʱ�ȭ
	g_Hero.Hero_Init(hWnd);
	//���ΰ� �ʱ�ȭ

	//-------���� �Ŵ��� �ʱ�ȭ
	g_Mon_Mgr.MonMgr_Init();
	//-------���� �Ŵ��� �ʱ�ȭ




		//------------������ �Ŵ��� �ʱ�ȭ
	g_ItemMgr.ItemMgr_Init();
	//------------������ �Ŵ��� �ʱ�ȭ

}

void CMyMain::MainUpdate(HWND hWnd)
{
	
	//-------- DeltaTime ��� ���� ���
	timeBeginPeriod(1);     //timeGetTime() �Լ��� ���е��� ���̱� ���� �Լ�
	m_CurTime = timeGetTime();
	m_DeltaTime = ((m_CurTime - m_LastTime) * 0.001);
	m_LastTime = m_CurTime;
	timeEndPeriod(1);
	//-------- DeltaTime ��� ���� ���

	if (m_hBackDC == NULL)
		return;

	GetClientRect(hWnd, &m_Rect);
	//-----------BackGround ������Ʈ
	g_BGround.BG_Update(m_Rect);
	//-----------BackGround ������Ʈ

	static float CountTime = 0;
	//�����׳뷡 ī����
//	PlaySound(NULL, 0, 0);
	if (g_GameState != GAME_REALSTART && g_GameState != GAME_MOUSESTART &&
		g_GameState != GAME_PILSALSTART && g_GameState != GAME_EXPLODE && 
		g_GameState != GAME_INVEN)
	{
		if (g_GameState == GAME_READY)
		{


			CountTime += m_DeltaTime;
			g_Sound.UpdateWav(GR);
			g_Sound.ResetWav(GameOver);
			g_Sound.ResetWav(DeadSound);
			g_Sound.ResetWav(Fire);
			//_stprintf_s(a_TmStr, _T("%d"), m_Count);

			//TextOut(m_hBackDC, 200, 200, a_TmStr, (int)_tcslen(a_TmStr));

			if (CountTime >= 1.0f)
			{
				if (CountTime > -1)
				{
					m_Count++;

					if (m_Count >= 30)
					{
						//������ ��������ش� 
						mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						m_Count = 0;


					}
				}
				CountTime = 0;
			}
			//g_Sound.UpdateWav(1);

		}//if (g_GameState == GAME_READY)


		//------Ű���� ó�� �κ�
		static bool a_OnceSpace = true;
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (a_OnceSpace == true)
			{

				if (g_GameState == GAME_READY)
				{
					mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					//PlaySound(NULL, 0, 0);
					//g_Sound.UpdateWav(2);
					g_GameState = GAME_START;  //RACE_START;
				//	PlaySound(NULL, 0, 0);  //�Ҹ� ���̱� 
				}
				a_OnceSpace = false;
			}
		}//if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		else
		{
			a_OnceSpace = true;
		}

		static bool a_Once_R = true;
		if (GetAsyncKeyState('R') & 0x8000)
		{
			if (a_Once_R == true)
			{
				if (g_GameState == GAME_END)
				{
					g_Sound.ResetWav(InvestSound);
					g_Sound.ResetWav(DeadSound);
					g_Sound.ResetWav(Fire);
					g_Sound.ResetWav(GameOver);
					g_Sound.ResetWav(Game_Over_Pen);

					ReSetGame(); //���� �ʱ�ȭ
				}//if (g_GameState == RACE_END)

				a_Once_R = false;
			}
		}//else if (VK_Key == 'R')
		else
		{
			a_Once_R = true;
		}//	if (GetAsyncKeyState('R') & 0x8000)


		if (GAME_REALCOUNT == g_GameState) //��¥���ӽ��� 
		{
			g_Char_Mgr.CM_ReSetPos();

		}

		//�׾����� �뷡ī����
		static float DeadCountTime = 0;
		//�׾����� �뷡ī����
		if (GAME_END == g_GameState)
		{
			g_Sound.ResetWav(InvestSound);
			g_Sound.ResetWav(GameStart);
			DeadCountTime += m_DeltaTime;

			if (DeadCountTime >= 1.0f)
			{
				if (DeadCountTime > -1)
				{
					m_EndCount++;

					if (m_EndCount >= 80)
					{
						//������ ��������ش� 
						g_Sound.ResetWav(GameOver);
						g_Sound.ResetWav(Game_Over_Pen);

						m_EndCount = 0;


					}
				}
				DeadCountTime = 0;
			}
			g_Sound.UpdateWav(GameOver);
			g_Sound.UpdateWav(Game_Over_Pen); //pen
		}//if (GAME_END == g_GameState)

		//keyboard


		bool isDeadStart = (g_GameState == GAME_DEAD) ? true : false;
		if (g_GameState == GAME_DEAD)
		{
			g_ExplodeMgr.CEM_Update(m_DeltaTime, &m_Rect, isDeadStart);
		}



		//----- ĳ���� �Ŵ��� ������Ʈ
		bool isRaceStart = (g_GameState == GAME_START) ? true : false;
		g_Char_Mgr.CM_Update(m_hBackDC, m_DeltaTime, &m_Rect, isRaceStart);
		//----- ĳ���� �Ŵ��� ������Ʈ
	}//	if (g_GameState != GAME_REALSTART || g_GameState != GAME_MOUSESTART)

	//�����뷡 ī����
	static float GameStartCount = 0;
	if (g_GameState == GAME_REALSTART || g_GameState == GAME_MOUSESTART || g_GameState == GAME_EXPLODE || g_GameState == GAME_INVEN)
	{
		GameStartCount += m_DeltaTime;
		if (GameStartCount >= 1.0f)
		{
			if (GameStartCount > - 1)
			{
				m_StartCount++;
				if (m_StartCount >= 185)
				{
					//��������� �κ� 
					g_Sound.ResetWav(GameStart); //statgame
					m_StartCount = 0;
				}
			}
			GameStartCount = 0;
		}

		g_Sound.UpdateWav(GameStart);

		//----- ���� ������Ʈ
		bool isRealStart = (g_GameState == GAME_REALSTART) ? true : false;

		g_Char_Mgr.CM_RealUpdate(m_hBackDC, m_DeltaTime, &m_Rect, isRealStart);
	
		//-----ĳ���� ���� ������Ʈ
	}//if (g_GameState == GAME_REALSTART || g_GameState == GAME_MOUSESTART)
		//�����뷡 ī����

	if (g_GameState == GAME_MOUSESTART || g_GameState == GAME_PILSALSTART || g_GameState == GAME_EXPLODE)
	{


		////----------���ΰ� ������Ʈ
		g_Hero.Hero_Update(m_hBackDC, m_DeltaTime, m_Rect);
		////----------���ΰ� ������Ʈ


		////-----------���� ������Ʈ
		g_Mon_Mgr.MonMgr_Update(m_DeltaTime, hWnd, g_Hero);
		////-----------���� ������Ʈ

		//	//-----------�Ѿ� ������Ʈ
		g_Bullet_Mgr.BLMgr_Update(m_hBackDC, m_DeltaTime, hWnd,&g_Mon_Mgr,&g_Hero);
		////-----------�Ѿ� ������Ʈ
	}////


	if (g_GameState == GAME_BOSTART)
	{
		////----------���ΰ� ������Ʈ
		g_Hero.Hero_Update(m_hBackDC, m_DeltaTime, m_Rect);
		////----------���ΰ� ������Ʈ


		//------------����������Ʈ
		g_Char_Mgr.BossM_Update(m_hBackDC, m_DeltaTime,g_Hero);

		//	//-----------�Ѿ� ������Ʈ
		g_Bullet_Mgr.BLMgr_Update(m_hBackDC, m_DeltaTime, hWnd, &g_Mon_Mgr,&g_Hero);
		////-----------�Ѿ� ������Ʈ
	}

	//-------------�����۸Ŵ���������Ʈ
	g_ItemMgr.ItemMgr_Update(m_DeltaTime);
	//-------------�����۸Ŵ���������Ʈ
	
	//----- UI ������Ʈ �κ�
	g_UI_Mgr.UIMgrUpdate(m_DeltaTime,hWnd, NextLevel,ReSetGame);
	//----- UI ������Ʈ �κ�


	

}


void CMyMain::MainRender(HWND hWnd)
{
	if (m_hBackDC == NULL)
		return;

	
	//-------------BackGround Render
	g_BGround.BG_Render(m_hBackDC, m_Rect, hWnd);
	//-------------BackGround Render



	SetBkMode(m_hBackDC, TRANSPARENT);      // �ؽ�Ʈ ����� ����.
	SetTextAlign(m_hBackDC, TA_CENTER);     // �۾� �����Լ� �߾�����

	if (g_GameState == GAME_DEAD)
	{
		g_ExplodeMgr.CEM_Render(m_hBackDC);
	}
	
	//��¥���ӽ�������� �κ� ���̴ºκ�
	if (g_GameState != GAME_MOUSESTART && g_GameState != GAME_PILSALSTART && g_GameState != GAME_EXPLODE
		&& g_GameState != GAME_INVEN && GAME_BOSS != g_GameState 
		&& g_GameState != GAME_BOSTART)
	//-------- ĳ���� �Ŵ��� ����
	g_Char_Mgr.CM_Render(m_hBackDC,m_DeltaTime);
	//-------- ĳ���� �Ŵ��� ����
	//��¥���ӽ�������� �κ� ���̴ºκ�

	//���� �������������'�� �κ� ���κκ�
	if(g_GameState == GAME_MOUSESTART || g_GameState == GAME_PILSALSTART || g_GameState == GAME_EXPLODE)
	{

		//������ ����
		g_ItemMgr.ItemMgr_Render(m_hBackDC);
		//������ ����
		//---------���� �̹��� �׸���
		g_Mon_Mgr.MonMgr_Render(m_hBackDC);
		//---------���� �̹��� �׸���
		//---------�Ѿ� �׷��ֱ�
		g_Bullet_Mgr.BLMgr_Render(m_hBackDC, m_DeltaTime);
		//---------�Ѿ� �׷��ֱ�
		g_Hero.Hero_Render(m_hBackDC, m_DeltaTime);
	}
	//���� �������������'�� �κ� ���κκ�

	if (g_GameState == GAME_BOSTART)
	{
		//������ ����
		g_ItemMgr.ItemMgr_Render(m_hBackDC);
		//������ ����
		//---------�Ѿ� �׷��ֱ�
		g_Bullet_Mgr.BLMgr_Render(m_hBackDC, m_DeltaTime);
		//---------�Ѿ� �׷��ֱ�

		g_Char_Mgr.BossM_Render(m_hBackDC, m_DeltaTime);
		g_Hero.Hero_Render(m_hBackDC, m_DeltaTime);
		//������������

	}
	//----- UI �׸��� �κ�
	g_UI_Mgr.UIMgrRender(m_hBackDC, m_Rect,m_DeltaTime);
	//----- UI �׸��� �κ�

	SetTextAlign(m_hBackDC, TA_LEFT);       // �������...
	SetBkMode(m_hBackDC, OPAQUE);			// �ؽ�Ʈ ��� �������...

	//-----------������۸�
	static HDC hdc;
	hdc = GetDC(hWnd);
	//ȭ����ȯ
	BitBlt(hdc, 0, 0, m_Rect.right, m_Rect.bottom, m_hBackDC, 0, 0, SRCCOPY);
	//ȭ����ȯ
	ReleaseDC(hWnd, hdc);
	//-----------������۸�

		

}

void CMyMain::MainDestroy()
{
	//�ִϸ��̼� ������ �����κ� 
	for (int i = 0; i < m_CharAniList.size(); i++)
	{
		if (m_CharAniList[i] != NULL)
		{
			delete m_CharAniList[i];
			m_CharAniList[i] = NULL;
		}
	}

	m_CharAniList.clear();
	//�ִϸ��̼� ������ �����κ� 

	//--------------������ �����
	g_ItemMgr.ItemMgr_Destroy();
	//--------------������ �����
	//--------���� �����
	g_Mon_Mgr.MonMgr_Destroy();
	//--------���� �����

	//-------�Ѿ�����
	g_Bullet_Mgr.BLMgr_Destroy();
	//-------�Ѿ�����
	//--------�Ҹ�����
	g_Sound.DestroyWav();
	//--------�Ҹ�����

	//-------���ΰ� ����
	g_Hero.Hero_Destroy();
	//-------���ΰ� ����

		//-------- ĳ���� �Ŵ��� ����
	g_Char_Mgr.CM_Destroy();
	//-------- ĳ���� �Ŵ��� ����

	//--------��׶������� 
	g_BGround.BG_Destroy();
	//--------��׶������� 

	g_ExplodeMgr.CEM_Destroy();

	//----- UI ���� �κ�
	g_UI_Mgr.UIMgrDestroy();
	//----- UI ���� �κ�


	//--------�ĸ� DC���� �ϱ�
	if (m_hBackBitmap != NULL)
	{
		DeleteObject(m_hBackBitmap);
		m_hBackBitmap;
	}

	if (m_hBackDC != NULL)
	{
		DeleteDC(m_hBackDC);
		m_hBackDC;
	}
	//--------�ĸ� DC���� �ϱ�

	//------GDI���� //�׻� ���� �������ְ� �������� �� 
	if (m_gdiplusToken != NULL)
	{
		GdiplusShutdown(m_gdiplusToken);
		m_gdiplusToken = NULL;
	}
	//------GDI����

}



void CMyMain::ReSetGame()
{

	//���� �ʱ�ȭ 
	g_TimeOut = 10;

	g_DiffLevel = 1;

	g_Bullet_Mgr.ReSrcClear(); //����� �ؽ��Ŀ� ���� �Ѿ����� 

	g_ItemMgr.ReSrcClear();

	g_Mon_Mgr.MonMgr_Reset();

	g_Char_Mgr.CM_ReSetPos();

	g_ExplodeMgr.CEM_ReSetPos();

	//���ΰ� �ʱ�ȭ 
	static RECT a_RT;
	GetClientRect(g_CMyMain.m_hWnd, &a_RT);
	g_Hero.m_CurPos.x = ((float)a_RT.right / 2.0f);
	g_Hero.m_CurPos.y = ((float)a_RT.bottom / 2.0f);

	g_Shield.m_SdOnTime = 0.0f;

	g_Hero.ChangeState(Idle);
	g_Hero.m_MaxHP = 150;
	g_Hero.m_CurHP = g_Hero.m_MaxHP;
	g_Hero.m_KillCount = 0;
	g_Hero.m_SkillCount = 5;
	g_Hero.m_ShieldCount = 5;
	g_Hero.m_Speed = 300.0f;

	g_Hero.m_STDelay = 0.5f;

	g_GameState = GAME_READY;
}

void CMyMain::BossRest()
{
	//������ġ
	g_Char_Mgr.BossM_ReSetPos(m_DeltaTime, m_hWnd);
	g_TimeOut = 10;
	g_GameState = GAME_BOSTART;
}

void CMyMain::NextLevel()
{
	g_TimeOut = 10;

	g_Bullet_Mgr.ReSrcClear(); //����� �ؽ��Ŀ� ���� �Ѿ����� 

	g_ItemMgr.ReSrcClear();

	g_Mon_Mgr.MonMgr_Reset();

	//----------���ΰ� �ʱ�ȭ 

	//static RECT a_RT;
	//GetClientRect(g_CMyMain.m_hWnd, &a_RT);
	//g_Hero.m_CurPos.x = (float)(a_RT.right / 2.0f);
	//g_Hero.m_CurPos.y = (float)(a_RT.bottom / 2.0f);

	g_Shield.m_SdOnTime = 0.0f;

	g_Hero.ChangeState(Idle);

	g_GameState = GAME_MOUSESTART;

}

CMyMain g_CMyMain; 
