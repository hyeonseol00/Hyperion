#include "DXUT.h"
#include "stdafx.h"

Player::Player()
{
	Init();
}

Player::~Player()
{
	Release();
}

void Player::Init()
{
	OBJMAN()->LoadData(L"Data\\Player.png", 160, 100, &pTex);
	rRect = { 0, 0, 40, 100 };
	rHitBox = { 11, 19, 29, 37 };
	vPos = { (float)SCREEN_WIDTH / 2 - rRect.right, 700, 0 };
	uiColor = 0xffffffff;

	iAS = 0;
	iUpgradeLevel = 0;
	iSpeed = 0;
	iSpeedLevel = 0;
	iHP = 3;
	iNuclearCount = 2;
	iAddonCount = 0;

	bPhoenix = false;
	iPhoenixTime = 0;
	bLeGenDPhoenix = false;

	bMove = false;
	for (int i = 0; i < 4; i++)
		rAnimation[i] = { i * rRect.right, 0, (i + 1) * rRect.right, rRect.bottom };
	iAniTime = 0;
	iAnii = 0;

	for (int i = 0; i < 50; i++)
		m_pPlayerBullet[i] = new PlayerBullet;
	iBulletTime = 0;
	iBulletCount = 0;

	bulletstate = STANDARD;

	for (int i = 0; i < 4; i++)
		m_aAddon[i] = new Addon;

	OBJMAN()->LoadData(L"Data\\Effect2.png", 5880, 980, &pEffectTex);
	for (int i = 0; i < 6; i++)
		rEffectRect[i] = { i * 980, 0, (i + 1) * 980, 980 };
	vEffectPos = { SCREEN_WIDTH / 2.0f - rEffectRect[0].right / 2, SCREEN_HEIGHT / 2.0f - rEffectRect[0].bottom / 2, 0 };
	iEffectTime = 0;
	iEffectCount = 0;
	bEffectVisible = false;
}

void Player::Release()
{
	pTex->Release();
	pEffectTex->Release();

	for (int i = 0; i < 50; i++)
		m_pPlayerBullet[i]->Release();

	for (int i = 0; i < 4; i++)
		m_aAddon[i]->Release();
}

void Player::KeyState()
{
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
		iSpeed = 3;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		vPos.x -= iSpeed;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		vPos.y -= iSpeed;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		vPos.x += iSpeed;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		vPos.y += iSpeed;

	bMove = false;
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_UP) ||
		GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_DOWN))
		bMove = true;

	iBulletTime++;
	if (GetAsyncKeyState(VK_LCONTROL) & 0x8000)
	{
		FireBullet();
		for (int i = 0; i < iAddonCount; i++)
			m_aAddon[i]->Fire();
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
		Nuclear();

	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
		GAAPP()->SetGameMode(GaApplication::PAUSE);

	//		CHEAT KEY		//
	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		if (bLeGenDPhoenix)
			bLeGenDPhoenix = false;
		else
			bLeGenDPhoenix = true;
	}
	if (GetAsyncKeyState(VK_F2) & 0x0001)
	{
		if (iUpgradeLevel < 7)
			iUpgradeLevel++;
		bulletstate = TRIPLE;
	}
	if (GetAsyncKeyState(VK_F3) & 0x0001)
	{
		if (iUpgradeLevel < 7)
			iUpgradeLevel++;
		bulletstate = GUIDED;
	}
}

void Player::MoveLimit()
{
	if (vPos.x < 0)
		vPos.x = 0;
	if (vPos.y < 0)
		vPos.y = 0;
	if (vPos.x >= SCREEN_WIDTH - rRect.right)
		vPos.x = SCREEN_WIDTH - rRect.right;
	if (vPos.y >= SCREEN_HEIGHT - rRect.bottom)
		vPos.y = SCREEN_HEIGHT - rRect.bottom;
}

void Player::Animation()
{
	if (bMove)
	{
		iAniTime++;
		if (iAniTime >= 10)
		{
			iAniTime = 0;
			iAnii++;
			if (iAnii >= 4)
				iAnii = 0;
		}
	}
	else
		iAnii = 0;
}

void Player::FireBullet()
{
	if (iBulletTime >= iAS)
	{
		iBulletTime = 0;
		switch (bulletstate)
		{
		case Player::TRIPLE:
			m_pPlayerBullet[iBulletCount]->Spawn(vPos, rRect, 0, false);
			iBulletCount++;
			if (iBulletCount >= 50)
				iBulletCount = 0;
			m_pPlayerBullet[iBulletCount]->Spawn(vPos, rRect, 2, false);
			iBulletCount++;
			if (iBulletCount >= 50)
				iBulletCount = 0;
		case Player::STANDARD:
			m_pPlayerBullet[iBulletCount]->Spawn(vPos, rRect, 1, false);
			iBulletCount++;
			if (iBulletCount >= 50)
				iBulletCount = 0;
			break;
		case Player::GUIDED:
			m_pPlayerBullet[iBulletCount]->Spawn(vPos, rRect, 1, true);
			iBulletCount++;
			if (iBulletCount >= 50)
				iBulletCount = 0;
			break;
		}
	}
}

void Player::Down()
{
	if (iHP <= 0)
		GAAPP()->SetGameMode(GaApplication::GAMEOVER);
}

void Player::Stats()
{
	iAS = 30 - iUpgradeLevel * 3;
	iSpeed = 4 + iSpeedLevel;

	for (int i = 0; i < iAddonCount; i++)
		m_aAddon[i]->Spawn(vPos, rRect, i, bMove);

	iPhoenixTime--;
	if (iPhoenixTime <= 0)
		bPhoenix = false;
	uiColor = 0xffffffff;
	if (bPhoenix)
		uiColor = 0xffff3f3f;
	if (bLeGenDPhoenix)
		uiColor = 0x7fffffff;
}

void Player::Nuclear()
{
	if (iNuclearCount > 0)
	{
		iNuclearCount--;
		bEffectVisible = true;
		iEffectTime = 0;
		iEffectCount = 0;

		for (int i = 0; i < 25; i++)
		{
			OBJMAN()->Enemy1Crash(i);
			OBJMAN()->Enemy2Crash(i);
			OBJMAN()->Enemy3Crash(i);
			OBJMAN()->Enemy4Crash(i);
			for (int j = 0; j < 10; j++)
				OBJMAN()->Enemy2BulletHit(i, j);
			for (int j = 0; j < 2; j++)
				OBJMAN()->Enemy4DivisionCrash(i, j);
		}
		OBJMAN()->Boss1Hit(50);
		for (int i = 0; i < 16; i++)
			OBJMAN()->Boss1BulletHit(i);
		OBJMAN()->Boss2Hit(50);
		for (int i = 0; i < 24; i++)
			OBJMAN()->Boss2BulletHit(i);
		OBJMAN()->Boss3Hit(50);
		for (int i = 0; i < 32; i++)
			OBJMAN()->Boss3BulletHit(i);
		OBJMAN()->Boss4Hit(50);
		for (int i = 0; i < 40; i++)
			OBJMAN()->Boss4BulletHit(i);
	}
}

void Player::CatchItem(int iVaule)
{
	switch (iVaule)
	{
	case 0:
		if (iAddonCount < 4)
			iAddonCount++;
		break;
	case 1:
		if (iNuclearCount < 5)
			iNuclearCount++;
		break;
	case 2:
		bulletstate = TRIPLE;
		break;
	case 3:
		bulletstate = GUIDED;
		break;
	case 4:
		if (iSpeedLevel < 5)
			iSpeedLevel++;
		break;
	case 5:
		if (iUpgradeLevel < 7)
			iUpgradeLevel++;
		break;
	case 6:
		if (iHP < 10)
			iHP++;
		break;
	}
	OBJMAN()->PlusScore(250);
	SNDMAN()->PlayItem();
}

void Player::Effect()
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

void Player::Hit(int iDmg)
{
	if (!bPhoenix && !bLeGenDPhoenix)
	{
		iHP -= iDmg;
		bPhoenix = true;
		iPhoenixTime = 90;
		if (iUpgradeLevel > 0)
			iUpgradeLevel--;
		if (iSpeedLevel > 0)
			iSpeedLevel--;
		if (iAddonCount > 0)
			iAddonCount--;
		bulletstate = STANDARD;
		SNDMAN()->PlayBoom2();
	}
}

void Player::Update()
{
	KeyState();
	MoveLimit();
	Animation();
	Down();
	for (int i = 0; i < 4; i++)
		m_aAddon[i]->Update();
	Stats();
	Effect();

	for (int i = 0; i < 50; i++)
		m_pPlayerBullet[i]->Update();
}

void Player::Render()
{
	for (int i = 0; i < 50; i++)
		m_pPlayerBullet[i]->Render();

	for (int i = 0; i < 4; i++)
		m_aAddon[i]->Render();

	OBJMAN()->Draw(pTex, rAnimation[iAnii], vPos, uiColor);

	if (bEffectVisible)
		OBJMAN()->Draw(pEffectTex, rEffectRect[iEffectCount], vEffectPos, 0xffffffff);
}
