#include "DXUT.h"
#include "stdafx.h"

UserInterface::UserInterface()
{
	Init();
}

UserInterface::~UserInterface()
{
	Release();
}

void UserInterface::Init()
{
	OBJMAN()->LoadData(L"Data\\CountIcon.png", 80, 40, &pCountIconTex);
	for (int i = 0; i < 2; i++)
		rCountIconRect[i] = { i * 40, 0, (i + 1) * 40, 40 };

	OBJMAN()->LoadData(L"Data\\Icon.png", 184, 46, &pIconTex);
	for (int i = 0; i < 4; i++)
	{
		vIconPos[i] = { 1125, 750.0f + i * 46, 0 };
		rIconRect[i] = { i * 46, 0, (i + 1) * 46, 46 };
	}

	OBJMAN()->LoadData(L"Data\\ScreenInterface.png", 7680, 960, &pSITex);
	for (int i = 0; i < 6; i++)
		rSIRect[i] = { i * 1280, 0, (i + 1) * 1280, 960 };
	uiStageIntroColor = 0xffffffff;
	uiStageClearColor = 0x00ffffff;
}

void UserInterface::Release()
{
	pCountIconTex->Release();
	pIconTex->Release();
	pSITex->Release();
}

void UserInterface::Update()
{
	if (uiStageIntroColor > 0x00ffffff)
		uiStageIntroColor -= 0x01000000;

	if (OBJMAN()->GetBoss2Death() && GAAPP()->GetGameMode() == GaApplication::STAGE1)
	{
		uiStageClearColor += 0x01000000;
		OBJMAN()->SetPlayerPhoenix();
	}
	if (OBJMAN()->GetBoss2Death() && GAAPP()->GetGameMode() == GaApplication::STAGE1 && uiStageClearColor >= 0xffffffff)
	{
		OBJMAN()->StageRelease();
		OBJMAN()->StageInit();
		OBJMAN()->stagestate = ObjectManager::STAGE2;
		GAAPP()->SetGameMode(GaApplication::STAGE2);
		OBJMAN()->SetPlayerPhoenixOff();
	}

	if (OBJMAN()->GetBoss4Death() && GAAPP()->GetGameMode() == GaApplication::STAGE2)
	{
		uiStageClearColor += 0x01000000;
		OBJMAN()->SetPlayerPhoenix();
	}
	if (OBJMAN()->GetBoss4Death() && GAAPP()->GetGameMode() == GaApplication::STAGE2 && uiStageClearColor >= 0xffffffff)
		GAAPP()->SetGameMode(GaApplication::ENDING);
}

void UserInterface::Render()
{
	wchar_t buf[256];

	switch (OBJMAN()->GetBulletState())
	{
	case 1:
		OBJMAN()->Draw(pIconTex, rIconRect[0], vIconPos[1], 0xffffffff);
		break;
	case 2:
		OBJMAN()->Draw(pIconTex, rIconRect[1], vIconPos[1], 0xffffffff);
		break;
	}
	for (int i = 2; i < 4; i++)
		OBJMAN()->Draw(pIconTex, rIconRect[i], vIconPos[i], 0xffffffff);
	wsprintf(buf, L"x%d", OBJMAN()->GetSpeedLevel());
	FONMAN()->Draw(60, buf, { (LONG)vIconPos[2].x + 46, (LONG)vIconPos[2].y - 10 }, 0xff7f7fff);
	wsprintf(buf, L"x%d", OBJMAN()->GetUpgradeLevel());
	FONMAN()->Draw(60, buf, { (LONG)vIconPos[3].x + 46, (LONG)vIconPos[3].y - 10 }, 0xffffff7f);

	for (int i = 0; i < OBJMAN()->GetPlayerHP(); i++)
		OBJMAN()->Draw(pCountIconTex, rCountIconRect[1], { 25, i * (40.0f + 25) + 25, 0 }, 0xffffffff);
	for (int i = 0; i < OBJMAN()->GetNuclearCount(); i++)
		OBJMAN()->Draw(pCountIconTex, rCountIconRect[0], { 1215, i * (40.0f + 25) + 25, 0 }, 0xffffffff);

	OBJMAN()->Draw(pSITex, rSIRect[2], { 0, 0, 0 }, uiStageClearColor);

	switch (GAAPP()->GetGameMode())
	{
	case GaApplication::STAGE1:
		OBJMAN()->Draw(pSITex, rSIRect[0], { 0, 0, 0 }, uiStageIntroColor);
		break;
	case GaApplication::STAGE2:
		OBJMAN()->Draw(pSITex, rSIRect[1], { 0, 0, 0 }, uiStageIntroColor);
		break;
	case GaApplication::PAUSE:
		OBJMAN()->Draw(pSITex, rSIRect[3], { 0, 0, 0 }, 0xbdffffff);
		break;
	case GaApplication::GAMEOVER:
		OBJMAN()->Draw(pSITex, rSIRect[4], { 0, 0, 0 }, 0xbdffffff);
		break;
	case GaApplication::ENDING:
		OBJMAN()->Draw(pSITex, rSIRect[5], { 0, 0, 0 }, 0xffffffff);
		break;
	}

	switch (GAAPP()->GetGameMode())
	{
	case GaApplication::PAUSE:
	case GaApplication::GAMEOVER:
	case GaApplication::ENDING:
		wsprintf(buf, L"InputInitial : %s", OBJMAN()->GetInitial());
		FONMAN()->Draw(60, buf, { 0, 0 }, 0xffffffff);
		break;
	}

	wsprintf(buf, L"SCORE : %d", OBJMAN()->GetScore());
	FONMAN()->Draw(60, buf, { 0, 900 }, 0xffffffff);
}