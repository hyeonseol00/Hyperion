#pragma once
class FontManager
{
public:
	FontManager();
	~FontManager();
	static FontManager* Instance() { return &singleton; }
	void Draw(int iSize, LPCWSTR pText, RECT rPos, UINT uiColor);

	void Init();
	void Release();

private:
	static FontManager singleton;

	LPD3DXSPRITE pSprite;
	LPD3DXFONT pFont40;
	LPD3DXFONT pFont60;
};

#define FONMAN() FontManager::Instance()