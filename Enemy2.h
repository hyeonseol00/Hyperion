#pragma once
class Enemy2
{
public:
	Enemy2();
	~Enemy2();

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
	void Fire();

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

	Enemy2Bullet* m_eEnemy2Bullet[10];
	int iFireTime;
	int iBulletCount;

public:
	void BulletHit(int i) { m_eEnemy2Bullet[i]->Hit(); }
};

