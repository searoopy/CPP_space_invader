#pragma once

#include "Actor/Actor.h"
#include "Utill/Timer.h"

using namespace wanted;




static const char* enemyType[] =
{

	R"( OO 
 OOO
 O0)",

	R"( oOo
ooooo
ooooo
 oOo)",

	R"(     oOo
  oooooooo
ooooooooooo
 ooooooooo
   oooooo
     oOo)",

		R"(   oooo
  oooooooo
 ooooooooooo
ooooooooooooo
 ooooooooooo
   oooooooo
     oooo)",


};

class EnemySpawner : public Actor
{
	RTTI_DECLARATIONS(EnemySpawner, Actor)

public:
	EnemySpawner();

public:
	virtual void Tick(float deltaTime)	override;

	void SpawnEnemy(float f);

private:
	Timer timer;



};

