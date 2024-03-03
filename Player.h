#pragma once

class Player
{
public:
	Player();
	~Player();
	enum BulletState { STANDARD, TRIPLE, GUIDED };

	void Init();
	void Release();
	void Update();
	void Render();

	void KeyState();
	void MoveLimit();
	void Animation();
	void FireBullet();
	void Down();
	void Stats();
	void Nuclear();
	void CatchItem(int iValue);
	void Effect();
	void Hit(int iDmg);
	void Slow() { iSpeed /= 2; }

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos;
	RECT rRect;
	RECT rHitBox;
	UINT uiColor;

	int iAS;
	int iUpgradeLevel;
	int iSpeed;
	int iSpeedLevel;
	int iHP;
	int iNuclearCount;
	int iAddonCount;

	bool bPhoenix;
	int iPhoenixTime;
	bool bLeGenDPhoenix;
	
	bool bMove;
	RECT rAnimation[4];
	int iAniTime;
	int iAnii;

	PlayerBullet* m_pPlayerBullet[50];
	int iBulletTime;
	int iBulletCount;

	BulletState bulletstate;

	Addon* m_aAddon[4];

	LPDIRECT3DTEXTURE9 pEffectTex;
	D3DXVECTOR3 vEffectPos;
	RECT rEffectRect[6];
	int iEffectTime;
	int iEffectCount;
	bool bEffectVisible;

public:
	D3DXVECTOR3 GetPos() { return vPos; }
	RECT GetRect() { return rRect; }
	RECT GetHitBox() { return rHitBox; }
	int GetHP() { return iHP; }
	int GetNuclearCount() { return iNuclearCount; }
	int GetBulletState() { return bulletstate; }
	int GetSpeedLevel() { return iSpeedLevel; }
	int GetUpgradeLevel() { return iUpgradeLevel; }

	void GuidedMissile(int i, D3DXVECTOR3 vEnemyPos, RECT vEnemyRect) { m_pPlayerBullet[i]->GuidedMissile(vEnemyPos, vEnemyRect); }
	D3DXVECTOR3 GetBulletPos(int i) { return m_pPlayerBullet[i]->GetPos(); }
	RECT GetBulletRect() { return m_pPlayerBullet[0]->GetRect(); }
	bool GetBulletVisible(int i) { return m_pPlayerBullet[i]->GetVisible(); }
	void BulletHit(int i) { m_pPlayerBullet[i]->Hit(); }
	bool GetBulletGuided(int i) { return m_pPlayerBullet[i]->GetGuided(); }

	D3DXVECTOR3 GetAddonBulletPos(int i, int j) { return m_aAddon[i]->GetBulletPos(j); }
	bool GetAddonBulletVisible(int i, int j) { return m_aAddon[i]->GetBulletVisible(j); }
	void AddonBulletHit(int i, int j) { m_aAddon[i]->BulletHit(j); }

	void SetClearPhoenix() { bPhoenix = true; iPhoenixTime = 5000; }
	void SetPhoenixOff() { bPhoenix = false; iPhoenixTime = 0; }
};

