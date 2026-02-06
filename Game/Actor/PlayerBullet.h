#pragma once

#include "Actor/Actor.h"


using namespace wanted;

class PlayerBullet :public Actor
{

	RTTI_DECLARATIONS(PlayerBullet, Actor)

public:

	PlayerBullet(const Vector2& position, float dir);
	~PlayerBullet();

	void Tick(float deltatime);

private:
	//float yPosition = 0;
	float moveSpeed = 0;
	float direction = 0;

	float mx = 0;
	float my = 0;
};

