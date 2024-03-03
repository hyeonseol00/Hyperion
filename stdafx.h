#pragma once
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	960
#define SCREEN_RECT		RECT{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}

#include <time.h>
#include "SDKsound.h"

//		CUSTOM HEADER		//
#include "GaApplication.h"
#include "FontManager.h"
#include "SoundManager.h"

#include "Intro.h"
#include "Menu.h"
#include "BackGround.h"
#include "PlayerBullet.h"
#include "Addon.h"
#include "Player.h"
#include "Enemy1.h"
#include "Enemy2Bullet.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4Division.h"
#include "Enemy4.h"
#include "Boss1Bullet.h"
#include "Boss1.h"
#include "Boss2Bullet.h"
#include "Boss2.h"
#include "Boss3Bullet.h"
#include "Boss3.h"
#include "Boss4Bullet.h"
#include "Boss4.h"
#include "Obstacle.h"
#include "Item.h"
#include "UserInterface.h"
#include "ObjectManager.h"