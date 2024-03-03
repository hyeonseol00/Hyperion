#pragma once
class Obstacle
{
public:
	Obstacle();
	~Obstacle();

	void Init();
	void Release();
	void Update();
	void Render();

	void Spawn();
	void Move();
	void Collision();
	void OutScreen();

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos;
	RECT rRect;
	RECT rType[2];
	bool bVisible;

	int iSpeed;
	int iType;
};

