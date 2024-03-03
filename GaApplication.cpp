#include "DXUT.h"
#include "stdafx.h"

GaApplication GaApplication::singleton;

GaApplication::GaApplication()
{
	gamemode = INTRO;
	for (int i = 0; i < 3; i++)
	{
		wcRankInitial[i] = NULL;
		uiRankScore[i] = 0;
	}
}

GaApplication::~GaApplication()
{
}