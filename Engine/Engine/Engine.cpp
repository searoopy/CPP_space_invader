#include <iostream>
#include <Windows.h>


#include "Engine.h"
#include "Level\Level.h"
#include "Core/Input.h"
#include "Utill/utill.h"
#include "Render/Renderer.h"


namespace wanted
{
	Engine* Engine::instance = nullptr;


	Engine::Engine()
	{
		instance = this;
		input = new Input();


		LoadSetting();


		//렌더러 객체 생성.
		renderer = new Renderer(Vector2(setting.width, setting.height));

		Utill::TurnOffCursor();


		Utill::SetRandomSeed();

	}


	Engine::~Engine()
	{
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}


		// 입력 관리자 제거.
		if (input)
		{
			delete input;
			input = nullptr;
		}

		SafeDelete(renderer);

	}

	void Engine::Run()
	{

		//시계 정밀도.
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);

		int64_t currentTime = 0;
		int64_t previousTime = 0;

		//하드웨어 타이머로 시간구함.
		LARGE_INTEGER time;

		QueryPerformanceCounter(&time);


		currentTime = time.QuadPart;
		previousTime = currentTime;


		//단위 :초
		//float targetFrameTime = 60.0f;   ///
		setting.framerate
			= setting.framerate == 0.0f ? 60.0f : setting.framerate;
		float oneFrameTime = 1.0f / setting.framerate;


		while (!isQuit)
		{

			QueryPerformanceCounter(&time);
			currentTime = time.QuadPart;



			float deltaTime = static_cast<float>(currentTime - previousTime);

			deltaTime = deltaTime / static_cast<float>(freq.QuadPart);


			//고정프레임
			if (deltaTime >= oneFrameTime)
			{
				input->ProcessInput();


				BeginPlay();
				Tick(deltaTime);
				Draw();

				previousTime = currentTime;


				input->SavePreviousInputStates();



				//레벨에 요청된 추가/제거 처리
				if (mainLevel)
				{
					mainLevel->ProcessPendingActors();	
				}

			}
		}

		Shutdown();
	}

	void Engine::QuitEngine()
	{
		isQuit = true;
	}


	void Engine::SetNewLevel(Level* newLevel)
	{
		//기존 레벨 있는지 확인
		//있으면 기존레벨 제거
		//todo: 임시코드 레벨 전환할때는 바로 제거하면 안됨.
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}


		//레벨 설정.
		mainLevel = newLevel;
	}

	Engine& Engine::Get()
	{
		if (!instance)
		{
			//silent is violent.
			std::cout << "error : engine::get(). instance is null\n";
			__debugbreak();
		}
		return *instance;
	}

	

	bool Engine::IsScreenOut(const Vector2& other) const
	{
		int _width = setting.width;
		int _height = setting.height;

		// 하나라도 만족하면 화면 밖이므로 바로 true 반환
		return (other.x > _width || other.x < 0 ||
			other.y > _height || other.y < 0);
	}

	void Engine::Shutdown()
	{

		// todo : 정리 작업.
		std::cout << "endgine has been shutdown\n";


		//커서 끄기.
		Utill::TurnOnCursor();
	}

	void Engine::LoadSetting()
	{
		FILE* file = nullptr;
		fopen_s(&file, "../Config/setting.txt", "rt");

		if (!file)
		{
			fopen_s(&file, "./Config/setting.txt", "rt");

		}
		
		if (!file)
		{
			std::cout << "file open fail\n";

			__debugbreak();

			return;

		}



		char buffer[2048] = {};

		//파일에서 읽기.
		size_t readsize = fread(buffer, sizeof(char), 2048, file);

		//문자열 자르기 (파싱)
		char* nexttoken = nullptr;
		char* strtemp = strtok_s(buffer, "\n", &nexttoken);
		while (strtemp)
		{
			char header[10] = {};


			sscanf_s(strtemp, "%s", header, 10);
		

			if (strcmp(header, "framerate") == 0)
			{
				sscanf_s(strtemp, "framerate = %f", &setting.framerate);
			}
			else if (strcmp(header, "width") == 0)
			{
				sscanf_s(strtemp, "width = %d", &setting.width);
			}
			else if (strcmp(header, "height") == 0)
			{
				sscanf_s(strtemp, "height = %d", &setting.height);
			}

			//개행 문자로 문자열 분리.
			strtemp = strtok_s(nullptr, "\n", &nexttoken);
		}


		fclose(file);
	}

	void Engine::BeginPlay()
	{
		if (!mainLevel)
		{
			std::cout << "mainLevel is empty.\n";
			//로그를 남겨야함.
			return;
		}

		mainLevel->BeginPlay();
	}

	void Engine::Tick(float deltaTime)
	{

		//std::cout << "Ticking... Delta Time: " << deltaTime << " seconds. ::" <<
		//	"FPS" << 1.0f / deltaTime << "\n";



		//레벨에 이벤트 흘리기.
		if (!mainLevel)
		{
			std::cout << "rrror:engine::tick()\n";
			return;
		}
		mainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		//레벨에 이벤트 흘리기.
		if (!mainLevel)
		{
			std::cout << "rrror:engine::Draw()\n";
			return;
		}


		//레벨의 모든 엑터가 렌더 데이터를 제출
		mainLevel->Draw();


		//드로우 그리기 명혈 전달.
		renderer->Draw();
	}


}