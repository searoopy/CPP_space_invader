#include "EnemySpawner.h"
#include "Actor/Enemy.h"
#include "Utill/Timer.h"
#include "Utill/utill.h"
#include "Level/GameLevel.h"
// 적 생성할 때 사용할 글자 값.
// 여기에서 static은 private.
//static const char* enemyType[] =
//{
//	";:^:;",
//	"zZwZz",
//	"oO@Oo",
//	"<-=->",
//	")qOp(",
//};


EnemySpawner::EnemySpawner()
{


}

void EnemySpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	timer.Tick(deltaTime);

	//timer.
	if(!timer.IsTimeOut() )
	{
		return;
	}


	SpawnEnemy(deltaTime);
}

void EnemySpawner::SpawnEnemy(float deltaTime)
{
	timer.Reset();

	static int length
		= sizeof(enemyType) / sizeof(enemyType[0]);


	//랜덤 인덱스
	int index = Utill::RandomRange(0, length - 1);

	int dist = Utill::RandomRange(30, 32);


	if (Enemy::enemyCnt < 3) 
	{

		GetOwner()->AddNewActor(new Enemy(enemyType[index], dist,index));
	}


}


