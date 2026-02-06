#pragma once
#include "Common/Common.h";
#include "Math/Vector2.h"


namespace wanted
{
	class Level;
	class Input;
	class Renderer;

	class WANTED_API Engine
	{
		struct EngineSetting
		{
			//프레임 속도
			float framerate = 0.0f;


			//화면 너비
			int width = 0;

			//화면높이
			int height = 0;
		};


	public:
		Engine();
		virtual ~Engine();
		
		void Run();

		void QuitEngine();

		void SetNewLevel(class Level* newLevel);


		static Engine& Get();

		// 화면 너비 반환 함수.
		inline int GetWidth() const { return setting.width; }
		inline int GetWidthCenter() const { return setting.width/2; }

		// 화면 높이 반환 함수.
		inline int GetHeight() const { return setting.height; }
		inline int GetHeightCenter() const { return setting.height/2; }

		bool IsScreenOut(const Vector2& other) const;

	protected:
		//정리 함수.
		void Shutdown();
		
		void LoadSetting();

		void BeginPlay();

		void Tick(float deltaTime);

		void Draw();

	

	protected:
		//종료 플래그.
		bool isQuit = false;

		//엔진 설정 값.
		EngineSetting setting;

		//입력 관리자
		Input* input = nullptr;

		Renderer* renderer = nullptr;

		//메인 레벨
		class Level* mainLevel = nullptr;

		static Engine* instance;

		int width = 0;
		int height = 0;

	};
}