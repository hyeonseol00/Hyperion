#pragma once
class Boss4Bullet
{
public:
	Boss4Bullet();
	~Boss4Bullet();

	void Init();
	void Release();
	void Update();
	void Render();

	void Fire(D3DXVECTOR3 vEnemyPos, RECT rEnemyRect, int iNum, float fMax);
	void Move();
	void OutScreen();
	void Collision();
	void Crash() { bVisible = false; }

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos;
	RECT rRect;

	D3DXVECTOR2 vDirectVec;
	bool bVisible;
	int iSpeed;
};


