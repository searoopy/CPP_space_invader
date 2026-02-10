#pragma once

#include "Actor/Actor.h"
#include "Utill/Timer.h"
#include "Utill/utill.h"

using namespace wanted;

class PlayerGui;

class Player : public Actor
{

	enum FireMode {
		None = -1,
		Normal = 0,
		Repeat = 1,
		MAX
	};

	RTTI_DECLARATIONS(Player, Actor)



public:
	Player();
	~Player();

	void InitData();

	inline void SetGUI(PlayerGui* pGui) {
		mpGui = pGui;
	}

private:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override ;

	// 맵 이동 루프.
	void MoveCheck();
	
	void CheckBulletFirePos();
	//void MoveLeft();


	void Fire();


	void FireInterval();


	//발사 가능여부 확인 함수.
	bool CanShot();

public:
	void SetBulletCnt(int val);
	void AddBulletCnt(int val);

	void OnDestroy() override;

private:
	PlayerGui* mpGui = nullptr;

	FireMode fireMode = FireMode::None;

	float elapsedTime = 0.0f;

	float fireInterval = 0.2f;


	//타이머변수
	Timer timer;


	const float moveSetSpeed = 1000;
	const float moveSlideSpeed = 15.1f;

	float moveSpeed = 0;
	float direction = 0;
	float rotSpeed = 155.5f;

	float mx;
	float my;

	char* image_cur = nullptr;

	char* image1 = nullptr;
	char* image2 = nullptr;
	char* image3 = nullptr;
	char* image4 = nullptr;
	char* image5 = nullptr;
	char* image6 = nullptr;
	char* image7 = nullptr;
	char* image8 = nullptr;

	Vector2 bulletFirePos;


	int bulletCnt = 0;



};

