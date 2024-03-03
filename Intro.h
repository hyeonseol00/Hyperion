#pragma once
class Intro
{
public:
	Intro();
	~Intro();

	void Init();
	void Release();
	void Update();
	void Render();

private:
	LPDIRECT3DTEXTURE9 pTex;

	int iIntroTime;
};

