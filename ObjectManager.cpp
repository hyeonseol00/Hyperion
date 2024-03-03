#include "DXUT.h"
#include "stdafx.h"

ObjectManager ObjectManager::singleton;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::LoadData(LPCWSTR pFile, int width, int height, LPDIRECT3DTEXTURE9* pTex)
{
	D3DXCreateTextureFromFileEx(DXUTGetD3D9Device(), pFile, width, height, 0, false, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL, pTex);
}

void ObjectManager::Draw(LPDIRECT3DTEXTURE9 pTex, RECT rRect, D3DXVECTOR3 vPos, UINT uiColor)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->Draw(pTex, &rRect, NULL, &vPos, uiColor);

	pSprite->End();
}

bool ObjectManager::Collision(D3DXVECTOR3 vOpponentPos, RECT rOpponentRect, D3DXVECTOR3 vPos, RECT rRect)
{
	if (vOpponentPos.x + rOpponentRect.left <= vPos.x + rRect.right &&
		vOpponentPos.y + rOpponentRect.top <= vPos.y + rRect.bottom &&
		vOpponentPos.x + rOpponentRect.right >= vPos.x + rRect.left &&
		vOpponentPos.y + rOpponentRect.bottom >= vPos.y + rRect.top)
		return true;
	
	return false;
}

void ObjectManager::Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &pSprite);

	uiScore = 0;

	stagestate = STAGE1;
	stagephase = PHASE1;

	iEnemy1Time = 0;
	iEnemy1Count = 0;

	iEnemy2Time = 0;
	iEnemy2Count = 0;

	iEnemy3Time = 0;
	iEnemy3Count = 0;

	iEnemy4Time = 0;
	iEnemy4Count = 0;

	iItemTime = 0;
	iItemCount = 0;

	iObstacleTime = 0;
	iObstacleCount = 0;

	m_iIntro = new Intro;
	m_mMenu = new Menu;

	m_bBackGround = new BackGround;
	m_pPlayer = new Player;
	for (int i = 0; i < 25; i++)
		m_eEnemy1[i] = new Enemy1;
	for (int i = 0; i < 25; i++)
		m_eEnemy2[i] = new Enemy2;
	for (int i = 0; i < 25; i++)
		m_eEnemy3[i] = new Enemy3;
	for (int i = 0; i < 25; i++)
		m_eEnemy4[i] = new Enemy4;
	for (int i = 0; i < 25; i++)
		m_iItem[i] = new Item;
	for (int i = 0; i < 25; i++)
		m_oObstacle[i] = new Obstacle;
	m_bBoss1 = new Boss1;
	m_bBoss2 = new Boss2;
	m_bBoss3 = new Boss3;
	m_bBoss4 = new Boss4;
	m_uUserInterface = new UserInterface;
}

void ObjectManager::Release()
{
	if (pSprite != NULL)
		pSprite->Release();

	m_iIntro->Release();
	m_mMenu->Release();

	m_bBackGround->Release();
	m_pPlayer->Release();
	for (int i = 0; i < 25; i++)
	{
		m_eEnemy1[i]->Release();
		m_eEnemy2[i]->Release();
		m_eEnemy3[i]->Release();
		m_eEnemy4[i]->Release();
		m_iItem[i]->Release();
		m_oObstacle[i]->Release();
	}
	m_bBoss1->Release();
	m_bBoss2->Release();
	m_bBoss3->Release();
	m_bBoss4->Release();
	m_uUserInterface->Release();
}

void ObjectManager::StageInit()
{
	stagephase = PHASE1;

	iEnemy1Time = 0;
	iEnemy1Count = 0;

	iEnemy2Time = 0;
	iEnemy2Count = 0;

	iEnemy3Time = 0;
	iEnemy3Count = 0;

	iEnemy4Time = 0;
	iEnemy4Count = 0;

	iItemTime = 0;
	iItemCount = 0;

	iObstacleTime = 0;
	iObstacleCount = 0;

	m_bBackGround = new BackGround;
	for (int i = 0; i < 25; i++)
		m_eEnemy1[i] = new Enemy1;
	for (int i = 0; i < 25; i++)
		m_eEnemy2[i] = new Enemy2;
	for (int i = 0; i < 25; i++)
		m_eEnemy3[i] = new Enemy3;
	for (int i = 0; i < 25; i++)
		m_eEnemy4[i] = new Enemy4;
	for (int i = 0; i < 25; i++)
		m_iItem[i] = new Item;
	for (int i = 0; i < 25; i++)
		m_oObstacle[i] = new Obstacle;
	m_bBoss1 = new Boss1;
	m_bBoss2 = new Boss2;
	m_bBoss3 = new Boss3;
	m_bBoss4 = new Boss4;
	m_uUserInterface = new UserInterface;
}

void ObjectManager::StageRelease()
{
	m_bBackGround->Release();
	for (int i = 0; i < 25; i++)
	{
		m_eEnemy1[i]->Release();
		m_eEnemy2[i]->Release();
		m_eEnemy3[i]->Release();
		m_eEnemy4[i]->Release();
		m_iItem[i]->Release();
		m_oObstacle[i]->Release();
	}
	m_bBoss1->Release();
	m_bBoss2->Release();
	m_bBoss3->Release();
	m_bBoss4->Release();
	m_uUserInterface->Release();
}

void ObjectManager::IntroUpdate() { m_iIntro->Update(); }
void ObjectManager::IntroRender() { m_iIntro->Render(); }
void ObjectManager::MenuUpdate() { m_mMenu->Update(); }
void ObjectManager::MenuRender() { m_mMenu->Render(); }

void ObjectManager::Stage1Spawn()
{
	iEnemy1Time++;
	if (iEnemy1Time >= 50)
	{
		iEnemy1Time = 0;
		m_eEnemy1[iEnemy1Count]->Spawn();
		iEnemy1Count++;
		if (iEnemy1Count >= 25)
			iEnemy1Count = 0;
	}

	iEnemy2Time++;
	if (iEnemy2Time >= 60)
	{
		iEnemy2Time = 0;
		m_eEnemy2[iEnemy2Count]->Spawn();
		iEnemy2Count++;
		if (iEnemy2Count >= 25)
			iEnemy2Count = 0;
	}

	iItemTime++;
	if (iItemTime >= 150)
	{
		iItemTime = 0;
		m_iItem[iItemCount]->Spawn();
		iItemCount++;
		if (iItemCount >= 25)
			iItemCount = 0;
	}

	iObstacleTime++;
	if (iObstacleTime >= 180)
	{
		iObstacleTime = 0;
		m_oObstacle[iObstacleCount]->Spawn();
		iObstacleCount++;
		if (iObstacleCount >= 25)
			iObstacleCount = 0;
	}
}

void ObjectManager::Stage1Update()
{
	m_bBackGround->Update();
	m_pPlayer->Update();

	Stage1Spawn();
	for (int i = 0; i < 25; i++)
	{
		m_eEnemy1[i]->Update();
		m_eEnemy2[i]->Update();
		m_iItem[i]->Update();
		m_oObstacle[i]->Update();
	}

	m_bBoss1->Update();
	m_bBoss2->Update();

	m_uUserInterface->Update();
}

void ObjectManager::Stage1Render()
{
	m_bBackGround->Render();
	for (int i = 0; i < 25; i++)
	{
		m_oObstacle[i]->Render();
		m_eEnemy1[i]->Render();
		m_eEnemy2[i]->Render();
		m_iItem[i]->Render();
	}
	m_bBoss1->Render();
	m_bBoss2->Render();

	m_pPlayer->Render();

	m_bBackGround->Render3();
	m_uUserInterface->Render();
}

//
//	Stage2
//

void ObjectManager::Stage2Spawn()
{
	iEnemy1Time++;
	if (iEnemy1Time >= 50)
	{
		iEnemy1Time = 0;
		m_eEnemy1[iEnemy1Count]->Spawn();
		iEnemy1Count++;
		if (iEnemy1Count >= 25)
			iEnemy1Count = 0;
	}

	iEnemy2Time++;
	if (iEnemy2Time >= 60)
	{
		iEnemy2Time = 0;
		m_eEnemy2[iEnemy2Count]->Spawn();
		iEnemy2Count++;
		if (iEnemy2Count >= 25)
			iEnemy2Count = 0;
	}

	iEnemy3Time++;
	if (iEnemy3Time >= 70)
	{
		iEnemy3Time = 0;
		m_eEnemy3[iEnemy3Count]->Spawn();
		iEnemy3Count++;
		if (iEnemy3Count >= 25)
			iEnemy3Count = 0;
	}

	iEnemy4Time++;
	if (iEnemy4Time >= 80)
	{
		iEnemy4Time = 0;
		m_eEnemy4[iEnemy4Count]->Spawn();
		iEnemy4Count++;
		if (iEnemy4Count >= 25)
			iEnemy4Count = 0;
	}

	iItemTime++;
	if (iItemTime >= 150)
	{
		iItemTime = 0;
		m_iItem[iItemCount]->Spawn();
		iItemCount++;
		if (iItemCount >= 25)
			iItemCount = 0;
	}

	iObstacleTime++;
	if (iObstacleTime >= 180)
	{
		iObstacleTime = 0;
		m_oObstacle[iObstacleCount]->Spawn();
		iObstacleCount++;
		if (iObstacleCount >= 25)
			iObstacleCount = 0;
	}
}

void ObjectManager::Stage2Update()
{
	m_bBackGround->Update();
	m_pPlayer->Update();

	Stage2Spawn();
	for (int i = 0; i < 25; i++)
	{
		m_eEnemy1[i]->Update();
		m_eEnemy2[i]->Update();
		m_eEnemy3[i]->Update();
		m_eEnemy4[i]->Update();
		m_iItem[i]->Update();
		m_oObstacle[i]->Update();
	}

	m_bBoss3->Update();
	m_bBoss4->Update();

	m_uUserInterface->Update();
}

void ObjectManager::Stage2Render()
{
	m_bBackGround->Render();
	for (int i = 0; i < 25; i++)
	{
		m_oObstacle[i]->Render();
		m_eEnemy1[i]->Render();
		m_eEnemy2[i]->Render();
		m_eEnemy3[i]->Render();
		m_eEnemy4[i]->Render();
		m_iItem[i]->Render();
	}
	m_bBoss3->Render();
	m_bBoss4->Render();

	m_pPlayer->Render();

	m_bBackGround->Render3();
	m_uUserInterface->Render();
}

void ObjectManager::SetRanking()
{
	if (uiScore > GAAPP()->GetRankScore(2))
	{
		if (uiScore > GAAPP()->GetRankScore(1))
		{
			if (uiScore > GAAPP()->GetRankScore(0))
			{
				GAAPP()->SetRankScore(2, GAAPP()->GetRankScore(1));
				GAAPP()->SetRankScore(1, GAAPP()->GetRankScore(0));
				GAAPP()->SetRankScore(0, uiScore);
				GAAPP()->SetRankInitial(2, GAAPP()->GetRankInitial(1));
				GAAPP()->SetRankInitial(1, GAAPP()->GetRankInitial(0));
				GAAPP()->SetRankInitial(0, m_mMenu->GetInitial());
				return;
			}
			GAAPP()->SetRankScore(2, GAAPP()->GetRankScore(1));
			GAAPP()->SetRankScore(1, uiScore);
			GAAPP()->SetRankInitial(2, GAAPP()->GetRankInitial(1));
			GAAPP()->SetRankInitial(1, m_mMenu->GetInitial());
			return;
		}
		GAAPP()->SetRankScore(2, uiScore);
		GAAPP()->SetRankInitial(2, m_mMenu->GetInitial());
		return;
	}
}

