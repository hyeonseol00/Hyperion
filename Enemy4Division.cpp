#include "DXUT.h"
#include "stdafx.h"

Enemy4Division::Enemy4Division()
{
	Init();
}

Enemy4Division::~Enemy4Division()
{
	Release();
}

void Enemy4Division::Init()
{
	OBJMAN()->LoadData(L"Data\\Enemy4Division.png", 100, 50, &pTex);
	vPos = { 0, 0, 0 };
	rRect = { 0, 0, 50, 50 };
	rHitBox = { 28, 34, 116, 120 };
	bVisible = false;
	uiColor = 0xffffffff;

	iSpeed = 3 + rand() % 3;
	iHP = 0;

	for (int i = 0; i < 2; i++)
		rAnimation[i] = { i * rRect.right, 0, (i + 1) * rRect.right, rRect.bottom };
	iAniTime = 0;
	iAnii = 0;

	rRader = { rRect.left - 150, rRect.bottom / 2, rRect.right + 150, rRect.bottom + 150 };
	bLockOn = false;

	rGuided = { rRect.left - 200, rRect.top - 200, rRect.right + 200, rRect.bottom + 200 };

	OBJMAN()->LoadData(L"Data\\Effect1.png", 840, 140, &pEffectTex);
	for (int i = 0; i < 6; i++)
		rEffectRect[i] = { i * 140, 0, (i + 1) * 140, 140 };
	iEffectTime = 0;
	iEffectCount = 0;
	bEffectVisible = false;

	vDirectVec = { 0, 1 };

	iDirection = 0;
}

void Enemy4Division::Release()
{
	pTex->Release();
	pEffectTex->Release();
}

void Enemy4Division::Spawn(D3DXVECTOR3 vEnemyPos, RECT rEnemyRect, int iDirection)
{
	bVisible = true;
	this->iDirection = iDirection;
	switch (iDirection)
	{
	case 0:
		vPos.x = vEnemyPos.x + rEnemyRect.right / 2 - rRect.right / 2 - 40;
		vPos.y = vEnemyPos.y + rEnemyRect.bottom / 2 - rRect.bottom / 2;
		break;
	case 1:
		vPos.x = vEnemyPos.x + rEnemyRect.right / 2 - rRect.right / 2 + 40;
		vPos.y = vEnemyPos.y + rEnemyRect.bottom / 2 - rRect.bottom / 2;
		break;
	}
	iHP = 1 * (OBJMAN()->stagephase + 1);
	switch (OBJMAN()->stagephase)
	{
	case 0:
		uiColor = 0xffffffff;
		break;
	case 1:
		uiColor = 0xffffff7f;
		break;
	}
	vDirectVec.x = (vPos.x + rRect.right / 2 - OBJMAN()->GetPlayerRect().right / 2) - OBJMAN()->GetPlayerPos().x;
	vDirectVec.y = (vPos.y + rRect.bottom / 2 - OBJMAN()->GetPlayerRect().bottom / 2) - OBJMAN()->GetPlayerPos().y;
	D3DXVec2Normalize(&vDirectVec, &vDirectVec);
	vDirectVec = -vDirectVec;
	iSpeed = 7 + rand() % 3;
	bLockOn = false;
}

void Enemy4Division::Move()
{
	if (bVisible || bEffectVisible)
	{
		vPos.x += vDirectVec.x * iSpeed;
		vPos.y += vDirectVec.y * iSpeed;
	}
}

void Enemy4Division::Collision()
{
	//플레이어 몸빵
	if (OBJMAN()->Collision(OBJMAN()->GetPlayerPos(), OBJMAN()->GetPlayerHitBox(), vPos, rRect)
		&& bVisible)
	{
		OBJMAN()->PlayerHit(1);
		Crash();
	}

	//플레이어 탄환 히트
	for (int i = 0; i < 50; i++)
		if (OBJMAN()->Collision(OBJMAN()->GetPlayerBulletPos(i), OBJMAN()->GetPlayerBulletRect(), vPos, rRect)
			&& bVisible && OBJMAN()->GetPlayerBulletVisible(i))
		{
			Hit(1);
			OBJMAN()->PlayerBulletHit(i);
		}

	//애드온
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 25; j++)
			if (OBJMAN()->Collision(OBJMAN()->GetAddonBulletPos(i, j), OBJMAN()->GetPlayerBulletRect(), vPos, rRect)
				&& bVisible && OBJMAN()->GetAddonBulletVisible(i, j))
			{
				Hit(1);
				OBJMAN()->AddonBulletHit(i, j);
			}

	//Guided
	for (int i = 0; i < 50; i++)
		if (OBJMAN()->Collision(OBJMAN()->GetPlayerBulletPos(i), OBJMAN()->GetPlayerBulletRect(), vPos, rGuided)
			&& bVisible && OBJMAN()->GetPlayerBulletVisible(i))
			OBJMAN()->PlayerGuidedMissile(i, vPos, rRect);
}

void Enemy4Division::Down()
{
	if (bVisible && iHP <= 0)
	{
		bVisible = false;
		bEffectVisible = true;
		iEffectTime = 0;
		iEffectCount = 0;
		vPos.x = vPos.x + rRect.right / 2 - rEffectRect[0].right / 2;
		vPos.y = vPos.y + rRect.bottom / 2 - rEffectRect[0].bottom / 2;
		OBJMAN()->PlusScore(150);
		SNDMAN()->PlayBoom();
	}
}

void Enemy4Division::Hit(int iDmg)
{
	iHP -= iDmg;
	OBJMAN()->PlusScore(50);
}

void Enemy4Division::OutScreen()
{
	if (vPos.x <= -rRect.right || vPos.y <= -rRect.bottom ||
		vPos.x >= SCREEN_WIDTH || vPos.y >= SCREEN_HEIGHT)
		bVisible = false;
}

void Enemy4Division::Effect()
{
	if (bEffectVisible)
	{
		iEffectTime++;
		if (iEffectTime >= 5)
		{
			iEffectTime = 0;
			iEffectCount++;
			if (iEffectCount >= 6)
				bEffectVisible = false;
		}
	}
}

void Enemy4Division::Update()
{
	Move();
	Collision();
	Down();
	OutScreen();
	Effect();
}

void Enemy4Division::Render()
{
	if (bVisible)
		OBJMAN()->Draw(pTex, rAnimation[iDirection], vPos, uiColor);

	if (bEffectVisible)
		OBJMAN()->Draw(pEffectTex, rEffectRect[iEffectCount], vPos, 0xffffffff);
}
