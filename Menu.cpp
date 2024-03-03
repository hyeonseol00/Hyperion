#include "DXUT.h"
#include "stdafx.h"

Menu::Menu()
{
	Init();
}

Menu::~Menu()
{
	Release();
}

void Menu::Init()
{
	OBJMAN()->LoadData(L"Data\\Menu.png", SCREEN_WIDTH * 5, SCREEN_HEIGHT, &pTex);
	for (int i = 0; i < 5; i++)
		rRect[i] = { i * SCREEN_WIDTH, 0, (i + 1) * SCREEN_WIDTH, SCREEN_HEIGHT };

	OBJMAN()->LoadData(L"Data\\MenuButton.png", 400, 700, &pButtonTex);
	for (int i = 0; i < 7; i++)
	{
		rButRect[i] = { 0, i * 100, 400, (i + 1) * 100 };
		vButPos[i] = { SCREEN_WIDTH - rButRect[0].right - 25.0f, 25.0f + i * (rButRect[0].bottom + 25), 0 };
		uiButColor[i] = 0xffffffff;
	}
	menustate = MAIN;
	iClickState = 0;

	for (int i = 0; i < 3; i++)
		pInitial[i] = 'A';
	pInitial[3] = NULL;
	iInitialCount = 0;
}

void Menu::Release()
{
	pTex->Release();
	pButtonTex->Release();
}

void Menu::MouseState(bool bM1Down, int x, int y)
{
	for (int i = 0; i < 7; i++)
		uiButColor[i] = 0xffffffff;

	switch (iClickState)
	{
	case 1:
		GAAPP()->SetGameMode(GaApplication::STAGE1);
		OBJMAN()->stagestate = ObjectManager::STAGE1;
		SNDMAN()->PlayBGM();
		break;
	case 2:
		menustate = HOWTO;
		break;
	case 3:
		menustate = STORY;
		break;
	case 4:
		menustate = RANKING;
		break;
	case 5:
		menustate = CREDIT;
		break;
	case 6:
		PostQuitMessage(0);
		break;
	case 7:
		menustate = MAIN;
		break;
	}
	iClickState = 0;

	switch (menustate)
	{
	case Menu::MAIN:
		for (int i = 0; i < 6; i++)
			if (OBJMAN()->Collision(vButPos[i], rButRect[0], { (float)x, (float)y, 0 }, { 0, 0, 0, 0 }) && bM1Down)
			{
				uiButColor[i] = 0xff7f7f7f;
				iClickState = i + 1;
			}
		break;
	case Menu::HOWTO:
	case Menu::STORY:
	case Menu::RANKING:
	case Menu::CREDIT:
		if (OBJMAN()->Collision(vButPos[6], rButRect[0], { (float)x, (float)y, 0 }, { 0, 0, 0, 0 }) && bM1Down)
		{
			uiButColor[6] = 0xff7f7f7f;
			iClickState = 7;
		}
		break;
	}
}

void Menu::InputInitial()
{
	if (GetAsyncKeyState('Q') & 0x0001) {
		pInitial[iInitialCount] = 'Q';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('W') & 0x0001) {
		pInitial[iInitialCount] = 'W';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('E') & 0x0001) {
		pInitial[iInitialCount] = 'E';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('R') & 0x0001) {
		pInitial[iInitialCount] = 'R';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('T') & 0x0001) {
		pInitial[iInitialCount] = 'T';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('Y') & 0x0001) {
		pInitial[iInitialCount] = 'Y';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('U') & 0x0001) {
		pInitial[iInitialCount] = 'U';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('I') & 0x0001) {
		pInitial[iInitialCount] = 'I';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('O') & 0x0001) {
		pInitial[iInitialCount] = 'O';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('P') & 0x0001) {
		pInitial[iInitialCount] = 'P';
		iInitialCount++;
	}


	else if (GetAsyncKeyState('A') & 0x0001) {
		pInitial[iInitialCount] = 'A';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('S') & 0x0001) {
		pInitial[iInitialCount] = 'S';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('D') & 0x0001) {
		pInitial[iInitialCount] = 'D';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('F') & 0x0001) {
		pInitial[iInitialCount] = 'F';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('G') & 0x0001) {
		pInitial[iInitialCount] = 'G';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('H') & 0x0001) {
		pInitial[iInitialCount] = 'H';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('J') & 0x0001) {
		pInitial[iInitialCount] = 'J';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('K') & 0x0001) {
		pInitial[iInitialCount] = 'K';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('L') & 0x0001) {
		pInitial[iInitialCount] = 'L';
		iInitialCount++;
	}


	else if (GetAsyncKeyState('Z') & 0x0001) {
		pInitial[iInitialCount] = 'Z';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('X') & 0x0001) {
		pInitial[iInitialCount] = 'X';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('C') & 0x0001) {
		pInitial[iInitialCount] = 'C';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('V') & 0x0001) {
		pInitial[iInitialCount] = 'V';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('B') & 0x0001) {
		pInitial[iInitialCount] = 'B';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('N') & 0x0001) {
		pInitial[iInitialCount] = 'N';
		iInitialCount++;
	}
	else if (GetAsyncKeyState('M') & 0x0001) {
		pInitial[iInitialCount] = 'M';
		iInitialCount++;
	}

	if (iInitialCount > 2)
		iInitialCount = 0;
}

void Menu::Update()
{
}

void Menu::Render()
{
	OBJMAN()->Draw(pTex, rRect[menustate], { 0, 0, 0 }, 0xffffffff);

	switch (menustate)
	{
	case Menu::MAIN:
		for (int i = 0; i < 6; i++)
			OBJMAN()->Draw(pButtonTex, rButRect[i], vButPos[i], uiButColor[i]);
		break;
	case Menu::HOWTO:
	case Menu::STORY:
	case Menu::RANKING:
	case Menu::CREDIT:
		OBJMAN()->Draw(pButtonTex, rButRect[6], vButPos[6], uiButColor[6]);
		break;
	}
	switch (menustate)
	{
	case Menu::RANKING:
		wchar_t buf[256];
		wsprintf(buf, L"1st. %s : %d", GAAPP()->GetRankInitial(0), GAAPP()->GetRankScore(0));
		FONMAN()->Draw(60, buf, { 400, 300 }, 0xffffffff);
		wsprintf(buf, L"2nd. %s : %d", GAAPP()->GetRankInitial(1), GAAPP()->GetRankScore(1));
		FONMAN()->Draw(60, buf, { 400, 400 }, 0xffffffff);
		wsprintf(buf, L"3rd. %s : %d", GAAPP()->GetRankInitial(2), GAAPP()->GetRankScore(2));
		FONMAN()->Draw(60, buf, { 400, 500 }, 0xffffffff);
		break;
	}
}
