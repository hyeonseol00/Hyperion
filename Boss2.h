#pragma once
class Boss2
{
public:
	Boss2();
	~Boss2();

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

	Boss2Bullet* m_bBoss2Bullet[24];
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
	bool GetDeath() { return bDeath; }
	void BulletHit(int i) { m_bBoss2Bullet[i]->Crash(); }
};

