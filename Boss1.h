#pragma once
class Boss1
{
public:
	Boss1();
	~Boss1();

	void Init();
	void Release();
	void Update();
	void Render();

	void Spawn();
	void Move();
	void Collision();
	void Down();
	void Fire();
	void Animation();
	void Effect();

	void Hit(int iDmg);

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos;
	RECT rRect;

	bool bVisible;
	bool bDeath;
	int iSpeed;
	int iHP;

	Boss1Bullet* m_bBoss1Bullet[16];
	int iBulletTime;

	RECT rGuided;

	RECT rAnimation[2];
	int iAniTime;
	int iAnii;

	LPDIRECT3DTEXTURE9 pEffectTex;
	RECT rEffectRect[6];
	int iEffectTime;
	int iEffecti;
	bool bEffectVisible;

public:
	bool GetVisible() { return bVisible; }
	void BulletHit(int i) { m_bBoss1Bullet[i]->Crash(); }
};

