#pragma once
#pragma warning(disable: 4251)
#include "Common/Common.h";
#include "Common/RTTI.h"
#include <vector>

namespace wanted
{

	class Actor;

	class WANTED_API Level : public RTTI
	{

	RTTI_DECLARATIONS(Level, RTTI)



	public:
		Level();
		virtual ~Level();

		//게임 플레이 이벤트
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void AddNewActor(Actor* newActor);

		void ProcessPendingActors();

	protected:
		//액터 배열.
		std::vector<Actor*> actors;


		//실행 중에 추가 요청된 액터의 배열.
		std::vector<Actor*> pendingAddActors;

	};

}

