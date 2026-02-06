#pragma once

#include "Math/Vector2.h"
#include "Math/color.h"
#include <time.h>
#include <cmath>
#include <iostream>

using namespace wanted;

namespace Utill
{
	inline void SetConsolePosition(const Vector2& position)
	{
		
		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			static_cast<COORD>(position)
		);
	}



	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextAttribute(
			GetStdHandle(STD_OUTPUT_HANDLE),
			static_cast<WORD>(color)
		);
	}


	inline void TurnOffCursor()
	{
		CONSOLE_CURSOR_INFO info = {};
		GetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);
		info.bVisible = false;
		SetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);
	}

	inline void TurnOnCursor()
	{
		CONSOLE_CURSOR_INFO info = {};
		GetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);
		info.bVisible = true;
		SetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);
	}

	inline void SetRandomSeed()
	{
		srand(static_cast<unsigned int>(time(nullptr)));
	}

	// 일반화한 함수.
	inline int RandomRange(int min, int max)
	{
		int diff = (max - min) + 1;
		return ((diff * rand()) / (RAND_MAX + 1)) + min;
	}


	inline float RandomRange(float min, float max)
	{

		float random =
			static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		float diff = (max - min);
		return (random * diff) + min;
	}

	inline float to_radian(float degree) {
		const float PI = static_cast<float>(std::acos(-1.0));
		return degree * (PI / 180.0);
	}


	inline float WrapAngle(float angle)
	{
		// 나머지를 구함 (예: 370 -> 10, -10 -> -10)
		angle = fmod(angle, 360.0f);

		// 음수일 경우 360을 더해 양수 범위로 전환
		if (angle < 0)
			angle += 360.0f;

		return angle;
	}



}


template<typename T>
void SafeDeleteArray(T*& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

template<typename T>
void SafeDelete(T*& ptr)
{
	if(ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}