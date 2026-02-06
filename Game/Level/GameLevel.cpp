#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/EnemySpawner.h"
#include "Actor/PlayerBullet.h"
#include "Actor/EnemyBullet.h"
#include "Actor/Enemy.h"
#include "Actor/PlayerGui.h"
#include "Engine/Engine.h"

GameLevel::GameLevel()
{
	// Player 액터 추가.
	Player* p = new Player();
	AddNewActor(p);
	AddNewActor(new EnemySpawner());

	int _x = Engine::Get().GetWidth() - 10;
	int _y = Engine::Get().GetHeight() - 1;
	PlayerGui* pGUI = new PlayerGui(Vector2(_x, _y));
	AddNewActor(pGUI) ;
	//p->SetGUI(pGUI);

}

GameLevel::~GameLevel()
{
}

void GameLevel::Tick(float dtime)
{
	super::Tick(dtime);

	ProcessCollisionPlayerBulletAndEnemy();
	ProcessCollisionPlayerAndEnemyBullet();
}



void GameLevel::ProcessCollisionPlayerBulletAndEnemy()
{
	std::vector<Actor*> bullets;
	std::vector<Enemy*> enemies;

	//액터 필터링.
	for (Actor* const actor : actors)
	{
		if (actor->IsTypeOf<PlayerBullet>())
		{
			bullets.emplace_back(actor);
			continue;
		}

		if (actor->IsTypeOf<Enemy>())
		{
			enemies.emplace_back(actor->As<Enemy>());

		}
	}
	if (bullets.size() == 0 || enemies.size() == 0)
	{

		return;
	}

	//충돌 판정.
	for (Actor* const bullet : bullets)
	{
		for (Actor* const enemy : enemies)
		{
			if (bullet->TestIntersect(enemy))
			{
				enemy->Destroy();
				bullet->Destroy();

				continue;
			}

		}
	}


}

void GameLevel::ProcessCollisionPlayerAndEnemyBullet()
{
	Player* player = nullptr;
	std::vector<Actor*> bullets;

	for (Actor* const actor : actors)
	{
		if (!player && actor->IsTypeOf<Player>())
		{
			player = actor->As<Player>();
			continue;
		}

		if ( actor->IsTypeOf<EnemyBullet>())
		{
			bullets.emplace_back(actor->As<EnemyBullet>());
			
		}

	}

	if (bullets.size() == 0 || !player)
	{
		return;
	}


	//충돌 판정
	for (Actor* const bullet : bullets)
	{
		if (bullet->TestIntersect(player))
		{
			player->Destroy();
			bullet->Destroy();
			break;
		}
	}

}
