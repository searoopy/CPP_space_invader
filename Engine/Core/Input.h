#pragma once

#include "Common/Common.h"

namespace wanted
{
	class WANTED_API Input
	{
		friend class Engine;  ///엔진클래스에서만 인풋생성가능.

		//데이터.
		struct KeyState
		{
			bool isKeyDown = false;
			bool wasKeyDown = false;
		};

	private: //아무곳에서나 생성하는것 방지.
		Input();
		~Input();

	public:
		bool GetKeyDown(int keyCode);
		bool GetKeyUp(int keyCode);
		bool GetKeyKey(int keyCode);

		static Input& Get();


	private:
		void ProcessInput();
		void SavePreviousInputStates();

	private:

		//키 상태 저장용 배열.
		KeyState keyStates[255] = {};

		static Input* instance;
	};


}

