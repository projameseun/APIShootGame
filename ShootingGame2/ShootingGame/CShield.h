#pragma once
#include "CUnit.h"
class CHero;
class CShield : public CUnit
{
	
	HFONT shFont_50 = NULL;
	HFONT sh_OldFont;
	//---------------------½¯µå
	float	m_DeltaTime = 0.0f;
	//Image	*m_Shield;
	float	m_SdDuration = 6.0f;

public:
	float	m_SdOnTime = 0.0f;
	float	m_SdHalfSize;
	float	m_ExCount = 0.0f;
	//---------------------½¯µå

public:
	CShield();
	~CShield();

public:
	void Shield_Init();
	void Load_Shield(HWND hWnd);
	void ShieldUpdate(float a_DelTatime,CHero &a_Hero);
	void ShieldRender(HDC a_hdc,Graphics &graphics,CHero &a_Hero,float a_DeltaTime);
	void ShieldDestroy();
};

extern CShield g_Shield;