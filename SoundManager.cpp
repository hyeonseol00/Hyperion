#include "DXUT.h"
#include "stdafx.h"

SoundManager SoundManager::singleton;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::LoadSound()
{
	m_cSoundManager->Create(&m_cBGM, L"Data\\Techno_1.wav", 0, GUID_NULL);
	
	for (int i = 0; i < 20; i++) 
		m_cSoundManager->Create(&m_cBoom[i], L"Data\\droid_destroyed3.wav", 0, GUID_NULL);

	for (int i = 0; i < 5; i++)
		m_cSoundManager->Create(&m_cBoom2[i], L"Data\\droid_destroyed2.wav", 0, GUID_NULL);

	for (int i = 0; i < 5; i++)
		m_cSoundManager->Create(&m_cItem[i], L"Data\\ammo_fire.wav", 0, GUID_NULL);
}

void SoundManager::Init()
{
	iCount = 0;
	iCount2 = 0;

	m_cSoundManager = new CSoundManager;
	m_cSoundManager->Initialize(DXUTGetHWND(), DSSCL_PRIORITY);
	m_cSoundManager->SetPrimaryBufferFormat(2, 22050, 16);

	LoadSound();
}

void SoundManager::PlayBoom()
{
	m_cBoom[iCount++]->Play(0, NULL); 
	if (iCount >= 20)
		iCount = 0;
}

void SoundManager::PlayBoom2()
{
	m_cBoom2[iCount2++]->Play(0, NULL);
	if (iCount2 >= 5)
		iCount2 = 0;
}

void SoundManager::PlayItem()
{
	m_cItem[iCount2++]->Play(0, NULL);
	if (iCount2 >= 5)
		iCount2 = 0;
}
