#include "DXUT.h"
#include "stdafx.h"

Enemy2Bullet::Enemy2Bullet()
{
	Init();
}

Enemy2Bullet::~Enemy2Bullet()
{
	Release();
}

void Enemy2Bullet::Init()
{
	OBJMAN()->LoadData(L"Data\\Enemy2Bullet.png", 30, 30, &pTex);
	vPos = { 0, 0, 0 };
	vDirectVec = { 0, 0 };
	rRect = { 0, 0, 30, 30 };

	iSpeed = 4;
	bVisible = false;

	OBJMAN()->LoadData(L"Data\\Effect1.png", 420, 70, &pEffectTex);
	for (int i = 0; i < 6; i++)
		rEffectRect[i] = { i * 70, 0, (i + 1) * 70, 70 };
	iEffectTime = 0;
	iEffectCount = 0;
	bEffectVisible = false;
}

void Enemy2Bullet::Release()
{
	pTex->Release();
	pEffectTex->Release();
}

void Enemy2Bullet::Spawn(D3DXVECTOR3 vEnemyPos, RECT rEnemyRect)
{
	bVisible = true;
	vPos.x = vEnemyPos.x + rEnemyRect.right / 2 - rRect.right / 2;
	vPos.y = vEnemyPos.y + rEnemyRect.bottom / 2 - rRect.bottom / 2;
	vDirectVec.x = (vPos.x + rRect.right / 2 - OBJMAN()->GetPlayerRect().right / 2) - OBJMAN()->GetPlayerPos().x;
	vDirectVec.y = (vPos.y + rRect.bottom / 2 - OBJMAN()->GetPlayerRect().bottom / 2) - OBJMAN()->GetPlayerPos().y;
	D3DXVec2Normalize(&vDirectVec, &vDirectVec);
	vDirectVec = -vDirectVec;
}

void Enemy2Bullet::Move()
{
	if (bVisible)
	{
		vPos.x += vDirectVec.x * iSpeed;
		vPos.y += vDirectVec.y * iSpeed;
	}
}

void Enemy2Bullet::OutScreen()
{
	if (vPos.x <= -rRect.right || vPos.y <= -rRect.bottom ||
		vPos.x >= SCREEN_WIDTH || vPos.y >= SCREEN_HEIGHT)
		bVisible = false;
}

void Enemy2Bullet::Collision()
{
	if (OBJMAN()->Collision(OBJMAN()->GetPlayerPos(), OBJMAN()->GetPlayerHitBox(), vPos, rRect)
		&& bVisible)
	{
		Hit();
		OBJMAN()->PlayerHit(1);
	}

	for (int i = 0; i < 25; i++)
		if (OBJMAN()->Collision(OBJMAN()->GetPlayerBulletPos(i), OBJMAN()->GetPlayerBulletRect(), vPos, rRect)
			&& bVisible && OBJMAN()->GetPlayerBulletGuided(i) && OBJMAN()->GetPlayerBulletVisible(i))
		{
			Hit();
			OBJMAN()->PlayerBulletHit(i);
		}
}

void Enemy2Bullet::Hit()
{
	if (bVisible)
	{
		bVisible = false;
		bEffectVisible = true;
		iEffectTime = 0;
		iEffectCount = 0;
		vPos.x = vPos.x + rRect.right / 2 - rEffectRect[0].right / 2;
		vPos.y = vPos.y + rRect.bottom / 2 - rEffectRect[0].bottom / 2;
	}
}

void Enemy2Bullet::Effect()
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

void Enemy2Bullet::Update()
{
	Move();
	OutScreen();
	Effect();
	Collision();
}

void Enemy2Bullet::Render()
{
	if (bVisible)
		OBJMAN()->Draw(pTex, rRect, vPos, 0xffff0000);
	if (bEffectVisible)
		OBJMAN()->Draw(pEffectTex, rEffectRect[iEffectCount], vPos, 0xffffffff);
}
