#include <iostream>
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

using namespace wanted;

int main()
{
	Engine engine;
	engine.SetNewLevel(new GameLevel());
	engine.Run();
}