#pragma once
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
	static ObjectManager* Instance() { return &singleton; }
	void LoadData(LPCWSTR pFile, int width, int height, LPDIRECT3DTEXTURE9* pTex);
	void Draw(LPDIRECT3DTEXTURE9 pTex, RECT rRect, D3DXVECTOR3 vPos, UINT uiColor);
	bool Collision(D3DXVECTOR3 vOpponentPos, RECT rOpponentRect, D3DXVECTOR3 vPos, RECT rRect);
	enum StageState { STAGE1, STAGE2 };
	enum StagePhase { PHASE1, PHASE2 };

	void Init();
	void Release();
	void StageInit();
	void StageRelease();

	void IntroUpdate();
	void IntroRender();
	void MenuUpdate();
	void MenuRender();
	
	void Stage1Spawn();
	void Stage1Update();
	void Stage1Render();

	void Stage2Spawn();
	void Stage2Update();
	void Stage2Render();

	void SetRanking();
	void InputInitial() { m_mMenu->InputInitial(); };
	LPCWSTR GetInitial() { return m_mMenu->GetInitial(); }

private:
	static ObjectManager singleton;

	LPD3DXSPRITE pSprite;

	Intro* m_iIntro;
	Menu* m_mMenu;

	UINT uiScore;

	Player* m_pPlayer;	
	BackGround* m_bBackGround;
	Enemy1* m_eEnemy1[25];
	Enemy2* m_eEnemy2[25];
	Enemy3* m_eEnemy3[25];
	Enemy4* m_eEnemy4[25];
	Item* m_iItem[25];
	Obstacle* m_oObstacle[25];
	Boss1* m_bBoss1;
	Boss2* m_bBoss2;
	Boss3* m_bBoss3;
	Boss4* m_bBoss4;
	UserInterface* m_uUserInterface;

public:
	StageState stagestate;
	StagePhase stagephase;

	int iEnemy1Time;
	int iEnemy1Count;

	int iEnemy2Time;
	int iEnemy2Count;

	int iEnemy3Time;
	int iEnemy3Count;

	int iEnemy4Time;
	int iEnemy4Count;

	int iItemTime;
	int iItemCount;

	int iObstacleTime;
	int iObstacleCount;

public:
	//Score
	UINT GetScore() { return uiScore; }
	void PlusScore(int _score) { uiScore += _score; }

	//Menu
	void MenuMouseSate(bool bM1Down, int x, int y) { m_mMenu->MouseState(bM1Down, x, y); }

	//Player
	D3DXVECTOR3 GetPlayerPos() { return m_pPlayer->GetPos(); }
	RECT GetPlayerRect() { return m_pPlayer->GetRect(); }
	RECT GetPlayerHitBox() { return m_pPlayer->GetHitBox(); }
	void PlayerHit(int iDmg) { m_pPlayer->Hit(iDmg); }
	int GetPlayerHP() { return m_pPlayer->GetHP(); }
	int GetNuclearCount() { return m_pPlayer->GetNuclearCount(); }
	void CatchItem(int iValue) { m_pPlayer->CatchItem(iValue); }
	int GetBulletState() { return m_pPlayer->GetBulletState(); }
	int GetSpeedLevel() { return m_pPlayer->GetSpeedLevel(); }
	int GetUpgradeLevel() { return m_pPlayer->GetUpgradeLevel(); }
	void PlayerSlow() { m_pPlayer->Slow(); }

	void PlayerGuidedMissile(int i, D3DXVECTOR3 vEnemyPos, RECT vEnemyRect) { m_pPlayer->GuidedMissile(i, vEnemyPos, vEnemyRect); }
	D3DXVECTOR3 GetPlayerBulletPos(int i) { return m_pPlayer->GetBulletPos(i); }
	RECT GetPlayerBulletRect() { return m_pPlayer->GetBulletRect(); }
	bool GetPlayerBulletVisible(int i) { return m_pPlayer->GetBulletVisible(i); }
	void PlayerBulletHit(int i) { m_pPlayer->BulletHit(i); }
	bool GetPlayerBulletGuided(int i) { return m_pPlayer->GetBulletGuided(i); }

	D3DXVECTOR3 GetAddonBulletPos(int i, int j) { return m_pPlayer->GetAddonBulletPos(i, j); }
	bool GetAddonBulletVisible(int i, int j) { return m_pPlayer->GetAddonBulletVisible(i, j); }
	void AddonBulletHit(int i, int j) { m_pPlayer->AddonBulletHit(i, j); }

	void SetPlayerPhoenix() { m_pPlayer->SetClearPhoenix(); }
	void SetPlayerPhoenixOff() { m_pPlayer->SetPhoenixOff(); }

	//Nuclear Launch Detected.
	void Enemy1Crash(int i) { m_eEnemy1[i]->Crash(); }
	void Enemy2Crash(int i) { m_eEnemy2[i]->Crash(); }
	void Enemy2BulletHit(int i, int j) { m_eEnemy2[i]->BulletHit(j); }
	void Enemy3Crash(int i) { m_eEnemy3[i]->Crash(); }
	void Enemy4Crash(int i) { m_eEnemy4[i]->Crash(); }
	void Enemy4DivisionCrash(int i, int j) { m_eEnemy4[i]->DivisionCrash(j); }

	//Boss
	bool GetBoss1Visible() { return m_bBoss1->GetVisible(); }
	void Boss1Hit(int iDmg) { m_bBoss1->Hit(iDmg); }
	void Boss1BulletHit(int i) { m_bBoss1->BulletHit(i); }

	bool GetBoss2Visible() { return m_bBoss2->GetVisible(); }
	void Boss2Hit(int iDmg) { m_bBoss2->Hit(iDmg); }
	void Boss2BulletHit(int i) { m_bBoss2->BulletHit(i); }
	bool GetBoss2Death() { return m_bBoss2->GetDeath(); }

	bool GetBoss3Visible() { return m_bBoss3->GetVisible(); }
	void Boss3Hit(int iDmg) { m_bBoss3->Hit(iDmg); }
	void Boss3BulletHit(int i) { m_bBoss3->BulletHit(i); }

	bool GetBoss4Visible() { return m_bBoss4->GetVisible(); }
	void Boss4Hit(int iDmg) { m_bBoss4->Hit(iDmg); }
	void Boss4BulletHit(int i) { m_bBoss4->BulletHit(i); }
	bool GetBoss4Death() { return m_bBoss4->GetDeath(); }
};

#define OBJMAN() ObjectManager::Instance()