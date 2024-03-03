#include "DXUT.h"
#include "stdafx.h"

Item::Item()
{
	Init();
}

Item::~Item()
{
	Release();
}

void Item::Init()
{
	OBJMAN()->LoadData(L"Data\\Item.png", 322, 46, &pTex);
	vPos = { 0, 0, 0 };
	rRect = { 0, 0, 46, 46 };
	for (int i = 0; i < 7; i++)
		rItemValue[i] = { i * rRect.right, 0, (i + 1) * rRect.right, rRect.bottom };

	bVisible = false;

	itemvalue = ADDON;

	iSpeed = 3;
}

void Item::Release()
{
	pTex->Release();
}

void Item::Spawn()
{
	bVisible = true;
	itemvalue = (ItemValue)(rand() % 7);
	vPos.x = rand() % (SCREEN_WIDTH - rRect.right);
	vPos.y = -rRect.bottom;
}

void Item::Move()
{
	if (bVisible)
		vPos.y += iSpeed;
}

void Item::Collision()
{
	if (OBJMAN()->Collision(OBJMAN()->GetPlayerPos(), OBJMAN()->GetPlayerRect(), vPos, rRect)
		&& bVisible)
	{
		bVisible = false;
		OBJMAN()->CatchItem(itemvalue);
	}
}

void Item::Update()
{
	Move();
	Collision();
}

void Item::Render()
{
	if (bVisible)
		OBJMAN()->Draw(pTex, rItemValue[itemvalue], vPos, 0xffffffff);
}
