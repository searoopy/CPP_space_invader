
#include "PlayerBullet.h"
#include "Utill/utill.h"
#include "Engine/Engine.h"
#include "PlayerGui.h"

PlayerBullet::PlayerBullet(const Vector2& position, float dir)
	: super("@", position, Color::Blue) , direction(dir), moveSpeed(50.0f)
{

	//direction = 270;
	//direction = Utill::WrapAngle(direction);
	mx = position.x;
	my = position.y;
}


PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	mx += cos(Utill::to_radian(direction)) * moveSpeed * deltaTime;
	my += sin(Utill::to_radian(direction)) * moveSpeed * deltaTime;

	//float yPosition = GetPosition().y;

	//yPosition -= moveSpeed * deltaTime;

	position.x = static_cast<int>(mx);
	position.y = static_cast<int>(my);

	//if (yPosition < 0)
	if(Engine::Get().IsScreenOut(position) == true)
	{
		OutputDebugString(L"destroy bullet.\n");
		Destroy();
		return;

	}

	//Vector2 newPos = GetPosition();
	//newPos.y = (int)yPosition;
	

	//위치 갱신.
	//SetPosition(newPos);


	
}