#include "DXUT.h"
#include "stdafx.h"

Obstacle::Obstacle()
{
	Init();
}

Obstacle::~Obstacle()
{
	Release();
}

void Obstacle::Init()
{
	OBJMAN()->LoadData(L"Data\\Obstacle.png", 200, 100, &pTex);
	vPos = { 0, 0, 0 };
	rRect = { 0, 0, 100, 100 };
	for (int i = 0; i < 2; i++)
		rType[i] = { i * 100, 0, (i + 1) * 100, 100 };
	bVisible = false;

	iSpeed = 4;
}

void Obstacle::Release()
{
	pTex->Release();
}

void Obstacle::Spawn()
{
	bVisible = true;
	vPos.x = rand() % (SCREEN_WIDTH - rRect.right);
	vPos.y = -rRect.bottom;
	iType = rand() % 2;
}

void Obstacle::Move()
{
	if (bVisible)
		vPos.y += iSpeed;
}

void Obstacle::Collision()
{
	if (OBJMAN()->Collision(OBJMAN()->GetPlayerPos(), OBJMAN()->GetPlayerHitBox(), vPos, rRect)
		&& bVisible)
		switch (iType)
		{
		case 0:
			OBJMAN()->PlayerHit(1);
			break;
		case 1:
			OBJMAN()->PlayerSlow();
			break;
		}
}

void Obstacle::OutScreen()
{
	if (vPos.x <= -rRect.right || vPos.y <= -rRect.bottom ||
		vPos.x >= SCREEN_WIDTH || vPos.y >= SCREEN_HEIGHT)
		bVisible = false;
}

void Obstacle::Update()
{
	Move();
	Collision();
	OutScreen();
}

void Obstacle::Render()
{
	if (bVisible)
		OBJMAN()->Draw(pTex, rType[iType], vPos, 0xffffffff);
}
