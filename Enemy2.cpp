#include "DXUT.h"
#include "stdafx.h"

Enemy2::Enemy2()
{
	Init();
}

Enemy2::~Enemy2()
{
	Release();
}

void Enemy2::Init()
{
	OBJMAN()->LoadData(L"Data\\Enemy2.png", 120, 60, &pTex);
	vPos = { 0, 0, 0 };
	rRect = { 0, 0, 60, 60 };
	rHitBox = { 28, 34, 116, 120 };
	bVisible = false;
	uiColor = 0xffffffff;

	iSpeed = 3 + rand() % 3;
	iHP = 0;

	for (int i = 0; i < 2; i++)
		rAnimation[i] = { i * rRect.right, 0, (i + 1) * rRect.right, rRect.bottom };
	iAniTime = 0;
	iAnii = 0;

	rRader = { rRect.left - 150, rRect.top - 150, rRect.right + 150, rRect.bottom + 150 };
	bLockOn = false;

	rGuided = { rRect.left - 200, rRect.top - 200, rRect.right + 200, rRect.bottom + 200 };

	OBJMAN()->LoadData(L"Data\\Effect1.png", 840, 140, &pEffectTex);
	for (int i = 0; i < 6; i++)
		rEffectRect[i] = { i * 140, 0, (i + 1) * 140, 140 };
	iEffectTime = 0;
	iEffectCount = 0;
	bEffectVisible = false;

	for (int i = 0; i < 10; i++)
		m_eEnemy2Bullet[i] = new Enemy2Bullet;
	iFireTime = 0;
	iBulletCount = 0;
}

void Enemy2::Release()
{
	pTex->Release();
	pEffectTex->Release();

	for (int i = 0; i < 10; i++)
		m_eEnemy2Bullet[i]->Release();
}

void Enemy2::Spawn()
{
	bVisible = true;
	vPos.x = rand() % (SCREEN_WIDTH - rRect.right);
	vPos.y = -rRect.bottom;
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
}

void Enemy2::Move()
{
	if (bVisible || bEffectVisible)
		vPos.y += iSpeed;
}

void Enemy2::Animation()
{
	iAniTime++;
	if (iAniTime >= 5)
	{
		iAniTime = 0;
		iAnii++;
		if (iAnii >= 2)
			iAnii = 0;
	}
}

void Enemy2::Collision()
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

	//LockOn
	bLockOn = false;
	if (OBJMAN()->Collision(OBJMAN()->GetPlayerPos(), OBJMAN()->GetPlayerRect(), vPos, rRader)
		&& bVisible)
		bLockOn = true;

	//Guided
	for (int i = 0; i < 50; i++)
		if (OBJMAN()->Collision(OBJMAN()->GetPlayerBulletPos(i), OBJMAN()->GetPlayerBulletRect(), vPos, rGuided)
			&& bVisible && OBJMAN()->GetPlayerBulletVisible(i))
			OBJMAN()->PlayerGuidedMissile(i, vPos, rRect);
}

void Enemy2::Down()
{
	if (bVisible && iHP <= 0)
	{
		bVisible = false;
		bEffectVisible = true;
		iEffectTime = 0;
		iEffectCount = 0;
		vPos.x = vPos.x + rRect.right / 2 - rEffectRect[0].right / 2;
		vPos.y = vPos.y + rRect.bottom / 2 - rEffectRect[0].bottom / 2;
		OBJMAN()->PlusScore(300);
		SNDMAN()->PlayBoom();
	}
}

void Enemy2::Hit(int iDmg)
{
	iHP -= iDmg;
	OBJMAN()->PlusScore(100);
}

void Enemy2::OutScreen()
{
	if (vPos.x <= -rRect.right || vPos.y <= -rRect.bottom ||
		vPos.x >= SCREEN_WIDTH || vPos.y >= SCREEN_HEIGHT)
		bVisible = false;
}

void Enemy2::Effect()
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

void Enemy2::Fire()
{
	if (bVisible && vPos.y <= 700)
	{
		iFireTime++;
		if (iFireTime >= 120)
		{
			iFireTime = 0;
			m_eEnemy2Bullet[iBulletCount]->Spawn(vPos, rRect);
			iBulletCount++;
			if (iBulletCount >= 10)
				iBulletCount = 0;
		}
	}
}

void Enemy2::Update()
{
	Move();
	Animation();
	Collision();
	Down();
	OutScreen();
	Effect();
	Fire();

	for (int i = 0; i < 10; i++)
		m_eEnemy2Bullet[i]->Update();
}

void Enemy2::Render()
{
	for (int i = 0; i < 10; i++)
		m_eEnemy2Bullet[i]->Render();

	if (bVisible)
		OBJMAN()->Draw(pTex, rAnimation[iAnii], vPos, uiColor);

	if (bEffectVisible)
		OBJMAN()->Draw(pEffectTex, rEffectRect[iEffectCount], vPos, 0xffffffff);
}
