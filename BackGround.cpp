#include "DXUT.h"
#include "stdafx.h"

BackGround::BackGround()
{
	Init();
}

BackGround::~BackGround()
{
	Release();
}

void BackGround::Init()
{
	OBJMAN()->LoadData(L"Data\\BackGround1.png", SCREEN_WIDTH * 2, SCREEN_HEIGHT, &pTex);
	for (int i = 0; i < 2; i++)
	{
		vPos[i] = { 0, -(float)SCREEN_HEIGHT * i, 0 };
		rRect[i] = { i * SCREEN_WIDTH, 0, (i + 1) * SCREEN_WIDTH, SCREEN_HEIGHT };
	}

	OBJMAN()->LoadData(L"Data\\BackGround2.png", SCREEN_WIDTH * 2, SCREEN_HEIGHT, &pTex2);
	for (int i = 0; i < 2; i++)
		vPos2[i] = { 0, -(float)SCREEN_HEIGHT * i, 0 };

	OBJMAN()->LoadData(L"Data\\BackGround3.png", SCREEN_WIDTH * 2, SCREEN_HEIGHT, &pTex3);
	for (int i = 0; i < 2; i++)
		vPos3[i] = { 0, -(float)SCREEN_HEIGHT * i, 0 };

}

void BackGround::Release()
{
	pTex->Release();
	pTex2->Release();
	pTex3->Release();
}

void BackGround::Update()
{
	if (!OBJMAN()->GetBoss1Visible() && !OBJMAN()->GetBoss2Visible() &&
		!OBJMAN()->GetBoss3Visible() && !OBJMAN()->GetBoss4Visible())
	{
		for (int i = 0; i < 2; i++)
		{
			vPos[i].y += 2;
			vPos2[i].y += 4;
			vPos3[i].y += 8;

			if (vPos[i].y >= SCREEN_HEIGHT)
				vPos[i].y = -SCREEN_HEIGHT;
			if (vPos2[i].y >= SCREEN_HEIGHT)
				vPos2[i].y = -SCREEN_HEIGHT;
			if (vPos3[i].y >= SCREEN_HEIGHT)
				vPos3[i].y = -SCREEN_HEIGHT;
		}
	}
}

void BackGround::Render()
{
	for (int i = 0; i < 2; i++)
		OBJMAN()->Draw(pTex, rRect[OBJMAN()->stagestate], vPos[i], 0xffffffff);
	for (int i = 0; i < 2; i++)
		OBJMAN()->Draw(pTex2, rRect[OBJMAN()->stagestate], vPos2[i], 0xffffffff);
}

void BackGround::Render3()
{
	for (int i = 0; i < 2; i++)
		OBJMAN()->Draw(pTex3, rRect[OBJMAN()->stagestate], vPos3[i], 0xffffffff);
}
