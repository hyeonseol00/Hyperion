#pragma once
class PlayerBullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	void Init();
	void Release();
	void Update();
	void Render();

	void Spawn(D3DXVECTOR3 vPlayerPos, RECT rPlayerRect, int iDirection, bool bGuided);
	void Move();
	void OutScreen();
	void GuidedMissile(D3DXVECTOR3 vEnemyPos, RECT vEnemyRect);
	void Effect();
	void Hit();

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos;
	D3DXVECTOR2 vDirectVec;
	RECT rRect;
	bool bVisible;

	float fSpeed;

	RECT rDirection[3];
	int iDirection;
	bool bGuided;

	LPDIRECT3DTEXTURE9 pEffectTex;
	RECT rEffectRect[6];
	int iEffectTime;
	int iEffectCount;
	bool bEffectVisible;

public:
	D3DXVECTOR3 GetPos() { return vPos; }
	RECT GetRect() { return rRect; }
	bool GetVisible() { return bVisible; }
	bool GetGuided() { return bGuided; }
};

