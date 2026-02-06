#pragma once


#include <Windows.h>
#include "Math/Vector2.h"

namespace wanted
{
	//더블 버퍼링에 사용할 console output 핸들을 관리하는 클래
	class ScreenBuffer
	{
	public:
		ScreenBuffer(const Vector2& size);
		~ScreenBuffer();



		//콘솔 버퍼 지우는 함수
		void  Clear();


		//콘솔 버퍼에 출력하는 함수
		void Draw(CHAR_INFO* buffer);

		inline HANDLE GetBuffer() const { return buffer; };



	private:
		HANDLE buffer = nullptr;
		Vector2 screenSize;


	};



}
