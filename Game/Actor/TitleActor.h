#pragma once

#include "Actor/Actor.h"
#include "Common/RTTI.h"
#include "Math/Vector2.h"
#include <string>


using namespace wanted;

class TitleActor : public Actor
{

	enum enumMenu
	{
		_gamestart,
		_quit,
		_max
	};


	RTTI_DECLARATIONS(TitleActor, Actor)

public:
	TitleActor(const Vector2& pos);
	~TitleActor();

public:
	virtual void Tick(float deltatime) override;
	virtual void Draw() override;

	static const char* titlename;		// = "abc";

private:
	int menuIdx = 0;

	std::string strStartGame = "Start Game";
	std::string strQuitGame = "Quit";

	Vector2 startGameVector;
	Vector2 quitGameVector;


	Vector2 titlenameVector;
};