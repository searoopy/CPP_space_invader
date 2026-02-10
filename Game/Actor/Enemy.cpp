#include "Enemy.h"
#include "Utill//utill.h"
#include "Engine/Engine.h"
#include "Actor/EnemyBullet.h"
#include "Level/GameLevel.h"
#include "Math/Vector2.h"
#include <math.h>
#include "Actor/EnemySpawner.h"

int Enemy::enemyCnt = 0;

Enemy::Enemy(const char* image, float dist, int level)
	: super(image) , level(level)
{
	enemyCnt += 1;
	//랜덤
	//moveSpeed = Utill::RandomRange(1, 5);
	moveSpeed = Utill::RandomRange(10,11);

	int randomDir = Utill::RandomRange(0, 360);

	int screenCenterx = Engine::Get().GetWidthCenter();
	int screenCentery = Engine::Get().GetHeightCenter();

	mx = screenCenterx + cos(Utill::to_radian(randomDir)) * dist ;
	my = screenCentery + sin(Utill::to_radian(randomDir)) * dist ;

	int dx = screenCenterx - mx;
	int dy = screenCentery - my;

	// 아크탄젠트로 라디안 각도 구하기
	float radian = std::atan2(dy, dx);

	// 라디안을 일반 각도(Degree)로 변환
	float degree = radian * (180.0f / 3.14);

	direction = Utill::WrapAngle(degree +180 );

	SetPosition(Vector2(mx, my));
	// 발사 타이머 목표 시간 설정.
	timer.SetTargetTime(Utill::RandomRange(1.0f, 3.0f));

	//

}

Enemy::Enemy(const char* image, const Vector2& vec, int level)
	: super(image), level(level)
{

	enemyCnt += 1;
	//랜덤
	//moveSpeed = Utill::RandomRange(1, 5);
	moveSpeed = Utill::RandomRange(5, 7);
	int randomDir = Utill::RandomRange(0, 360);
	int screenCenterx = Engine::Get().GetWidthCenter();
	int screenCentery = Engine::Get().GetHeightCenter();
	mx = vec.x;
	my = vec.y;

	direction = randomDir;
	SetPosition(Vector2(mx, my));
	// 발사 타이머 목표 시간 설정.
	timer.SetTargetTime(Utill::RandomRange(1.0f, 3.0f));


}

Enemy::~Enemy()
{


	enemyCnt -= 1;



}


void Enemy::MoveCheck()
{
	int width2 = Engine::Get().GetWidth();
	int height2 = Engine::Get().GetHeight();

	if (mx - width > width2)
	{
		mx = 0 - width;

	}
	else if (mx < -width)
	{
		mx = width2 - 1;

	}

	if (my - height > height2)
	{
		my = 0 -height;

	}
	else if (my < -height)
	{
		my = height2 - 1;
	}

}

void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//이동 처리.
	//float dir = direction == MoveDirection::Left ? -1.0f : 1.0f;
	mx += cos(direction) * moveSpeed  * deltaTime;
	my += sin(direction) * moveSpeed  * deltaTime;

	
	//m_distanceSum = startPos.GetDistance(Vector2(mx, my));
 
 	MoveCheck();

	/*
	if( Engine::Get().IsScreenOut( position ) == true )
	{
		Destroy();
		return ;
	}
	*/
	if (m_distanceSum > 30)
	{
		Destroy();
		return;
	}




	//위치 설정.
	SetPosition(Vector2(int(mx), (int)my));


	//발사 타이머...
	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
	{
		return;
	}

	timer.Reset();


	/*
	//적 탄약 발사.
	//todo: 적 탄약
	GetOwner()->AddNewActor(new EnemyBullet(
		Vector2(position.x + width / 2, position.y),
		Utill::RandomRange(10.0f, 20.0f)
	));
	*/

}

void Enemy::OnDamaged()
{

	Destroy();

	// todo: 이펙트 생성...


}

void Enemy::OnDestroy()
{
	

	//분열..
	if (level > 0)
	{
		level -= 1;
		GetOwner()->AddNewActor(new Enemy(enemyType[level], Vector2(position.x, position.y), level));

		GetOwner()->AddNewActor(new Enemy(enemyType[level], Vector2(position.x, position.y), level));
	}
}
