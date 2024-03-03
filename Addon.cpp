#include "DXUT.h"
#include "stdafx.h"

Addon::Addon()
{
	Init();
}

Addon::~Addon()
{
	Release();
}

void Addon::Init()
{
	OBJMAN()->LoadData(L"Data\\Addon.png", 120, 80, &pTex);
	vPos = { 0, 0, 0 };
	rRect = { 0, 0, 30, 80 };

	for (int i = 0; i < 4; i++)
		rAnimation[i] = { i * rRect.right, 0, (i + 1) * rRect.right, rRect.bottom };
	iAniTime = 0;
	iAnii = 0;
	bMove = false;

	bVisible = false;

	for (int i = 0; i < 25; i++)
		m_pAddonBullet[i] = new PlayerBullet;
	iFireTime = 0;
	iBulletCount = 0;
}

void Addon::Release()
{
	pTex->Release();

	for (int i = 0; i < 25; i++)
		m_pAddonBullet[i]->Release();
}

void Addon::Spawn(D3DXVECTOR3 vPlayerPos, RECT rPlayerRect, int iDirection, bool bMove)
{
	bVisible = true;
	switch (iDirection)
	{
	case 0:
		vPos.x = vPlayerPos.x - rRect.right;
		vPos.y = vPlayerPos.y + 25;
		break;
	case 1:
		vPos.x = vPlayerPos.x + rPlayerRect.right;
		vPos.y = vPlayerPos.y + 25;
		break;
	case 2:
		vPos.x = vPlayerPos.x - rRect.right * 2;
		vPos.y = vPlayerPos.y + 50;
		break;
	case 3:
		vPos.x = vPlayerPos.x + rPlayerRect.right + rRect.right;
		vPos.y = vPlayerPos.y + 50;
		break;
	}
}

void Addon::Fire()
{
	iFireTime++;
	if (iFireTime >= 40)
	{
		iFireTime = 0;
		m_pAddonBullet[iBulletCount]->Spawn(vPos, rRect, 1, false);
		iBulletCount++;
		if (iBulletCount >= 25)
			iBulletCount = 0;
	}
}

void Addon::Update()
{
	bVisible = false;

	for (int i = 0; i < 25; i++)
		m_pAddonBullet[i]->Update();
}

void Addon::Render()
{
	for (int i = 0; i < 25; i++)
		m_pAddonBullet[i]->Render();

	if (bVisible)
		OBJMAN()->Draw(pTex, rAnimation[iAnii], vPos, 0xffffffff);
}
