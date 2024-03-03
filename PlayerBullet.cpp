#include "DXUT.h"
#include "stdafx.h"

PlayerBullet::PlayerBullet()
{
	Init();
}

PlayerBullet::~PlayerBullet()
{
	Release();
}

void PlayerBullet::Init()
{
	OBJMAN()->LoadData(L"Data\\PlayerBullet.png", 90, 50, &pTex);
	vPos = { 0, 0, 0 };
	vDirectVec = { 0, 1 };
	rRect = { 0, 0, 30, 50 };
	bVisible = false;

	fSpeed = -5.0f;

	for (int i = 0; i < 3; i++)
		rDirection[i] = { i * rRect.right, 0, (i + 1) * rRect.right, rRect.bottom };
	iDirection = 1;
	bGuided = false;

	OBJMAN()->LoadData(L"Data\\Effect2.png", 420, 70, &pEffectTex);
	for (int i = 0; i < 6; i++)
		rEffectRect[i] = { i * 70, 0, (i + 1) * 70, 70 };
	iEffectTime = 0;
	iEffectCount = 0;
	bEffectVisible = false;
}

void PlayerBullet::Release()
{
	pTex->Release();
	pEffectTex->Release();
}

void PlayerBullet::Spawn(D3DXVECTOR3 vPlayerPos, RECT rPlayerRect, int iDirection, bool bGuided)
{
	bVisible = true;
	vPos.x = vPlayerPos.x + rPlayerRect.right / 2 - rRect.right / 2;
	vPos.y = vPlayerPos.y + rPlayerRect.bottom / 2 - rRect.bottom / 2;

	switch (iDirection)
	{
	case 0:
		vDirectVec = { 0.2f, 1 };
		break;
	case 1:
		vDirectVec = { 0, 1 };
		break;
	case 2:
		vDirectVec = { -0.2f, 1 };
		break;
	}
	fSpeed = -5.0f;
	this->iDirection = iDirection;
	this->bGuided = bGuided;
}

void PlayerBullet::Move()
{
	if (bVisible)
	{
		fSpeed += 0.5f;
		vPos.x -= vDirectVec.x * fSpeed;
		vPos.y -= vDirectVec.y * fSpeed;
	}
}

void PlayerBullet::OutScreen()
{
	if (vPos.x <= -rRect.right || vPos.y <= -rRect.bottom ||
		vPos.x >= SCREEN_WIDTH || vPos.y >= SCREEN_HEIGHT)
		bVisible = false;
}

void PlayerBullet::GuidedMissile(D3DXVECTOR3 vEnemyPos, RECT vEnemyRect)
{
	if (bGuided)
	{
		fSpeed += 2.5f;
		vDirectVec.x = (vPos.x + rRect.right / 2 - vEnemyRect.right / 2) - vEnemyPos.x;
		vDirectVec.y = (vPos.y + rRect.bottom / 2 - vEnemyRect.bottom / 2) - vEnemyPos.y;
		D3DXVec2Normalize(&vDirectVec, &vDirectVec);
	}
}

void PlayerBullet::Effect()
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

void PlayerBullet::Hit()
{
	bVisible = false;
	bEffectVisible = true;
	iEffectTime = 0;
	iEffectCount = 0;
	vPos.x = vPos.x + rRect.right / 2 - rEffectRect[0].right / 2;
	vPos.y = vPos.y + rRect.bottom / 2 - rEffectRect[0].bottom / 2;
}

void PlayerBullet::Update()
{
	Move();
	OutScreen();
	Effect();
}

void PlayerBullet::Render()
{
	if (bVisible)
		OBJMAN()->Draw(pTex, rDirection[iDirection], vPos, 0xffffffff);
	if (bEffectVisible)
		OBJMAN()->Draw(pEffectTex, rEffectRect[iEffectCount], vPos, 0xffffffff);
}
