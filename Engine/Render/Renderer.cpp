#include "Renderer.h"
#include "Utill/utill.h"
#include "ScreenBuffer.h"

#include <string>
#include <string_view>
#include <sstream>


namespace wanted
{

	Renderer* Renderer::instance = nullptr;

	Renderer::Renderer(const Vector2& screenSize)
		: screenSize(screenSize)
	{
		instance = this;

		//프레임 객체 생성.
		const int buffercount = screenSize.x * screenSize.y;
		frame = new Frame(buffercount);
		frame->Clear(screenSize);
		

		//이중 버퍼 배열.
		screenBuffers[0] = new  ScreenBuffer(screenSize);
		screenBuffers[1] = new  ScreenBuffer(screenSize);
		screenBuffers[0]->Clear();
		screenBuffers[1]->Clear();


		Present();
		//ScreenBuffer* screenBuffers[2] = {};


	}
	Renderer::~Renderer()
	{
		SafeDelete(frame);

		for(ScreenBuffer*& buffer : screenBuffers)
		{
			SafeDelete(buffer);
		}
	}

	void Renderer::Submit(const char* text, const Vector2& position, Color color, int sortingOrder)
	{
		RenderCommand command;
		command.text = text;
		command.position = position;
		command.color = color;
		command.sortingOrder = sortingOrder;

		renderQueue.emplace_back(command);
	}

	void Renderer::Present()
	{
		//버퍼 교환.
		SetConsoleActiveScreenBuffer(
			GetCurrentBuffer()->GetBuffer()
		);


		//인덱스 교체
		currentBufferIndex = 1 - currentBufferIndex;
	}


	void Renderer::Draw()
	{
		//화면 지우기.
		Clear();

		//전제조건: 레벨의 모든 액터가 렌더러에 submit을 완료.
		//렌더큐  순회하면서 프레임 채우기
		for (const RenderCommand& command : renderQueue)
		{
			if (!command.text) continue;

			// 1. 문자열을 줄 단위로 분리
			std::vector<std::string> lines;
			std::stringstream ss(command.text);
			std::string segment;
			while (std::getline(ss, segment, '\n')) {
				lines.push_back(segment);
			}

			// 2. 각 줄을 순회하며 그리기
			for (int i = 0; i < lines.size(); ++i) {
				int targetY = command.position.y + i;

				// Y축 화면 범위 체크
				if (targetY < 0 || targetY >= screenSize.y) continue;

				const std::string& line = lines[i];
				for (int j = 0; j < line.length(); ++j) {
					int targetX = command.position.x + j;

					// X축 화면 범위 체크
					if (targetX < 0 || targetX >= screenSize.x) continue;

					// 3. 2차원 인덱스 계산
					const int index = (targetY * screenSize.x) + targetX;

					// 4. 우선순위(Sorting Order) 체크
					if (frame->sortingOrderArray[index] > command.sortingOrder) {
						continue;
					}

					// 5. 데이터 기록
					frame->charInfo[index].Char.AsciiChar = line[j];
					frame->charInfo[index].Attributes = (WORD)command.color;
					frame->sortingOrderArray[index] = command.sortingOrder;
				}
			}
		}



		//그리기.
		GetCurrentBuffer()->Draw(frame->charInfo);


		//버퍼 교환.,
		Present();


		//렌더큐 지우기.
		renderQueue.clear();
	}


	void Renderer::Clear()
	{
		//화면 지우기.
		//1. 프레임 지우기
		frame->Clear(screenSize);

		//2. 콘솔 버퍼 지우기
		GetCurrentBuffer()->Clear();
	}

	ScreenBuffer* Renderer::GetCurrentBuffer() const
	{
		return screenBuffers[currentBufferIndex];
	}

	Renderer& Renderer::Get()
	{
		if(!instance)
		{
			MessageBoxA(
				nullptr,
				"Renderer instance is null!",
				"Renderer Get Error",
				MB_OK
			);
			__debugbreak();
		}

		return *instance;
	}
	

	Renderer::Frame::Frame(int bufferCount)
	{
		charInfo = new CHAR_INFO[bufferCount];
		memset(charInfo, 0, sizeof(CHAR_INFO) * bufferCount);


		sortingOrderArray = new int[bufferCount];
		memset(sortingOrderArray, 0, sizeof(int) * bufferCount);
	}

	Renderer::Frame::~Frame()
	{
		SafeDeleteArray(charInfo);
		SafeDeleteArray(sortingOrderArray);
	}

	void Renderer::Frame::Clear(const Vector2& screenSize)
	{

		const int width = (int)screenSize.x;
		const int height = (int)screenSize.y;

		for(int y = 0; y < height; ++y)
		{
			for(int x = 0; x < width; ++x)
			{
				const int index = y * width + x;

				//todo : ㅁㄴㅇㄹㄴㅁㄹ
				//test : ㄴㅇㄹㄴㄹㅇ
				charInfo[index].Char.AsciiChar = '#';  
				charInfo[index].Attributes = static_cast<WORD>(Color::Black);
				sortingOrderArray[index] = -1;
			}
		}
	}

}