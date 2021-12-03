#pragma once


//-----------------------InGameStart
enum GameState
{
	GAME_READY = 0, //게임맨처음 
	GAME_START,  //가짜게임시작
	GAME_DEAD,  //가짜게임죽음
	GAME_END,  //게임끝낫을대
	GAME_REALCOUNT,  //게임 진짜시작되는 카운터
	GAME_REALSTART, //진짜시작
	GAME_MOUSESTART, //마우스클릭햇을대 변경부분 
	GAME_EXPLODE, //실드안에서 폭발
	GAME_PILSALSTART,
	GAME_INVEN,
	GAME_BOSS, //보스
	GAME_BOSTART,
	GAME_ENDING,//엔딩부분

};

enum SoundState
{
	GR = 1,
	Walk,
	DeadSound,
	Fire,
	GameOver,
	Game_Over_Pen,
	Keyboard,
	Mouse,
	GameStart,
	Fly,
	Gun,
	Machine_Gun,
	Pilsalgi,
	Run,
	Die01,
	Die02,
	InvestSound, //캐빈
	PlayerExSound, //플레이어폭발
	CoinSound,
	EndingSound,
};

enum ClickState
{
	GAME_LEFT,
	GAME_RIGHT,
};

extern	GameState g_GameState;	//게임의 상태
extern  ClickState g_ClickState;
extern  SoundState g_SoundState;
extern int g_TimeOut;
extern int g_DiffLevel; //난이도
