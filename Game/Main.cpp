#include <iostream>
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Game/Game.h"
using namespace wanted;

int main()
{
	/*Engine engine;
	engine.SetNewLevel(new GameLevel());
	engine.Run();*/

	Game game;
	game.Run();

}