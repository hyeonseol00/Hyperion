#pragma once
class BackGround
{
public:
	BackGround();
	~BackGround();

	void Init();
	void Release();
	void Update();
	void Render();
	void Render3();

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos[2];
	RECT rRect[2];
	
	LPDIRECT3DTEXTURE9 pTex2;
	D3DXVECTOR3 vPos2[2];

	LPDIRECT3DTEXTURE9 pTex3;
	D3DXVECTOR3 vPos3[2];
};

