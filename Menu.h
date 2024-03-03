#pragma once
class Menu
{
public:
	Menu();
	~Menu();
	enum MenuState { MAIN, HOWTO, STORY, RANKING, CREDIT };

	void Init();
	void Release();
	void Update();
	void Render();

	void MouseState(bool bM1Down, int x, int y);

private:
	LPDIRECT3DTEXTURE9 pTex;
	RECT rRect[5];

	LPDIRECT3DTEXTURE9 pButtonTex;
	D3DXVECTOR3 vButPos[7];
	RECT rButRect[7];
	UINT uiButColor[7];

	MenuState menustate;
	int iClickState;

	wchar_t pInitial[4];
	int iInitialCount;

public:
	void InputInitial();
	LPCWSTR GetInitial() { return pInitial; }
};

