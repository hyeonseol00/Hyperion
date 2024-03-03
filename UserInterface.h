#pragma once
class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void Init();
	void Release();
	void Update();
	void Render();

private:
	LPDIRECT3DTEXTURE9 pCountIconTex;
	RECT rCountIconRect[2];

	LPDIRECT3DTEXTURE9 pIconTex;
	D3DXVECTOR3 vIconPos[4];
	RECT rIconRect[4];

	LPDIRECT3DTEXTURE9 pSITex;
	RECT rSIRect[6];
	UINT uiStageIntroColor;
	UINT uiStageClearColor;
};

