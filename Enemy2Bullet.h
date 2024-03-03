#pragma once
class Enemy2Bullet
{
public:
	Enemy2Bullet();
	~Enemy2Bullet();

	void Init();
	void Release();
	void Update();
	void Render();

	void Spawn(D3DXVECTOR3 vEnemyPos, RECT rEnemyRect);
	void Move();
	void OutScreen();
	void Collision();
	void Hit();
	void Effect();

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos;
	D3DXVECTOR2 vDirectVec;
	RECT rRect;

	int iSpeed;
	bool bVisible;

	LPDIRECT3DTEXTURE9 pEffectTex;
	RECT rEffectRect[6];
	int iEffectTime;
	int iEffectCount;
	bool bEffectVisible;
};

