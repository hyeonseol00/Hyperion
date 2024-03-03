#include "DXUT.h"
#include "stdafx.h"

FontManager FontManager::singleton;

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

void FontManager::Draw(int iSize, LPCWSTR pText, RECT rPos, UINT uiColor)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	switch (iSize)
	{
	case 40:
		pFont40->DrawTextW(pSprite, pText, -1, &rPos, DT_NOCLIP, uiColor);
		break;
	case 60:
		pFont60->DrawTextW(pSprite, pText, -1, &rPos, DT_NOCLIP, uiColor);
		break;
	}

	pSprite->End();
}

void FontManager::Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &pSprite);

	D3DXCreateFont(DXUTGetD3D9Device(), 40, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"FixedSys", &pFont40);
	D3DXCreateFont(DXUTGetD3D9Device(), 60, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"FixedSys", &pFont60);
}

void FontManager::Release()
{
	if (pSprite != NULL)
		pSprite->Release();

	if (pFont40 != NULL)
		pFont40->Release();
	if (pFont60 != NULL)
		pFont60->Release();
}
