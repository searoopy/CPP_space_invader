#pragma once
#include "Common/Common.h"
#include <Windows.h>

namespace wanted
{
	class WANTED_API Vector2
	{
	public:
		Vector2();
		Vector2(int x, int y);
		~Vector2();

		const char* ToString();

		Vector2 operator+(const Vector2& other)const;
		Vector2 operator-(const Vector2& other)const;
		Vector2 operator*(const Vector2& other)const;
		Vector2 operator/(const Vector2& other)const;


		float GetDistance(const Vector2& other)const;

		bool operator==(const Vector2& other)const;
		bool operator!=(const Vector2& other)const;

		operator COORD() const;

	public:
		//x,yÁÂÇ¥
		int x = 0;
		int y = 0;

		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Up;
		static Vector2 Right;
	private:
		char* string = nullptr;
	};
}

