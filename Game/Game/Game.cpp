#include "Game.h"
#include "Level/GameLevel.h"
#include <iostream>

//정적 변수 초기화.
Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	// 두 레벨 생성 및 배열에 추가..
	levels.emplace_back(new GameLevel());
	levels.emplace_back(new TitleLevel());

	//시작 상태(레벨) 설정.
	state = State::GamePlay;

	//게임 시작시 활성화할 레벨 설정.
	mainLevel = levels[0];
}

Game::~Game()
{

	//중복 제거 방지.
	mainLevel = nullptr;


	for (Level*& level : levels)
	{
		delete level;
		level = nullptr;
	}
}

void Game::ToggleMenu()
{
	//화면 지우기
	system("cls");

	//변경할 인덱스 계산
	//마법의 공식 - (1-x) -> oneMinus
	int stateIndex = (int)state;  //static_cast<int>
	//int stateIndex = static_cast<int>(state);  //static_cast<int>
	int nextState = 1 - stateIndex;  //  one - x.
	state = (State)nextState;

	if (state == State::GamePlay)
	{
		levels[0]->Reset_Level();
	}

	//플레이어 데이터 리셋.


	//메인 레벨 변경.
	mainLevel = levels[static_cast<int>(state)];




}


Game& Game::Get()
{
	if (!instance)
	{
		std::cerr << "Game::Get() - instance is null\n";
		__debugbreak();
	}

	return *instance;
}