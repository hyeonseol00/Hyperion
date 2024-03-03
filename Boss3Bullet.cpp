#include "DXUT.h"
#include "stdafx.h"

Boss3Bullet::Boss3Bullet()
{
	Init();
}

Boss3Bullet::~Boss3Bullet()
{
	Release();
}

void Boss3Bullet::Init()
{
	OBJMAN()->LoadData(L"Data/Boss3Bullet.png", 30, 30, &pTex);
	vPos = { 0, 0, 0 };
	rRect = { 0, 0, 30, 30 };

	vDirectVec = { 0, 0 };
	bVisible = false;
	iSpeed = 7;
}

void Boss3Bullet::Release()
{
	pTex->Release();
}

void Boss3Bullet::Fire(D3DXVECTOR3 vEnemyPos, RECT rEnemyRect, int iNum, float fMax)
{
	bVisible = true;
	vPos.x = vEnemyPos.x + rEnemyRect.right / 2 - rRect.right / 2;
	vPos.y = vEnemyPos.y + rEnemyRect.bottom / 2 - rRect.bottom / 2;

	vDirectVec.x = cos(2.0 * 3.14 * (iNum / fMax));
	vDirectVec.y = sin(2.0 * 3.14 * (iNum / fMax));
	D3DXVec2Normalize(&vDirectVec, &vDirectVec);
	vDirectVec = -vDirectVec;
}

void Boss3Bullet::Move()
{
	if (bVisible)
	{
		vPos.x += vDirectVec.x * iSpeed;
		vPos.y += vDirectVec.y * iSpeed;
	}
}

void Boss3Bullet::OutScreen()
{
	if ((vPos.x <= -rRect.right || vPos.x >= 1280 ||
		vPos.y <= -rRect.bottom || vPos.y >= 960)
		&& bVisible)
		bVisible = false;
}

void Boss3Bullet::Collision()
{
	if (OBJMAN()->Collision(OBJMAN()->GetPlayerPos(), OBJMAN()->GetPlayerHitBox(), vPos, rRect)
		&& bVisible)
	{
		bVisible = false;
		OBJMAN()->PlayerHit(1);
	}

	for (int i = 0; i < 50; i++)
	{
		if (OBJMAN()->Collision(OBJMAN()->GetPlayerBulletPos(i), OBJMAN()->GetPlayerBulletRect(), vPos, rRect)
			&& bVisible && OBJMAN()->GetPlayerBulletGuided(i) && OBJMAN()->GetPlayerBulletVisible(i))
		{
			bVisible = false;
			OBJMAN()->PlayerBulletHit(i);
		}
	}
}

void Boss3Bullet::Update()
{
	Move();
	OutScreen();
	Collision();
}

void Boss3Bullet::Render()
{
	if (bVisible)
		OBJMAN()->Draw(pTex, rRect, vPos, 0xffffffff);
}

