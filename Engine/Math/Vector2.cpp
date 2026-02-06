#include "Vector2.h"
#include "Common/Common.h"
#include <iostream>
#include <cmath>

namespace wanted
{

	Vector2 Vector2::Zero(0, 0);
	Vector2 Vector2::One(1, 1);
	Vector2 Vector2::Up(0, 1);
	Vector2 Vector2::Right(1, 0);


	Vector2::Vector2()
	{
	}

	Vector2::Vector2(int x, int y)
		:x(x), y(y)
	{
	}

	Vector2::~Vector2()
	{
	}

	const char* Vector2::ToString()
	{
		if (string)
		{
			delete[] string;
			string = nullptr;
		}

		string = new char[128];
		memset(string, 0, sizeof(char) * 128);
		sprintf_s(string, 128, "(%d, %d)", x, y);
		return nullptr;
	}


	Vector2 Vector2::operator+(const Vector2& other)const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 Vector2::operator-(const Vector2& other)const
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 Vector2::operator*(const Vector2& other)const
	{
		return Vector2(x * other.x, y * other.y);
	}
	

	Vector2 Vector2::operator/(const Vector2& other)const
	{
		return Vector2(x / other.x, y / other.y);
	}
	

	float Vector2::GetDistance(const Vector2& other) const
	{

		float dx = x - other.x;
		float dy = y - other.y;
		return std::sqrt(dx * dx + dy * dy);

		
	}

	bool Vector2::operator==(const Vector2& other)const
	{
		return (x == other.x) && (y == other.y);
	}

	bool Vector2::operator!=(const Vector2& other)const
	{
		return (x != other.x) && (y != other.y);
	}

	Vector2::operator COORD() const
	{
		COORD coord = {};
		coord.X = static_cast<short>(x);
		coord.Y = static_cast<short>(y);

		return coord;
	}

}