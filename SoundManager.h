#pragma once
class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	static SoundManager* Instance() { return &singleton; }
	void LoadSound();

	void Init();

private:
	static SoundManager singleton;
	
	CSound* m_cBGM;
	CSound* m_cBoom[20];
	CSound* m_cBoom2[5];
	CSound* m_cItem[5];
	int iCount;
	int iCount2;

	CSoundManager* m_cSoundManager;

public:
	void PlayBGM() { m_cBGM->Play(0, DSBPLAY_LOOPING); }
	void StopBGM() { m_cBGM->Stop(); }
	
	void PlayBoom();
	void PlayBoom2();
	void PlayItem();
};

#define SNDMAN() SoundManager::Instance()