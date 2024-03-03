#pragma once
class Enemy4Division
{
public:
	Enemy4Division();
	~Enemy4Division();

	void Init();
	void Release();
	void Update();
	void Render();

	void Spawn(D3DXVECTOR3 vEnemyPos, RECT rEnemyRect, int Direction);
	void Move();
	void Collision();
	void Down();
	void OutScreen();
	void Effect();

	void Hit(int iDmg);
	void Crash() { iHP = 0; }

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos;
	RECT rRect;
	RECT rHitBox;
	bool bVisible;
	UINT uiColor;

	int iSpeed;
	int iHP;

	RECT rAnimation[2];
	int iAniTime;
	int iAnii;

	RECT rRader;
	bool bLockOn;

	RECT rGuided;

	LPDIRECT3DTEXTURE9 pEffectTex;
	RECT rEffectRect[6];
	int iEffectTime;
	int iEffectCount;
	bool bEffectVisible;

	D3DXVECTOR2 vDirectVec;

	int iDirection;
};

