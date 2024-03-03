#include "DXUT.h"
#include "stdafx.h"

Intro::Intro()
{
	Init();
}

Intro::~Intro()
{
	Release();
}

void Intro::Init()
{
	OBJMAN()->LoadData(L"Data\\Intro.png", 1280, 960, &pTex);

	iIntroTime = 0;
}

void Intro::Release()
{
	pTex->Release();
}

void Intro::Update()
{
	iIntroTime++;
	//if (iIntroTime >= 180)
		//GAAPP()->SetGameMode(GaApplication::MENU);

	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
		GAAPP()->SetGameMode(GaApplication::MENU);
}

void Intro::Render()
{
	OBJMAN()->Draw(pTex, { 0, 0, 1280, 960 }, { 0, 0, 0 }, 0xffffffff);
}
