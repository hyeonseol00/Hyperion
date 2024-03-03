#pragma once
class Addon
{
public:
	Addon();
	~Addon();

	void Init();
	void Release();
	void Update();
	void Render();

	void Spawn(D3DXVECTOR3 vPlayerPos, RECT rPlayerRect, int iDirection, bool bMove);
	void Fire();

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos;
	RECT rRect;

	RECT rAnimation[4];
	int iAniTime;
	int iAnii;
	bool bMove;

	bool bVisible;

	PlayerBullet* m_pAddonBullet[25];
	int iFireTime;
	int iBulletCount;

public:
	D3DXVECTOR3 GetBulletPos(int i) { return m_pAddonBullet[i]->GetPos(); }
	bool GetBulletVisible(int i) { return m_pAddonBullet[i]->GetVisible(); }
	void BulletHit(int i) { m_pAddonBullet[i]->Hit(); }
};

