#pragma once
class GaApplication
{
public:
	GaApplication();
	~GaApplication();
	static GaApplication* Instance() { return &singleton; }
	enum GameMode { INTRO, MENU, STAGE1, STAGE2, PAUSE, GAMEOVER, ENDING };

private:
	static GaApplication singleton;
	GameMode gamemode;

	LPCWSTR wcRankInitial[3];
	UINT uiRankScore[3];

public:
	GameMode GetGameMode() { return gamemode; }
	void SetGameMode(GameMode _mode) { gamemode = _mode; }

	LPCWSTR GetRankInitial(int i) { return wcRankInitial[i]; }
	void SetRankInitial(int i, LPCWSTR initial) { wcRankInitial[i] = initial; }
	UINT GetRankScore(int i) { return uiRankScore[i]; }
	void SetRankScore(int i, UINT score) { uiRankScore[i] = score; }
};

#define GAAPP() GaApplication::Instance()