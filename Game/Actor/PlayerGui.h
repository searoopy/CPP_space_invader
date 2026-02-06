#pragma once

#include "Actor/Actor.h"
#include "Common/RTTI.h"

using namespace wanted;

class PlayerGui :public Actor
{
	//friend class GameLevel;

	RTTI_DECLARATIONS(PlayerGui, Actor)

public:
	PlayerGui(const Vector2& pos  );
	~PlayerGui();

public:
	void Tick(float deltatime);

	void Draw();

	inline void SetBullet(int cnt) { BulletCnt = cnt; }

	static PlayerGui& Get();
	static PlayerGui* instance;

private:
	int BulletCnt;

	char* displayStr = nullptr;
};

