#pragma once

#include "Actor/Actor.h"
#include "Actor/Enemy.h"
#include "Utill/Timer.h"
#include "Utill/utill.h"

using namespace wanted;



class BulletItem : public Actor
{
	RTTI_DECLARATIONS(BulletItem, Actor)

public:
	BulletItem(const char* image = "BB\nBB");
	~BulletItem();

	virtual void Tick(float deltaTime) override;

	virtual void OnDestroy() override;

	inline int GetBulletCnt() {
		return bulletAddCnt;
	}

private:
	int bulletAddCnt = 5;
	float mx = 0.0f;
	float my = 0.0f;

public:
	static int bulletItemCnt;
};

