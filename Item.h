#pragma once
class Item
{
public:
	Item();
	~Item();
	enum ItemValue {ADDON, NUCLEAR, TRIPLE, GUIDED, SPEED, UPGRADE, HEAL};

	void Init();
	void Release();
	void Update();
	void Render();

	void Spawn();
	void Move();
	void Collision();

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos;
	RECT rRect;
	RECT rItemValue[7];

	bool bVisible;

	ItemValue itemvalue;

	int iSpeed;
};

