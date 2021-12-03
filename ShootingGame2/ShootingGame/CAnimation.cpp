#include "stdafx.h"
#include "CAnimation.h"


CAnimation::CAnimation()
{
	for (int ii = 0; ii < AniLength; ii++)
	{
		CAniMotion* a_Node = new CAniMotion();
		m_AniMoList.push_back(a_Node);
	}



}


CAnimation::~CAnimation()
{
	for (int i = 0; i < m_AniMoList.size(); i++)
	{
		if (m_AniMoList[i] != NULL)
		{
			delete m_AniMoList[i];
			m_AniMoList[i] = NULL;
		}
	}

	m_AniMoList.clear();

}


void CAnimation::CAni_LoadAnimList(CharType a_CharType)
{




	
	if (a_CharType == RealPlayer) //RealPlayer
	{
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle01.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle02.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle03.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle04.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle05.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle06.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle07.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle08.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle09.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle10.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle11.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle12.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle13.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle14.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle15.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle16.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\RealPlayer\\idle17.png")); //
	}
	else if (a_CharType == Player) //Player
	{

		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Bolt\\Idle\\i01.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Bolt\\Idle\\i02.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Bolt\\Idle\\i03.png")); //
		 
		m_AniMoList[(int)Front_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Front_Walk\\f01.png")); //
		m_AniMoList[(int)Front_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Front_Walk\\f02.png")); //
		m_AniMoList[(int)Front_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Front_Walk\\f03.png")); //
		m_AniMoList[(int)Front_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Front_Walk\\f04.png")); //
		  
		//AniMoListst[(int)Back_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Back_Walk\\b01.png")); //
		m_AniMoList[(int)Back_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Back_Walk\\b02.png")); //
		m_AniMoList[(int)Back_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Back_Walk\\b03.png")); //
		m_AniMoList[(int)Back_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Back_Walk\\b04.png")); //
		 
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Left_Walk\\l01.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Left_Walk\\l02.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Left_Walk\\l03.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Left_Walk\\l04.png")); //
		 
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Right_Walk\\r01.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Right_Walk\\r02.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Right_Walk\\r03.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Right_Walk\\r04.png")); //
		 
		//AniMoList
		 
		m_AniMoList[(int)Dead]->LoadTexImg(_T(".\\Reso\\Bolt\\Blood\\dead01.png")); //
		m_AniMoList[(int)Dead]->LoadTexImg(_T(".\\Reso\\Bolt\\Blood\\dead02.png")); //
		m_AniMoList[(int)Dead]->LoadTexImg(_T(".\\Reso\\Bolt\\Blood\\dead03.png")); //
		m_AniMoList[(int)Dead]->LoadTexImg(_T(".\\Reso\\Bolt\\Blood\\dead04.png")); //
		m_AniMoList[(int)Dead]->LoadTexImg(_T(".\\Reso\\Bolt\\Blood\\dead05.png")); //
		m_AniMoList[(int)Dead]->LoadTexImg(_T(".\\Reso\\Bolt\\Blood\\dead06.png")); //
		m_AniMoList[(int)Dead]->LoadTexImg(_T(".\\Reso\\Bolt\\Blood\\dead07.png")); //
		m_AniMoList[(int)Dead]->LoadTexImg(_T(".\\Reso\\Bolt\\Blood\\dead08.png")); //
		m_AniMoList[(int)Dead]->LoadTexImg(_T(".\\Reso\\Bolt\\Blood\\dead09.png")); //

	}
	else if (a_CharType == Bullet) //bullet
	{
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Right_Bolt\\rightbolt01.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Right_Bolt\\rightbolt02.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Right_Bolt\\rightbolt03.png")); //
		 
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Left_Bolt\\Leftbolt01.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Left_Bolt\\Leftbolt02.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Bolt\\Left_Bolt\\Leftbolt03.png")); //
	}

	else if (a_CharType == PlayerExplode) //plex
	{
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex01.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex02.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex03.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex04.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex05.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex06.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex07.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex08.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex09.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex10.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex11.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex12.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex13.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex14.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex15.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex16.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex17.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex18.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex19.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex20.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex21.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex22.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex23.png")); //
		m_AniMoList[(int)EX_Walk]->LoadTexImg(_T(".\\Reso\\Explode\\ex24.png")); //

	}

	//else if (a_CharType == Potion) //Gold
	//{
	//	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Potion\potion.png")); //
	//}
	else if (a_CharType == Gold) //Gold
	{
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold01.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold02.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold03.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold04.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold05.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold06.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold07.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold08.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold09.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold10.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold11png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold12.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold13.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold14.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold15.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold16.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold17.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold18.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold19.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold20.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold21.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold22.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold23.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold24.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold25.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold26.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold27.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold28.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold29.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold30.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold31.png")); //
		m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Gold\\Gold32.png")); //
	
	}

	else if (a_CharType == Silver) //bullet
	{
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver01.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver02.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver03.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver04.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver05.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver06.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver07.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver08.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver09.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver10.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver11png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver12.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver13.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver14.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver15.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver16.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver17.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver18.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver19.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver20.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver21.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver22.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver23.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver24.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver25.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver26.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver27.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver28.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver29.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver30.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver31.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver32.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\Silver\\Silver33.png")); //

	}



	else if (a_CharType == DeadCoin) //DeadCoin
	{
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead01.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead02.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead03.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead04.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead05.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead06.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead07.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead08.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead09.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead10.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead11png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead12.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead13.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead14.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead15.png")); //
	m_AniMoList[(int)Coin_Walk]->LoadTexImg(_T(".\\Reso\\Coin\\DeadCoin\\Dead16.png")); //


	}

	else if (a_CharType == Shield) //DeadCoin
	{
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Shield\\sh01.png")); //
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Shield\\sh02.png")); //
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Shield\\sh03.png")); //
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Shield\\sh04.png")); //
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Shield\\sh05.png")); //
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Shield\\sh06.png")); //
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Shield\\sh07.png")); //
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Shield\\sh08.png")); //


	}



	else if (a_CharType== Enemy01) //enemy
	{


		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Left_Walk\\left01.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Left_Walk\\left02.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Left_Walk\\left03.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Left_Walk\\left04.png")); //
															 
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Left_Walk\\left01.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Left_Walk\\left02.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Left_Walk\\left03.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Left_Walk\\left04.png")); //
															  
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Right_Walk\\right01.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Right_Walk\\right02.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Right_Walk\\right03.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon1\\Right_Walk\\right04.png")); //
	}

	else if (a_CharType == Enemy02) //enemy µÅÁö
	{
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\left01.png")); 
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\left02.png"));
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\left03.png"));
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\left04.png"));

		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\left01.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\left02.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\left03.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\left04.png")); //

		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\right01.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\right02.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\right03.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon2\\right04.png")); //
	}

	else if (a_CharType == Enemy03) //ºí·¢¸Ç
	{
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon3\\left01.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon3\\left02.png")); //
		m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon3\\left03.png")); //

		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon3\\left01.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon3\\left02.png")); //
		m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon3\\left03.png")); //

		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon3\\right01.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon3\\right02.png")); //
		m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon3\\right03.png")); //
	}

	else if (a_CharType == Enemy04) //¾ó±¼
	{
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon4\\left01.png")); //
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon4\\left02.png")); //


	m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon4\\left01.png")); //
	m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon4\\left02.png")); //


	m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon4\\right01.png")); //
	m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon4\\right02.png")); //

	}

	else if (a_CharType == Enemy05) //¾ó±¼
	{
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon5\\left01.png")); //
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon5\\left02.png")); //


	m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon5\\left01.png")); //
	m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon5\\left02.png")); //


	m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon5\\right01.png")); //
	m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon5\\right02.png")); //

	}

	else if (a_CharType == Enemy06) //enemy µÅÁö
	{
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\left01.png"));
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\left02.png"));
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\left03.png"));
	m_AniMoList[(int)Idle]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\left04.png"));

	m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\left01.png")); //
	m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\left02.png")); //
	m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\left03.png")); //
	m_AniMoList[(int)Left_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\left04.png")); //

	m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\right01.png")); //
	m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\right02.png")); //
	m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\right03.png")); //
	m_AniMoList[(int)Right_Walk]->LoadTexImg(_T(".\\Reso\\Mon\\Mon6\\right04.png")); //
	}

	else if (a_CharType == Explode) //ÆøÆÈ
	{ 
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex1.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex2.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex3.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex4.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex5.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex6.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex7.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex8.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex9.png")); //
						
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex10.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex11.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex12.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex13.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex14.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex15.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex16.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex17.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex18.png")); //
						
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex19.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex20.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex21.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex22.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex23.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex24.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex25.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex26.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex27.png")); //
		  				
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex28.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex29.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex30.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex31.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex32.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex33.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex34.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex35.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex36.png")); //
						
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex37.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex38.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex39.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex40.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex41.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex42.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex43.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex44.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex45.png")); //
		 				
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex46.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex47.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex48.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex49.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex50.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex51.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex52.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex53.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex54.png")); //
		  				
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex55.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex56.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex57.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex58.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex59.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex60.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex61.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex62.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex63.png")); //
		  				 
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex64.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex65.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex66.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex67.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex68.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex69.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex70.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex71.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex72.png")); //
						 
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex73.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex74.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex75.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex76.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex77.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex78.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex79.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex80.png")); //
		m_AniMoList[(int)Dead_Walk]->LoadTexImg(_T(".\\Reso\\Explosion\\ex81.png")); //

	}



}

