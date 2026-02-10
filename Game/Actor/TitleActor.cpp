#include "TitleActor.h"
#include "Core/Input.h"
#include "Render/Renderer.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
using namespace wanted;


const char* TitleActor::titlename =
R"(
  ____  ____   _    ____ _____   ___ _   ___     Abstract ____  _____ ____  
 / ___||  _ \ / \  / ___| ____| |_ _| \ | \ \   / /  _  |  _ \| ____|  _ \ 
 \___ \| |_) / _ \| |   |  _|    | ||  \| |\ \ / /| | | | | | |  _| | |_) |
  ___) |  __/ ___ \ |___| |___   | || |\  | \ V / | |_| | |_| | |___|  _ < 
 |____/|_| /_/   \_\____|_____| |___|_| \_|  \_/  |____/|____/|_____|_| \_\
                                                                            
             [  ; : ^ : ;  ]  [  z Z w Z z  ]  [  o O @ O o  ]
)";

TitleActor::TitleActor(const Vector2& pos)
    : super(titlename, pos, Color::Green), menuIdx(enumMenu::_gamestart)
{

	int _x = Engine::Get().GetWidthCenter() - (width / 2);
	int _y = 0;
	titlenameVector.x = _x;
	titlenameVector.y = _y;

	startGameVector.x = Engine::Get().GetWidthCenter() - (strStartGame.length() / 2);
	startGameVector.y = Engine::Get().GetHeightCenter() + 5;
	quitGameVector.x = Engine::Get().GetWidthCenter() - (strQuitGame.length() / 2);
	quitGameVector.y = Engine::Get().GetHeightCenter() + 6;



}

TitleActor::~TitleActor()
{
}


void TitleActor::Tick(float deltatime) 
{

	super::Tick(deltatime);

	if (Input::Get().GetKeyDown(VK_UP))
	{

		menuIdx -= 1;
		if (menuIdx < 0)
		{
			menuIdx = enumMenu::_max - 1;
		}

	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		menuIdx += 1;
		if (menuIdx >= enumMenu::_max)
		{
			menuIdx = 0;
		}
	}

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		if (menuIdx == enumMenu::_gamestart)
		{
			Game::Get().ToggleMenu();

		}
		else if(menuIdx == enumMenu::_quit)
		{
			Game::Get().QuitEngine();
		}

	}
}

void TitleActor::Draw()
{

	

	//title..
	Renderer::Get().Submit(
		titlename, titlenameVector, color, sortingorder);



	if (menuIdx == enumMenu::_gamestart)
	{

		Renderer::Get().Submit(
			strStartGame.c_str() , startGameVector, Color::Green, sortingorder);
		Renderer::Get().Submit(
			strQuitGame.c_str(), quitGameVector, Color::White, sortingorder);

	}
	else
	{
		Renderer::Get().Submit(
			strStartGame.c_str(), startGameVector, Color::White, sortingorder);
		Renderer::Get().Submit(
			strQuitGame.c_str(), quitGameVector, Color::Green, sortingorder);
	}



}


