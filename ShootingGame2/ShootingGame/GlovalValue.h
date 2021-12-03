#pragma once


//-----------------------InGameStart
enum GameState
{
	GAME_READY = 0, //���Ӹ�ó�� 
	GAME_START,  //��¥���ӽ���
	GAME_DEAD,  //��¥��������
	GAME_END,  //���ӳ�������
	GAME_REALCOUNT,  //���� ��¥���۵Ǵ� ī����
	GAME_REALSTART, //��¥����
	GAME_MOUSESTART, //���콺Ŭ�������� ����κ� 
	GAME_EXPLODE, //�ǵ�ȿ��� ����
	GAME_PILSALSTART,
	GAME_INVEN,
	GAME_BOSS, //����
	GAME_BOSTART,
	GAME_ENDING,//�����κ�

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
	InvestSound, //ĳ��
	PlayerExSound, //�÷��̾�����
	CoinSound,
	EndingSound,
};

enum ClickState
{
	GAME_LEFT,
	GAME_RIGHT,
};

extern	GameState g_GameState;	//������ ����
extern  ClickState g_ClickState;
extern  SoundState g_SoundState;
extern int g_TimeOut;
extern int g_DiffLevel; //���̵�
