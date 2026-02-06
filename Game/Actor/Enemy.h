#pragma once

#include "Actor/Actor.h"
#include "Actor/Enemy.h"
#include "Utill/Timer.h"
#include "Utill/utill.h"

using namespace wanted;

class Enemy : public Actor
{
	RTTI_DECLARATIONS(Enemy, Actor)

		// 이동 방향 열거형
		enum class MoveDirection
	{
		None = -1,
		Left,
		Right,
	};

public:
	Enemy(const char* image = "(oOo)", float  dist = 0  , int level = 0 );
	Enemy(const char* image = "(oOo)", const Vector2& vec = Vector2(0,0), int level = 0);
	~Enemy();


	virtual void Tick(float deltaTime) override;


	//데미지 받았을때 함수.
	void OnDamaged();
	virtual void OnDestroy() override;

	void MoveCheck();

private:

	//MoveDirection direction = MoveDirection::None;

	float direction = 0.0f;

	//조ㅘ우 이동 처리
	float mx = 0.0f;
	float my = 0.0f;
	float moveSpeed = 0.0f;


	float m_distanceSum = 0;

	int level = 0; //단계가 0이 되면 분열 안함...

	//: 발사 타이머.
	Timer timer;

public:
	static int enemyCnt;

};

