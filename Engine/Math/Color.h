#pragma once


#include "common/Common.h"
#include <Windows.h>



namespace wanted
{
	enum class WANTED_API Color : unsigned char
	{
		Black = 0,
		Red = FOREGROUND_RED,
		Green = FOREGROUND_GREEN,
		Blue = FOREGROUND_BLUE,
		Yellow = FOREGROUND_RED | FOREGROUND_GREEN,


		White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
	};	


}