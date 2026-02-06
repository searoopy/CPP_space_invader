#include <iostream>
#include <Windows.h>

#include "Utill/utill.h"
#include "Render/Renderer.h"
#include "Actor.h"
#include "Math/color.h"
#include "Engine/Engine.h"

namespace wanted
{

	Actor::Actor(const char* image ,
		const Vector2& position,
		Color color)
		: position(position), color(color), startPos(position)
	{

		size_t length = strlen(image) + 1;
		this->image = new char[length];
		strcpy_s(this->image, length, image);
		

		// 문자열 길이.
		int count = 0;
		for (int i = 0; i < length - 1; ++i) {
			if (this->image[i] == '\n') {
				count++;
			}
		}

		if (count == 0)
			count = 1;

		size_t max_len = 0;
		char* current_line_start = this->image;

		// 널 종료 문자(\0)를 만날 때까지 전체 순회
		for (size_t i = 0; i < length; ++i) {
			// 줄바꿈(\n)이나 문자열의 끝(\0)을 만났을 때가 한 '줄'의 끝입니다.
			if (this->image[i] == '\n' || this->image[i] == '\0') {

				// 현재 줄의 길이 계산 (현재 위치 주소 - 시작 위치 주소)
				size_t current_line_len = &this->image[i] - current_line_start;

				// 최댓값 비교 및 갱신
				if (current_line_len > max_len) {
					max_len = current_line_len;
				}

				// 다음 줄의 시작점은 현재 개행 문자 바로 다음 칸
				current_line_start = &this->image[i + 1];
			}
		}


		width = max_len;
		height = count+1;
	}

	Actor::~Actor()
	{
		SafeDeleteArray(image);

	}


	//게임 플레이 이벤트
	void Actor::BeginPlay()
	{
		//이벤트를 받은 후에는 플래그 설정.
		hasBeganPlay = true;
	}
	void Actor::Tick(float deltaTime)
	{
	}
	void Actor::Draw()
	{
		//Renderer::Draw(position, image, color);
		Renderer::Get().Submit(
			image, position, color, sortingorder);
	}

	void Actor::Destroy()
	{
		destroyRequested = true;
		OnDestroy();
	}

	void Actor::OnDestroy()
	{
	}

	void Actor::QuitGame()
	{
		Engine::Get().QuitEngine();
	}

	bool Actor::TestIntersect(const Actor* const other)
	{
		//aabb
		//x좌표만 고려하면됨 y는 크기가 1이기 때문...
		int xMin = position.x;
		int xMax = position.x + width - 1;

		int yMin = position.y;
		int yMax = position.y + height - 1;

		//충돌을 비교할 다른액터의 x좌표 정보
		int otherXMin = other->GetPosition().x;
		int otherXMax = other->position.x + other->width - 1;

		int otherYMin = other->GetPosition().y;
		int otherYMax = other->position.y + other->height - 1;

		//안겹치는지 조건 확인
		if (otherXMin > xMax)
		{
			return false;
		}
		else if (otherXMax < xMin)
		{
			return false;
		}

		if (otherYMin > yMax)
		{
			return false;
		}
		else if (otherYMax < yMin)
		{
			return false;
		}

		return true;
		
		//return position.y == other->position.y;
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		//Renderer::Draw(position, ' '); //이전 위치 지우기.

		if (position == newPosition)
		{
			return;
		}

		position = newPosition;

	}



}