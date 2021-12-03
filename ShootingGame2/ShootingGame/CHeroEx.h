#pragma once
#include "CUnit.h"

class CHero;
class CHeroEx :public CUnit
{
public:
	CHeroEx();
	~CHeroEx();

public:
	void Load_PExplode(HWND hWnd);
	void PExplodeUpdate(float a_DelTatime, CHero &a_Hero);
	void PExplodeRender(HDC a_hdc, Graphics &graphics, CHero &a_Hero, float a_DeltaTime, bool a_ExStart= false);
	void PExplodeDestroy();
};

extern CHeroEx g_HeroEx;
