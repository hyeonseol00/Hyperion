#include "DXUT.h"
#include "stdafx.h"

Enemy3::Enemy3()
{
	Init();
}

Enemy3::~Enemy3()
{
	Release();
}

void Enemy3::Init()
{
	OBJMAN()->LoadData(L"Data\\Enemy3.png", 1100, 100, &pTex);
	vPos = { 0, 0, 0 };
	rRect = { 0, 0, 100, 100 };
	rHitBox = { 28, 34, 116, 120 };
	bVisible = false;
	uiColor = 0xffffffff;

	iSpeed = 3 + rand() % 3;
	iHP = 0;

	for (int i = 0; i < 11; i++)
		rAnimation[i] = { i * rRect.right, 0, (i + 1) * rRect.right, rRect.bottom };
	iAniTime = 0;
	iAnii = 0;

	rRader = { rRect.left - 300, rRect.bottom / 2, rRect.right + 300, rRect.bottom + 300 };
	bLockOn = false;

	rGuided = { rRect.left - 200, rRect.top - 200, rRect.right + 200, rRect.bottom + 200 };

	OBJMAN()->LoadData(L"Data\\Effect1.png", 840, 140, &pEffectTex);
	for (int i = 0; i < 6; i++)
		rEffectRect[i] = { i * 140, 0, (i + 1) * 140, 140 };
	iEffectTime = 0;
	iEffectCount = 0;
	bEffectVisible = false;

	vDirectVec = { 0, 1 };
}

void Enemy3::Release()
{
	pTex->Release();
	pEffectTex->Release();
}

void Enemy3::Spawn()
{
	bVisible = true;
	vPos.x = rand() % (SCREEN_WIDTH - rRect.right);
	vPos.y = -rRect.bottom;
	iHP = 3 * (OBJMAN()->stagephase + 1);
	switch (OBJMAN()->stagephase)
	{
	case 0:
		uiColor = 0xffffffff;
		break;
	case 1:
		uiColor = 0xffffff7f;
		break;
	}
	vDirectVec = { 0, 1 };
	iSpeed = 3 + rand() % 3;
	bLockOn = false;
}

void Enemy3::Move()
{
	if (bVisible || bEffectVisible)
	{
		vPos.x += vDirectVec.x * iSpeed;
		vPos.y += vDirectVec.y * iSpeed;
	}
}

void Enemy3::Animation()
{
	iAniTime++;
	if (bLockOn)
	{
		if (iAniTime >= 5)
		{
			iAniTime = 0;
			iAnii++;
			if (iAnii >= 11)
				iAnii = 3;
		}
	}
	else
	{
		if (iAniTime >= 5)
		{
			iAniTime = 0;
			iAnii++;
			if (iAnii >= 2)
				iAnii = 0;
		}
	}
}

void Enemy3::Collision()
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
	if (OBJMAN()->Collision(OBJMAN()->GetPlayerPos(), OBJMAN()->GetPlayerRect(), vPos, rRader)
		&& bVisible && !bLockOn)
		LockOn();

	//Guided
	for (int i = 0; i < 50; i++)
		if (OBJMAN()->Collision(OBJMAN()->GetPlayerBulletPos(i), OBJMAN()->GetPlayerBulletRect(), vPos, rGuided)
			&& bVisible && OBJMAN()->GetPlayerBulletVisible(i))
			OBJMAN()->PlayerGuidedMissile(i, vPos, rRect);
}

void Enemy3::Down()
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

void Enemy3::Hit(int iDmg)
{
	iHP -= iDmg;
	OBJMAN()->PlusScore(100);
}

void Enemy3::OutScreen()
{
	if (vPos.x <= -rRect.right || vPos.y <= -rRect.bottom ||
		vPos.x >= SCREEN_WIDTH || vPos.y >= SCREEN_HEIGHT)
		bVisible = false;
}

void Enemy3::Effect()
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

void Enemy3::LockOn()
{
	iSpeed *= 2;
	bLockOn = true;
	vDirectVec.x = (vPos.x + rRect.right / 2 - OBJMAN()->GetPlayerRect().right / 2) - OBJMAN()->GetPlayerPos().x;
	vDirectVec.y = (vPos.y + rRect.bottom / 2 - OBJMAN()->GetPlayerRect().bottom / 2) - OBJMAN()->GetPlayerPos().y;
	D3DXVec2Normalize(&vDirectVec, &vDirectVec);
	vDirectVec = -vDirectVec;
}

void Enemy3::Update()
{
	Move();
	Animation();
	Collision();
	Down();
	OutScreen();
	Effect();
}

void Enemy3::Render()
{
	if (bVisible)
		OBJMAN()->Draw(pTex, rAnimation[iAnii], vPos, uiColor);

	if (bEffectVisible)
		OBJMAN()->Draw(pEffectTex, rEffectRect[iEffectCount], vPos, 0xffffffff);
}
