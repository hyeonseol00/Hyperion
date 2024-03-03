#pragma once
class Enemy4
{
public:
	Enemy4();
	~Enemy4();

	void Init();
	void Release();
	void Update();
	void Render();

	void Spawn();
	void Move();
	void Animation();
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

	Enemy4Division* m_eEnemy4Division[2];

public:
	void DivisionCrash(int i) { m_eEnemy4Division[i]->Crash(); }
};

