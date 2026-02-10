#pragma once

#include "Engine/Engine.h"
#include "Level/TitleLevel.h"


#include <vector>

using namespace wanted;

enum class State
{
	//None = -1,
	GamePlay = 0,
	Menu = 1,

	Length
};

class Game : public Engine
{

public:
	Game();
	virtual ~Game();


	void ToggleMenu();

	static Game& Get();

private:
	//게임에서 관리하는 레벨을 저장할 배열.
	std::vector<Level*> levels;


	//현재 활성화된 레벨을 나타냄.
	State state = State::GamePlay;

	static Game* instance;

};

