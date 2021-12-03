#include "stdafx.h"
#include "CMonster_Mgr.h"
#include "CHero.h" //�÷��̾��� ���� �浹������
#include "GlovalValue.h"
#include "CItem_Mgr.h"
#include "CShield.h"


CMonster::CMonster()
{
	m_isActive = false; //false�� �ʱ�ȭ 

	m_MaxHP = 200.0f; 
	m_MonHp = 200.0f;

	m_Speed = 150.0f; //���ͼӵ�
	m_HalfColl = 20;  //������ �ݰ�Ÿ� 

}

CMonster::~CMonster()
{


}

void CMonster::Init_Unit()
{


}

void CMonster::Update_Unit(float a_DeltaTime, CHero & a_Hero)
{
	Vector2D a_CacVec = a_Hero.m_CurPos - m_CurPos;
	//�ǵ� �ݰ�
	/*if (0.0f < g_Shield.m_SdOnTime)
	{
		if (a_CacVec.Magnitude() < g_Shield.m_SdHalfSize)
		{
			a_DeltaTime = a_DeltaTime * 0.05f;
		}
	}*/


	//MonSter AI
	if (a_Hero.m_HalfColl + m_HalfColl < a_CacVec.Magnitude()) //�浹 �ݰ��� 
	{
		
		
		
		//����
		m_DirVec = a_CacVec; //������ ���� ����
		m_DirVec.Normalize();
		m_CurPos = m_CurPos + (m_DirVec * (a_DeltaTime * m_Speed));



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
			a_Hero.TakeDamage(10);

			m_AttackTick = 1.0f; //����
		}
	}
	//---------------------���� ����ó�� �κ�
	if (0.0f < a_CacVec.x)
	{
		ChangeState(Right_Walk);
	}
	else
	{
		ChangeState(Left_Walk);
	}
	//----------�ִϸ��̼� �÷��� ���
	CUnit::Update_Unit(a_DeltaTime);
}

void CMonster::Render_Unit(HDC a_hDC, HBRUSH & a_R_brsh)
{
	if (m_SocketImg == NULL)
		return;

	//----hp bar
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hDC, a_R_brsh);
	static float a_CacMXX = 0.0f;
	static float a_CacMYY = (int)(m_HalfHeight * 0.8f); //�Ӹ��� ���̰� ���̺���
	static float a_HpBSize = 50;
	static float a_CurHpSize = 0;
	a_CacMXX = a_HpBSize / 2.0f;
	a_CurHpSize = a_HpBSize * ((float)m_MonHp / (float)m_MaxHP);

	a_CacMYY = m_HalfHeight * 1.2f; //((int)m_HalfHeight * 1.1f)  //ũ�⿡ ���� �������� �ٲ��

	Rectangle(a_hDC, m_CurPos.x - a_CacMXX, m_CurPos.y - a_CacMYY,
		m_CurPos.x - a_CacMXX + a_CurHpSize,
		m_CurPos.y - (a_CacMYY + 10.0f));
	SelectObject(a_hDC, h_Old_Brush);

	//-----hp bar


	Graphics graphics(a_hDC);
	graphics.DrawImage(m_SocketImg, m_CurPos.x - m_HalfWidth,
		m_CurPos.y - (int)(m_HalfHeight * 1.2f),
		(float)m_ImgSizeX, (float)m_ImgSizeY);

}

void CMonster::Destroy_Unit()
{


}

void CMonster::Reset_Unit()
{
	m_isActive = false; //false�� �ʱ�ȭ 

	m_MaxHP = 200.0f;
	m_MonHp = 200.0f;

	m_Speed = 150.0f; //���ͼӵ�
	m_HalfColl = 20;  //������ �ݰ�Ÿ� 


}

void CMonster::Spawn(float a_XX, float a_YY)
{
	//���̵��� ���� �̼Ӻ���
	m_Speed = 150.0f + ((g_DiffLevel - 1) * 30.0f);

	m_CurPos.x = a_XX;
	m_CurPos.y = a_YY;

	m_isActive = true;

	m_MonHp = m_MaxHP;

	SetAni_Rsc(m_CharType);
	

}

void CMonster::LoadUnitSize()
{
	

}

void CMonster::TakeDamage(float a_Value)
{

	m_MonHp = m_MonHp - a_Value;

	if (m_MonHp <= 0.0f)
	{
		g_Hero.m_KillCount++;
		g_ItemMgr.SpawnItem(m_CurPos);
		m_isActive = false; //���
	}
}

////////////////////////////////////////////////////////

CMonster_Mgr::CMonster_Mgr()
{


}


CMonster_Mgr::~CMonster_Mgr()
{


}

void CMonster_Mgr::MonMgr_Init()
{
	//Image * a_ImgeNode = NULL;

	//a_ImgeNode = Image::FromFile(_T(".\\Reso\\Mon\\Mon1\\Right_Walk\\right01.png"));
	//m_ImgList.push_back(a_ImgeNode);

	//���� �޸�Ǯ�� �̸������ ���� 
	CMonster* a_Node = NULL;

;

	for (int i = 0; i < 20; i++)
	{
		//	a_Node->Init_Unit();
		a_Node = new CMonster();
		m_MonList.push_back(a_Node);
	}
	//���� �޸�Ǯ�� �̸������ ���� 

	m_R_brsh = CreateSolidBrush(RGB(255, 0, 0)); //�������� 

}

void CMonster_Mgr::MonMgr_Update(float a_DeltaTime, HWND a_hWnd, CHero & a_Hero)
{
	//---------- �ֱ����� Monster Spawn   
	SpawnMonster(a_DeltaTime, a_hWnd);
	//---------- �ֱ����� Monster Spawn  

	//-----------Monster AI
	//���� ���� ��ġ�� �ʰ� �ϱ� ���� ����...
	static Vector2D a_CacVec;
	static float a_CacSDist;
	static float a_CacMargin = 0.0f;
	static float a_RadiusHap;
	static Vector2D a_CacMovePos;
	static Vector2D a_CacSNormal;
	static float a_CacShiftLen = 0.0f;

	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == false)
			continue;

		if (g_GameState == GAME_PILSALSTART)
			continue;

		m_MonList[ii]->Update_Unit(a_DeltaTime, a_Hero);

		//���� ���� ��ġ�� �ʰ� �ϱ�...
		for (int xx = 0; xx < m_MonList.size(); xx++)
		{
			if (m_MonList[ii] == m_MonList[xx])
				continue;

			if (m_MonList[xx]->m_isActive == false)
				continue;

			a_CacVec = m_MonList[ii]->m_CurPos - m_MonList[xx]->m_CurPos;
			//��Ÿ��󽺷� ����ؼ� �Ÿ��� �˼��ִ�
			a_CacSDist = a_CacVec.Magnitude();
			//�����浹 �Ǻ� 1������ 2������ �Ÿ��� 
			a_RadiusHap = m_MonList[ii]->m_HalfColl + 4 + m_MonList[xx]->m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��

			a_CacMovePos = m_MonList[ii]->m_CurPos;

			if (a_CacSDist < a_RadiusHap) //��ģ ����
			{
				//����
				a_CacMargin = a_RadiusHap - a_CacSDist;
				a_CacSNormal = a_CacVec; //�з����� ����
				a_CacSNormal.Normalize();

				a_CacShiftLen = a_CacMargin;
				if (a_RadiusHap < a_CacShiftLen) //������ġ �ð����ݵ� ���������� Ŀ���� �ȵȴ�. 
				{
					a_CacShiftLen = a_RadiusHap;
				}

				a_CacMovePos = a_CacMovePos + (a_CacSNormal * a_CacShiftLen);

			}//if (a_CacSDist < a_RadiusHap)

			m_MonList[ii]->m_CurPos = a_CacMovePos;
		}
		//���� ���� ��ġ�� �ʰ� �ϱ�...

		//------- ���ΰ����� �浹ó��
		a_CacVec = m_MonList[ii]->m_CurPos - a_Hero.m_CurPos;
		a_CacSDist = a_CacVec.Magnitude();
		a_RadiusHap = m_MonList[ii]->m_HalfColl + 4 + a_Hero.m_HalfColl + 4; //(���ݰ� + ���ݰ�) ���� ��Ȱ��

		a_CacMovePos = m_MonList[ii]->m_CurPos;

		if (a_CacSDist < a_RadiusHap)
		{
			a_CacMargin = a_RadiusHap - a_CacSDist;
			a_CacSNormal = a_CacVec; //�з����� ����
			a_CacSNormal.Normalize();

			a_CacShiftLen = a_CacMargin;
			if (a_RadiusHap < a_CacShiftLen) //������ġ �ð����ݵ� ���������� Ŀ���� �ȵȴ�. 
			{
				a_CacShiftLen = a_RadiusHap;
			}

			a_CacMovePos = a_CacMovePos + (a_CacSNormal * a_CacShiftLen);

		}//if (a_CacSDist < a_RadiusHap)

		m_MonList[ii]->m_CurPos = a_CacMovePos;
		//------- ���ΰ����� �浹ó��

	}//for (int ii = 0; ii < m_MonList.size(); ii++)
	//-----------Monster AI

}

void CMonster_Mgr::MonMgr_Render(HDC a_hDC)
{
	//���� �̹��� �׸���
	for (int i = 0; i < m_MonList.size(); i++)
	{
		if (m_MonList[i]->m_isActive == false)
			continue;

		m_MonList[i]->Render_Unit(a_hDC, m_R_brsh);
	}
	//���� �̹��� �׸���

}

void CMonster_Mgr::MonMgr_Destroy()
{
	


	//���� �޸�Ǯ �����ϱ�... 
	for (int aii = 0; aii < m_MonList.size(); aii++)
	{
		if (m_MonList[aii] != NULL)
		{
			m_MonList[aii]->Destroy_Unit();

			delete m_MonList[aii];
			m_MonList[aii] = NULL;
		}
	}
	m_MonList.clear();
	//���� �޸�Ǯ �����ϱ�... 

	if (m_R_brsh != NULL)
	{
		DeleteObject(m_R_brsh);//brush object ����
		m_R_brsh = NULL;
	}


}

void CMonster_Mgr::MonMgr_Reset()
{
	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		m_MonList[ii]->m_isActive = false;
	}

//	g_MonCount = 0;

	

}

void CMonster_Mgr::SpawnMonster(float a_DeltaTime, HWND a_hWnd)
{
	//--- ���� Active ���� �� ������ ī��Ʈ 
	/*static int g_MonCount = 0;*/
	
	g_MonCount = 0;
	for (int ii = 0; ii < m_MonList.size(); ii++)
	{
		if (m_MonList[ii]->m_isActive == true)
		{
		
			g_MonCount++;
		}
	}
	//--- ���� Active ���� �� ������ ī��Ʈ 

	//---------- �ֱ����� Monster Spawn         //���� ���� ����
	static float a_SpawnTime = 0.0f;
	a_SpawnTime = a_SpawnTime - a_DeltaTime;
	if (a_SpawnTime < 0.0f)
	{
		m_SpawnLim = 6 + (g_DiffLevel - 2);
		if (m_SpawnLim < 6)
			m_SpawnLim = 6;

		if (10 < m_SpawnLim)
			m_SpawnLim = 10;

		for (int ii = 0; ii < m_MonList.size(); ii++)
		{
			if (m_SpawnLim <= g_MonCount)
				break;

			if (m_MonList[ii]->m_isActive == false)
			{
				////----------------------Random �ϰ� ���� ��ǥ �����ϴ� �κ� 
				////���� - [0] x�� -150.0f ~ -50.0f  Y�� -150.0f ~ (float)m_cRT.bottom + 150.0f
				////       [1] x�� -50.0f ~ (int)m_cRT.right + 50.0f  Y�� -150.0f ~ -50.0f
				////���� - [2] x�� (int)m_cRT.right + 50.0f ~ (int)m_cRT.right + 150.0f  Y�� -150.0f ~ (float)m_cRT.bottom + 150.0f
				////       [3] x�� -50.0f ~ (int)m_cRT.right + 50.0f  Y�� (float)m_cRT.bottom + 50.0f ~ (float)m_cRT.bottom + 150.0f
				////�翷 //�� �Ʒ� 4���� �Ѱ� ���� ���߿��� �������� �ɸ��� �ϴ� ����� �ִ�.

				static bool a_TicToc = true;
				//�ѹ��� x������ 
				//�ѹ��� y������

				GetClientRect(a_hWnd, &m_cRT); // Ŭ���̾�Ʈ ȭ���� ũ�⸦ �޴´�

				float a_XX = 0.0f;
				float a_YY = 0.0f;
				if (a_TicToc == true)
				{
					a_XX = (float)((rand() % 200) - 100);
					float a_PushVal = 50.0f;
					int a_YLenVal = (int)m_cRT.bottom + 100;

					if (a_XX < 0.0f)
					{
						a_XX = a_XX - a_PushVal;
					}
					else
					{
						a_XX = a_XX + (float)m_cRT.right + a_PushVal;
					}

					a_YY = (float)((rand() % a_YLenVal) + (100 / 2));

					a_TicToc = false;
				}
				else
				{
					a_YY = (float)((rand() % 200) - 100);
					float a_PushVal = 50.0f;
					int a_XLenVal = (int)m_cRT.right + 100;

					if (a_YY < 0.0f)
					{
						a_YY = a_YY - a_PushVal;
					}
					else
					{
						a_YY = a_YY + (float)m_cRT.bottom + a_PushVal;
					}

					a_XX = (float)((rand() % a_XLenVal) - (100 / 2));

					a_TicToc = true;
				}
				////----------------------Random �ϰ� ���� ��ǥ �����ϴ� �κ� 
				m_MonList[ii]->m_CharType = GetSpMonType();
				m_MonList[ii]->Spawn(a_XX, a_YY);

				break;

			}//if (m_MonList[ii]->m_isActive == false)
		}//for (int ii = 0; ii < m_MonList.size(); ii++)
		//�������� �Ÿ��� ������ + ������ ���� �պ��� �۰ų������� �浹 
		a_SpawnTime = GetSpTimeLevel();
	}
	//---------- �ֱ����� Monster Spawn  

}

void CMonster_Mgr::ReSrcClear()
{


}

CharType CMonster_Mgr::GetSpMonType()
{
	CharType a_SpType = Enemy02;

	if (g_DiffLevel <= 1)
	{
		a_SpType = Enemy01;
	}
	else if (g_DiffLevel == 2)
	{
		a_SpType = Enemy02;
	}
	else if (g_DiffLevel == 3)
	{
		a_SpType = Enemy03;
	}
	else if (g_DiffLevel == 4)
	{
		a_SpType = Enemy04;
	}
	else if (g_DiffLevel == 5)
	{
		a_SpType = Enemy05;
	}
	else if (g_DiffLevel == 6)
	{
		a_SpType = Enemy06;
	}
	else
	{
		a_SpType = Enemy02;
	}


	return a_SpType;
}

float CMonster_Mgr::GetSpTimeLevel()
{
	float a_SpTime = 2.0f;

	if (g_DiffLevel <= 1)
	{
		a_SpTime = (float)((rand() % 3) + 2); //���������ð�����
	}
	else if (g_DiffLevel == 2)
	{
		a_SpTime = (float)((rand() % 3) + 1);
	}
	else if (g_DiffLevel == 3)
	{
		a_SpTime = (float)((rand() % 2) + 1);
	}
	else if (g_DiffLevel == 4)
	{
		a_SpTime = 1.0f;
	}
	else if (g_DiffLevel == 5)
	{
		a_SpTime = 0.5f;
	}
	else
	{
		a_SpTime = 0.3f;
	}

	return a_SpTime;
}


CMonster_Mgr g_Mon_Mgr;