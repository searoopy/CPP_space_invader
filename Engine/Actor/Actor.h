#pragma once
#include "Common/Common.h";
#include "Common/RTTI.h"
#include "Math/Vector2.h"
#include "Math/color.h"

namespace wanted
{ 

	class Level;

	class WANTED_API Actor : public RTTI
	{


		RTTI_DECLARATIONS(Actor, RTTI)

	public:
		Actor(const char* image = " " ,
			const Vector2& position = Vector2::Zero,
			Color color = Color::White);
		virtual ~Actor();

		//게임 플레이 이벤트
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();


		//삭제 요청 함수
		void Destroy();

		//삭제가 될떄 호출될 이벤트 함수
		virtual void OnDestroy();

		//
		void QuitGame();
	
		bool TestIntersect(const Actor* const other);

		//위치 변경 및 읽기 함수.
		void SetPosition(const Vector2& newPosition);
		inline Vector2 GetPosition() const { return position; }

		//오너십 추가/읽기 함수.
		inline void SetOwner(Level* newOwner) { owner = newOwner; }
		inline Level* GetOwner() const { return owner; }

		//Getter.	
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		bool IsActive() const
		{
			return isActive && !destroyRequested;
		}

		inline bool DestroyRequested() const
		{
			return destroyRequested;
		}

		inline int GetSortOrder() const
		{
			return sortingorder;
		}

		inline int GetWidth() const { return width; }

	protected:

		//이미 beginPlay 이벤트를받았는지 여부
		bool hasBeganPlay = false;


		bool isActive = true;

		//현재 프레임에 삭제요청 받았는지
		bool destroyRequested = false;

		char* image = nullptr;

		Color color = Color::White;

		//오너쉽(ownership).
		Level* owner = nullptr;

		int sortingorder = 0;

		int width = 0;
		int height = 0;

		Vector2 position;
		Vector2 startPos;

	};

}
