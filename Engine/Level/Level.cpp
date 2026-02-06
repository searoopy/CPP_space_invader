#include "Level.h"
#include "Actor/Actor.h"

namespace wanted
{


	Level::Level()
	{
	}
	Level::~Level()
	{
		for (Actor*& actor : actors)
		{


			if (actor)
			{

				delete actor;
				actor = nullptr;

			}

		}

		actors.clear();
	}

	//게임 플레이 이벤트
	void Level::BeginPlay()
	{
		for (Actor* actor : actors)
		{
			//이미 beginplay 호출된 액터는 건너뛰기.
			if (actor->HasBeganPlay())
			{
				continue;
			}

			actor->BeginPlay();
		}
	}
	void Level::Tick(float deltaTime)
	{
		for (Actor* actor : actors)
		{
			actor->Tick(deltaTime);
		}
	}
	void Level::Draw()
	{
		//for (Actor* actor : actors)
		//{

		//	Actor* search = nullptr;
		//	for (Actor* otherActor : actors)
		//	{
		//		// 같은 액터는 비교 안함.
		//		if (actor == otherActor)
		//		{
		//			continue;
		//		}

		//		// 위치 비교.
		//		if (actor->GetPosition() == otherActor->GetPosition())
		//		{
		//			if (actor->GetSortOrder() < otherActor->GetSortOrder())
		//			{
		//				search = otherActor;
		//				break;
		//			}
		//			
		//		
		//		}
		//	}

		//	//같은 위치에 다른 액터가 있으면 안그림..
		//	if (search)
		//	{
		//		continue;
		//	}

		//	//그리기.
		//	actor->Draw();
		//	

		//}


		//엑터 순회 하면서 draw함수 호출
		for (Actor* const  actor : actors)
		{
			if (!actor->IsActive())
			{
				continue;
			}

			actor->Draw();
		}
	}

	void Level::AddNewActor(Actor* newActor)
	{
		//나중에 프레임 처리 고려해서 따로 추가 작업 해야함.
		pendingAddActors.emplace_back(newActor);

		newActor->SetOwner(this);

	}

	void Level::ProcessPendingActors()
	{
		for (int i = 0; i < static_cast<int>(actors.size()); )
		{
			if (actors[i]->DestroyRequested())
			{
				delete actors[i];
				actors.erase(actors.begin() + i);
				continue;
			}
			++i;

		}

		//추가 처리.

		if (pendingAddActors.size() == 0)
		{
			return;
		}
		for (Actor* const actor : pendingAddActors)
		{
			actors.emplace_back(actor);
		}

		pendingAddActors.clear();


	}


}