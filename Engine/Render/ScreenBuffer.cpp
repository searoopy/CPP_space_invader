#include "ScreenBuffer.h"
#include <iostream>
#include "Renderer.h"

namespace wanted
{
	ScreenBuffer::ScreenBuffer(const Vector2& size)
		: screenSize(size)
	{
		buffer = CreateConsoleScreenBuffer(
			GENERIC_READ |           // read/write access
			GENERIC_WRITE,
			FILE_SHARE_READ |
			FILE_SHARE_WRITE,        // shared
			NULL,                    // default security attributes
			CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
			NULL);

		if (buffer == INVALID_HANDLE_VALUE)
		{
			MessageBoxA(nullptr, "Screenbuffer can't created!",
				"buffer creation error",
				MB_OK);

			__debugbreak();
		}

		SMALL_RECT rect;
		rect.Left = 0;	
		rect.Top = 0;	
		rect.Right = screenSize.x - 1;		
		rect.Bottom = screenSize.y - 1;	


		if(!SetConsoleWindowInfo(buffer, TRUE, &rect))
		{
			MessageBoxA(nullptr, "Screenbuffer window info can't set!",
				"buffer window info error",
				MB_OK);
			__debugbreak();
		}


		//버퍼 크기 설정.
		if (!SetConsoleScreenBufferSize(buffer, (COORD)screenSize))
		{
			std::cerr << "Screenbuffer size can't set!\n";
			__debugbreak();
		}


		//커서 끄기.
		CONSOLE_CURSOR_INFO info;
		GetConsoleCursorInfo(buffer, &info);
		info.bVisible = false;
		SetConsoleCursorInfo(buffer, &info);

	}
	ScreenBuffer::~ScreenBuffer()
	{
		if (buffer)
		{
			CloseHandle(buffer);
			buffer = nullptr;
		}
	}
	
	void ScreenBuffer::Clear()
	{

		//실제로 화면을 지우고 난뒤
		//몇글자를 썻는지 반환받는데 사용.
		DWORD writtenCount = 0;


		//콘솔 버퍼에 있는 화면 지우기.
		//그래픽스 -> 지우기 -> 한 색상(또는 값)으로 덮어쓰기.
		FillConsoleOutputCharacterA(
			buffer,
			' ',
			screenSize.x * screenSize.y,
			Vector2::Zero,
			&writtenCount
		);
	}

	void ScreenBuffer::Draw(CHAR_INFO* buffer)
	{

		//설정할 버퍼의 크기.
		SMALL_RECT writeRegion = {};
		writeRegion.Left = 0;
		writeRegion.Top = 0;
		writeRegion.Right = static_cast<short>(screenSize.x - 1);
		writeRegion.Bottom = static_cast<short>(screenSize.y - 1);	

		

		
		WriteConsoleOutputA(
			this->buffer,
			buffer,
			(COORD)screenSize,
			Vector2::Zero,
			&writeRegion
		);
		


	}
}