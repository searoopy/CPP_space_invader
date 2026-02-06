#include "PlayerGui.h"
#include "Render/Renderer.h"
using namespace wanted;

PlayerGui* PlayerGui::instance = nullptr;

PlayerGui::PlayerGui(const Vector2& pos )
	: super("H :", pos, Color::Red) , BulletCnt(5)
{

	instance = this;


	displayStr = new char[10];

}

PlayerGui::~PlayerGui()
{
	delete[] displayStr;
	displayStr = nullptr;
}

PlayerGui& PlayerGui::Get()
{

	// 싱글턴
	if (!instance)
	{

		std::cout << "error:gui::get(). instance is null";


		//디버그 모드에서만 작동
		//자동으로 중단점 걸림.
		__debugbreak();

	}

	return *instance;
}



void PlayerGui::Draw()
{
	
	int count = (BulletCnt < 0) ? 0 : (BulletCnt > 5) ? 5 : BulletCnt;




	// 2. 고정된 앞부분 쓰기
	displayStr[0] = 'B';
	displayStr[1] = ' ';
	displayStr[2] = ':';
	displayStr[3] = ' ';

	// 3. 총알 개수만큼 별(*) 채우기
	for (int i = 0; i < count; ++i) {
		displayStr[4 + i] = '*';
	}

	// 4. 중요: 남은 공간을 공백으로 지우거나, 바로 널 문자로 닫기
	// 여기서는 문자열의 끝을 명확히 하기 위해 별 다음에 바로 \0을 넣습니다.
	displayStr[4 + count] = '\0';



	Renderer::Get().Submit(displayStr, position, color, sortingorder);
}

void PlayerGui::Tick(float deltatime)
{

}


