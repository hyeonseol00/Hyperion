#include "DXUT.h"
#include "stdafx.h"

Boss2::Boss2()
{
	Init();
}

Boss2::~Boss2()
{
	Release();
}

void Boss2::Init()
{
	OBJMAN()->LoadData(L"Data\\Boss2.png", 520, 260, &pTex);
	vPos = { 0, 0, 0 };
	rRect = { 0, 0, 260, 260 };

	bVisible = false;
	bDeath = false;
	iSpeed = 2;
	iHP = 150;

	for (int i = 0; i < 24; i++)
		m_bBoss2Bullet[i] = new Boss2Bullet;
	iBulletTime = 0;

	rGuided = { rRect.left - 200, rRect.top - 200, rRect.right + 200, rRect.bottom + 200 };

	for (int i = 0; i < 2; i++)
		rAnimation[i] = { i * rRect.right, 0, (i + 1) * rRect.right, rRect.bottom };
	iAniTime = 0;
	iAnii = 0;

	OBJMAN()->LoadData(L"Data\\Effect1.png", 2520, 420, &pEffectTex);
	for (int i = 0; i < 6; i++)
		rEffectRect[i] = { i * 420, 0, (i + 1) * 420, 420 };
	iEffectTime = 0;
	iEffecti = 0;
	bEffectVisible = false;
}

void Boss2::Release()
{
	pTex->Release();
	pEffectTex->Release();

	for (int i = 0; i < 24; i++)
		m_bBoss2Bullet[i]->Release();
}

void Boss2::Spawn()
{
	if (OBJMAN()->GetScore() >= 40000 && !bVisible && !bDeath)
	{
		bVisible = true;
		vPos = { 1280.0f / 2 - rRect.right / 2, -(float)rRect.bottom, 0 };
	}
}

void Boss2::Move()
{
	if (bVisible)
		vPos.y += iSpeed;
	if (vPos.y >= 100)
		iSpeed = 0;
}

void Boss2::Collision()
{
	if (OBJMAN()->Collision(OBJMAN()->GetPlayerPos(), OBJMAN()->GetPlayerHitBox(), vPos, rRect)
		&& bVisible)
	{
		OBJMAN()->PlayerHit(1);
	}

	for (int i = 0; i < 50; i++)
		if (OBJMAN()->Collision(OBJMAN()->GetPlayerBulletPos(i), OBJMAN()->GetPlayerBulletRect(), vPos, rRect)
			&& bVisible && OBJMAN()->GetPlayerBulletVisible(i))
		{
			Hit(1);
			OBJMAN()->PlayerBulletHit(i);
		}

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
		{
			OBJMAN()->PlayerGuidedMissile(i, vPos, rRect);
		}
}

void Boss2::Down()
{
	if (iHP <= 0 && bVisible)
	{
		bVisible = false;
		bDeath = true;

		bEffectVisible = true;
		iEffecti = 0;
		vPos.x = vPos.x + rRect.right / 2 - rEffectRect[0].right / 2;
		vPos.y = vPos.y + rRect.bottom / 2 - rEffectRect[0].bottom / 2;
		SNDMAN()->PlayBoom();
	}
}

void Boss2::Fire()
{
	if (bVisible)
	{
		iBulletTime++;
		if (iBulletTime >= 240)
		{
			iBulletTime = 0;
			for (int i = 0; i < 24; i++)
				m_bBoss2Bullet[i]->Fire(vPos, rRect, i, 24);
		}
	}
}

void Boss2::Animation()
{
	iAniTime++;
	if (iAniTime >= 10)
	{
		iAniTime = 0;
		iAnii++;
		if (iAnii >= 2)
			iAnii = 0;
	}
}

void Boss2::Effect()
{
	if (bEffectVisible)
	{
		iEffectTime++;
		if (iEffectTime >= 7)
		{
			iEffectTime = 0;
			iEffecti++;
			if (iEffecti >= 6)
			{
				iEffecti = 0;
				bEffectVisible = false;
			}
		}
	}
}

void Boss2::Hit(int iDmg)
{
	if (bVisible)
	{
		iHP -= iDmg;
		OBJMAN()->PlusScore(50);
	}
}

void Boss2::Update()
{
	Spawn();
	Move();
	Collision();
	Down();
	Fire();
	Animation();
	Effect();

	for (int i = 0; i < 24; i++)
		m_bBoss2Bullet[i]->Update();
}

void Boss2::Render()
{
	if (bVisible)
		OBJMAN()->Draw(pTex, rAnimation[iAnii], vPos, 0xffffffff);

	for (int i = 0; i < 24; i++)
		m_bBoss2Bullet[i]->Render();

	if (bEffectVisible)
		OBJMAN()->Draw(pEffectTex, rEffectRect[iEffecti], vPos, 0xffffffff);
}
