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

//---------------음악을 사용할 헤더추가
#define Sound_Opening ".\\Music\\GR.wav"
#define Sound_Walk ".\\Music\\Walk.wav"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <Digitalv.h>
//---------------음악을 사용할 헤더추가

//--------------------- GDI+ 사용을 위한 헤더 추가
#include <ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//--------------------- GDI+ 사용을 위한 헤더 추가

//--------------------- Window의 시간값을 얻어오기 위한 헤더 추가
#include <Mmsystem.h>                //timeGetTime(); 함수 사용을 위해서...
#pragma comment(lib, "winmm.lib")    //timeGetTime(); 함수 사용을 위해서...
#include <time.h>
#include <math.h>
//--------------------- Window의 시간값을 얻어오기 위한 헤더 추가



//mci함수들
//재생
//MCI_PLAY_PARMS mciPlay;
//hWnd = mciOpen.wDeviceID;
//mciSendCommand(hWnd, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
////MCI_NOTIFY:기본 , MCI_DGV_PLAY_REPEAT :반복
//
////다시시작
//mciSendCommand(hWnd, MCI_RESUME, 0, NULL);
//
////일시정지
//msciSendCommand(hWnd, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
//
////정지
//mciSendCommand(hWnd, MCI_CLOSE, 0, NULL);
//
//
////조건마다 소리 진행
//
//Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
//mci함수들



CMyMain::CMyMain()
{
}


CMyMain::~CMyMain()
{
}

void CMyMain::MainInit(HWND hWnd)
{
	srand((unsigned)time(NULL));	//랜덤초기화

	m_LastTime = timeGetTime(); //현재시간가져오기



	//PlaySound(TEXT(Sound_Opening), NULL, SND_ASYNC | SND_LOOP);


	GetWindowRect(hWnd, &m_Rect);  //윈도우전체사이즈 
	GetClientRect(hWnd, &m_Rect); //클라이언트 화면의 크기를 받는

	//---------- GDI+ 초기화 (프로젝트 시작하자마자 한번만 해 주면된다.)
	GdiplusStartupInput gdiplusStartInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartInput, NULL);
	//gdiplusToken <--마지막에 gdiplusShutdown에서 사용하므로 저장
	//---------- GDI+ 초기화

	//---------- 후면 BackDC 생성
	HDC hdc = GetDC(hWnd); //메인 DC가져오기
	m_hBackDC = CreateCompatibleDC(hdc);  //메인 DC의 쌍둥이 복사본 DC를 하나 만든다.
	m_hBackBitmap = CreateCompatibleBitmap(hdc,           //BackDC에 붙여줄 Bitmap(이미지)를 하나 만들어 준다.
		GetSystemMetrics(SM_CXSCREEN),  //바탕화면의 가로 사이즈
		GetSystemMetrics(SM_CYSCREEN)); //바탕화면의 세로 사이즈
	SelectObject(m_hBackDC, m_hBackBitmap);

	ReleaseDC(hWnd, hdc);

	//-----------소리생성
	g_Sound.InitWAV(hWnd, L".\\Music\\GR.wav"); //1
	g_Sound.InitWAV(hWnd, L".\\Music\\Walk.wav"); //2
	g_Sound.InitWAV(hWnd, L".\\Music\\DeadSound.wav"); //3
	g_Sound.InitWAV(hWnd, L".\\Music\\Fire.wav"); //4
	g_Sound.InitWAV(hWnd, L".\\Music\\GameOver.wav"); //5
	g_Sound.InitWAV(hWnd, L".\\Music\\Game_Over_Pen.wav"); //6
	g_Sound.InitWAV(hWnd, L".\\Music\\Keyboard.wav"); //7
	g_Sound.InitWAV(hWnd, L".\\Music\\Mouse.wav"); //8 mouse
	g_Sound.InitWAV(hWnd, L".\\Music\\GameStart.wav"); //9 start
	g_Sound.InitWAV(hWnd, L".\\Music\\Fly.wav"); //10 플라이
	g_Sound.InitWAV(hWnd, L".\\Music\\Gun.wav"); //11 총
	g_Sound.InitWAV(hWnd, L".\\Music\\Machine_Gun.wav"); //12 머신총
	g_Sound.InitWAV(hWnd, L".\\Music\\Pilsalgi.wav"); //13 필살기
	g_Sound.InitWAV(hWnd, L".\\Music\\Run.wav"); //14 런
	g_Sound.InitWAV(hWnd, L".\\Music\\Die01.wav"); //15 다이1
	g_Sound.InitWAV(hWnd, L".\\Music\\Die02.wav"); //16 다이2
	g_Sound.InitWAV(hWnd, L".\\Music\\Investgation.wav"); //17 다이2
	g_Sound.InitWAV(hWnd, L".\\Music\\PlayerEX.wav"); //18 폭팔
	g_Sound.InitWAV(hWnd, L".\\Music\\Coin.wav"); //19 동전
	g_Sound.InitWAV(hWnd, L".\\Music\\Ending.wav"); //20 엔ㄷㅇ
	
	//-----------소리생성
	//---------- 후면 BackDC 생성


	for (int i = 0; i < CT_Length; i++)
	{
		CAnimation *a_Node = new CAnimation();
		a_Node->CAni_LoadAnimList((CharType)i);
		m_CharAniList.push_back(a_Node);
	}

		//----- UI 초기화 부분
	g_UI_Mgr.UIMgrInit(m_hBackDC,m_Rect);
	//----- UI 초기화 부분

	//----------BackGround 초기화
	g_BGround.BG_Init(hWnd);
	//----------BackGround 초기화

	////-----------폭발 이미지
	g_ExplodeMgr.CEM_Init(hWnd);
	////-----------폭발 이미지

		//-------총알 매너지 초기화
	g_Bullet_Mgr.BLMgr_Init(hWnd);
	//-------총알 매너지 초기화

	//----- 캐릭터 매니저 초기화
	g_Char_Mgr.CM_Init(hWnd);
	//----- 캐릭터 매니저 초기화

		//주인공 초기화
	g_Hero.Hero_Init(hWnd);
	//주인공 초기화

	//-------몬스터 매니저 초기화
	g_Mon_Mgr.MonMgr_Init();
	//-------몬스터 매니저 초기화




		//------------아이템 매니저 초기화
	g_ItemMgr.ItemMgr_Init();
	//------------아이템 매니저 초기화

}

void CMyMain::MainUpdate(HWND hWnd)
{
	
	//-------- DeltaTime 얻어 오는 방법
	timeBeginPeriod(1);     //timeGetTime() 함수의 정밀도를 높이기 위한 함수
	m_CurTime = timeGetTime();
	m_DeltaTime = ((m_CurTime - m_LastTime) * 0.001);
	m_LastTime = m_CurTime;
	timeEndPeriod(1);
	//-------- DeltaTime 얻어 오는 방법

	if (m_hBackDC == NULL)
		return;

	GetClientRect(hWnd, &m_Rect);
	//-----------BackGround 업데이트
	g_BGround.BG_Update(m_Rect);
	//-----------BackGround 업데이트

	static float CountTime = 0;
	//오프닝노래 카운터
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
						//음악을 재시작해준다 
						mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
						m_Count = 0;


					}
				}
				CountTime = 0;
			}
			//g_Sound.UpdateWav(1);

		}//if (g_GameState == GAME_READY)


		//------키보드 처리 부분
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
				//	PlaySound(NULL, 0, 0);  //소리 죽이기 
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

					ReSetGame(); //게임 초기화
				}//if (g_GameState == RACE_END)

				a_Once_R = false;
			}
		}//else if (VK_Key == 'R')
		else
		{
			a_Once_R = true;
		}//	if (GetAsyncKeyState('R') & 0x8000)


		if (GAME_REALCOUNT == g_GameState) //진짜게임시작 
		{
			g_Char_Mgr.CM_ReSetPos();

		}

		//죽었을때 노래카운터
		static float DeadCountTime = 0;
		//죽었을때 노래카운터
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
						//음악을 재시작해준다 
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



		//----- 캐릭터 매니저 업데이트
		bool isRaceStart = (g_GameState == GAME_START) ? true : false;
		g_Char_Mgr.CM_Update(m_hBackDC, m_DeltaTime, &m_Rect, isRaceStart);
		//----- 캐릭터 매니저 업데이트
	}//	if (g_GameState != GAME_REALSTART || g_GameState != GAME_MOUSESTART)

	//실제노래 카운터
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
					//음악재시작 부분 
					g_Sound.ResetWav(GameStart); //statgame
					m_StartCount = 0;
				}
			}
			GameStartCount = 0;
		}

		g_Sound.UpdateWav(GameStart);

		//----- 실제 업데이트
		bool isRealStart = (g_GameState == GAME_REALSTART) ? true : false;

		g_Char_Mgr.CM_RealUpdate(m_hBackDC, m_DeltaTime, &m_Rect, isRealStart);
	
		//-----캐릭터 실제 업데이트
	}//if (g_GameState == GAME_REALSTART || g_GameState == GAME_MOUSESTART)
		//실제노래 카운터

	if (g_GameState == GAME_MOUSESTART || g_GameState == GAME_PILSALSTART || g_GameState == GAME_EXPLODE)
	{


		////----------주인공 업데이트
		g_Hero.Hero_Update(m_hBackDC, m_DeltaTime, m_Rect);
		////----------주인공 업데이트


		////-----------몬스터 업데이트
		g_Mon_Mgr.MonMgr_Update(m_DeltaTime, hWnd, g_Hero);
		////-----------몬스터 업데이트

		//	//-----------총알 업데이트
		g_Bullet_Mgr.BLMgr_Update(m_hBackDC, m_DeltaTime, hWnd,&g_Mon_Mgr,&g_Hero);
		////-----------총알 업데이트
	}////


	if (g_GameState == GAME_BOSTART)
	{
		////----------주인공 업데이트
		g_Hero.Hero_Update(m_hBackDC, m_DeltaTime, m_Rect);
		////----------주인공 업데이트


		//------------보스업데이트
		g_Char_Mgr.BossM_Update(m_hBackDC, m_DeltaTime,g_Hero);

		//	//-----------총알 업데이트
		g_Bullet_Mgr.BLMgr_Update(m_hBackDC, m_DeltaTime, hWnd, &g_Mon_Mgr,&g_Hero);
		////-----------총알 업데이트
	}

	//-------------아이템매니저업데이트
	g_ItemMgr.ItemMgr_Update(m_DeltaTime);
	//-------------아이템매니저업데이트
	
	//----- UI 업데이트 부분
	g_UI_Mgr.UIMgrUpdate(m_DeltaTime,hWnd, NextLevel,ReSetGame);
	//----- UI 업데이트 부분


	

}


void CMyMain::MainRender(HWND hWnd)
{
	if (m_hBackDC == NULL)
		return;

	
	//-------------BackGround Render
	g_BGround.BG_Render(m_hBackDC, m_Rect, hWnd);
	//-------------BackGround Render



	SetBkMode(m_hBackDC, TRANSPARENT);      // 텍스트 배경을 뺀다.
	SetTextAlign(m_hBackDC, TA_CENTER);     // 글씨 정렬함수 중앙정렬

	if (g_GameState == GAME_DEAD)
	{
		g_ExplodeMgr.CEM_Render(m_hBackDC);
	}
	
	//가짜게임실행됫을때 부분 속이는부분
	if (g_GameState != GAME_MOUSESTART && g_GameState != GAME_PILSALSTART && g_GameState != GAME_EXPLODE
		&& g_GameState != GAME_INVEN && GAME_BOSS != g_GameState 
		&& g_GameState != GAME_BOSTART)
	//-------- 캐릭터 매니저 랜더
	g_Char_Mgr.CM_Render(m_hBackDC,m_DeltaTime);
	//-------- 캐릭터 매니저 랜더
	//가짜게임실행됫을때 부분 속이는부분

	//진자 게임진행됫을ㄸ'ㅐ 부분 메인부분
	if(g_GameState == GAME_MOUSESTART || g_GameState == GAME_PILSALSTART || g_GameState == GAME_EXPLODE)
	{

		//아이템 랜더
		g_ItemMgr.ItemMgr_Render(m_hBackDC);
		//아이템 랜더
		//---------몬스터 이미지 그리기
		g_Mon_Mgr.MonMgr_Render(m_hBackDC);
		//---------몬스터 이미지 그리기
		//---------총알 그려주기
		g_Bullet_Mgr.BLMgr_Render(m_hBackDC, m_DeltaTime);
		//---------총알 그려주기
		g_Hero.Hero_Render(m_hBackDC, m_DeltaTime);
	}
	//진자 게임진행됫을ㄸ'ㅐ 부분 메인부분

	if (g_GameState == GAME_BOSTART)
	{
		//아이템 랜더
		g_ItemMgr.ItemMgr_Render(m_hBackDC);
		//아이템 랜더
		//---------총알 그려주기
		g_Bullet_Mgr.BLMgr_Render(m_hBackDC, m_DeltaTime);
		//---------총알 그려주기

		g_Char_Mgr.BossM_Render(m_hBackDC, m_DeltaTime);
		g_Hero.Hero_Render(m_hBackDC, m_DeltaTime);
		//보ㅅ나왓을대

	}
	//----- UI 그리기 부분
	g_UI_Mgr.UIMgrRender(m_hBackDC, m_Rect,m_DeltaTime);
	//----- UI 그리기 부분

	SetTextAlign(m_hBackDC, TA_LEFT);       // 원래대로...
	SetBkMode(m_hBackDC, OPAQUE);			// 텍스트 배경 원래대로...

	//-----------더블버퍼링
	static HDC hdc;
	hdc = GetDC(hWnd);
	//화면전환
	BitBlt(hdc, 0, 0, m_Rect.right, m_Rect.bottom, m_hBackDC, 0, 0, SRCCOPY);
	//화면전환
	ReleaseDC(hWnd, hdc);
	//-----------더블버퍼링

		

}

void CMyMain::MainDestroy()
{
	//애니메이션 데이터 삭제부분 
	for (int i = 0; i < m_CharAniList.size(); i++)
	{
		if (m_CharAniList[i] != NULL)
		{
			delete m_CharAniList[i];
			m_CharAniList[i] = NULL;
		}
	}

	m_CharAniList.clear();
	//애니메이션 데이터 삭제부분 

	//--------------아이템 지우기
	g_ItemMgr.ItemMgr_Destroy();
	//--------------아이템 지우기
	//--------몬스터 지우기
	g_Mon_Mgr.MonMgr_Destroy();
	//--------몬스터 지우기

	//-------총알제거
	g_Bullet_Mgr.BLMgr_Destroy();
	//-------총알제거
	//--------소리제거
	g_Sound.DestroyWav();
	//--------소리제거

	//-------주인공 제거
	g_Hero.Hero_Destroy();
	//-------주인공 제거

		//-------- 캐릭터 매니저 제거
	g_Char_Mgr.CM_Destroy();
	//-------- 캐릭터 매니저 제거

	//--------백그라운드제거 
	g_BGround.BG_Destroy();
	//--------백그라운드제거 

	g_ExplodeMgr.CEM_Destroy();

	//----- UI 제거 부분
	g_UI_Mgr.UIMgrDestroy();
	//----- UI 제거 부분


	//--------후면 DC제거 하기
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
	//--------후면 DC제거 하기

	//------GDI해제 //항상 모든걸 해제해주고 마지막에 꼭 
	if (m_gdiplusToken != NULL)
	{
		GdiplusShutdown(m_gdiplusToken);
		m_gdiplusToken = NULL;
	}
	//------GDI해제

}



void CMyMain::ReSetGame()
{

	//게임 초기화 
	g_TimeOut = 10;

	g_DiffLevel = 1;

	g_Bullet_Mgr.ReSrcClear(); //지운공 텍스쳐와 남은 총알제거 

	g_ItemMgr.ReSrcClear();

	g_Mon_Mgr.MonMgr_Reset();

	g_Char_Mgr.CM_ReSetPos();

	g_ExplodeMgr.CEM_ReSetPos();

	//주인공 초기화 
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
	//보스위치
	g_Char_Mgr.BossM_ReSetPos(m_DeltaTime, m_hWnd);
	g_TimeOut = 10;
	g_GameState = GAME_BOSTART;
}

void CMyMain::NextLevel()
{
	g_TimeOut = 10;

	g_Bullet_Mgr.ReSrcClear(); //지운공 텍스쳐와 남은 총알제거 

	g_ItemMgr.ReSrcClear();

	g_Mon_Mgr.MonMgr_Reset();

	//----------주인공 초기화 

	//static RECT a_RT;
	//GetClientRect(g_CMyMain.m_hWnd, &a_RT);
	//g_Hero.m_CurPos.x = (float)(a_RT.right / 2.0f);
	//g_Hero.m_CurPos.y = (float)(a_RT.bottom / 2.0f);

	g_Shield.m_SdOnTime = 0.0f;

	g_Hero.ChangeState(Idle);

	g_GameState = GAME_MOUSESTART;

}

CMyMain g_CMyMain; 
