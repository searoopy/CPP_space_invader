#pragma once

#include "Level/Level.h"

using namespace wanted;

class Player;

class GameLevel : public Level
{
	// RTTI 등록.
	RTTI_DECLARATIONS(GameLevel, Level)



public:

	GameLevel();
	~GameLevel();

	virtual void Tick(float dtime) override;

	//충돌 판정 처리 함수.
	void ProcessCollisionPlayerBulletAndEnemy();

	void ProcessCollisionPlayerAndEnemyBullet();

	void ProcessCollisionPlayerAndEnemy();


	virtual void Reset_Level() override;



private:

	Player* m_player  = nullptr;

};
