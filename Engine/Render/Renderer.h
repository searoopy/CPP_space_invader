#pragma once

#include <iostream>
#include <vector>

#include "Common/Common.h"
#include "Math/color.h"
#include "Math/Vector2.h"

namespace wanted
{
	class ScreenBuffer;


	class WANTED_API Renderer
	{

		//프레임 구조체 -2차원 글자 배열의 항목이 될 구조체
		struct Frame {

			Frame(int bufferCount);
			~Frame();

			void Clear(const Vector2& screenSize);

			CHAR_INFO* charInfo = nullptr;
			

			int* sortingOrderArray = nullptr;
		};


		struct RenderCommand
		{
			const char* text = nullptr;/// charInfo;
			Color color = Color::White;
			Vector2 position;
			int sortingOrder = 0;
		};

	public:

		Renderer(const Vector2& screenSize);
		~Renderer();
		void Draw();

		void Submit(
			const char* text,
			const Vector2& position,
			Color color = Color::White,
			int sortingOrder = 0
		);


		static Renderer& Get();

	private:
		void Clear();



		//더블 버퍼링을 활용해 프레임을 교체하는 함수	
		void Present();

		//현재 사용할 버퍼를 반환하는 함수
		ScreenBuffer* GetCurrentBuffer() const;

	private:
		Vector2 screenSize;

		//관리할 프레임 객체.
		Frame* frame = nullptr;

		//이중 버퍼 배열.
		ScreenBuffer* screenBuffers[2] = {};

		//현재 활성화된 버퍼 인덱스
		int currentBufferIndex = 0;

		//렌더 큐
		std::vector<RenderCommand> renderQueue;
		

		static Renderer* instance;;

	};
}