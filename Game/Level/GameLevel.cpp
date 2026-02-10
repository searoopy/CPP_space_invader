#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/EnemySpawner.h"
#include "Actor/PlayerBullet.h"
#include "Actor/EnemyBullet.h"
#include "Actor/Enemy.h"
#include "Actor/PlayerGui.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Actor/BulletItem.h"

GameLevel::GameLevel()
{
	// Player 액터 추가.
	m_player = new Player();
	AddNewActor(m_player);

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
	ProcessCollisionPlayerAndEnemy();
}

void GameLevel::ProcessCollisionPlayerAndEnemy()
{
	Player* player = nullptr;
	std::vector<Enemy*> enemies;
	std::vector<BulletItem*> items;

	for (Actor* const actor : actors)
	{

		if (!player && actor->IsTypeOf<Player>())
		{
			player = actor->As<Player>();
			continue;
		}

		if (actor->IsTypeOf<Enemy>())
		{
			enemies.emplace_back(actor->As<Enemy>());
			continue;
		}

		if (actor->IsTypeOf<BulletItem>())
		{

			items.emplace_back(actor->As<BulletItem>());
		}

	}

	if (items.size() > 0)
	{
		for (Actor* const item : items)
		{
			if (item->TestIntersect(player))
			{
				BulletItem* pp = reinterpret_cast<BulletItem*>(item);
				player->AddBulletCnt( pp->GetBulletCnt() );

				item->Destroy();
				
			}
		}
	}


	if (enemies.size() == 0 || !player)
	{
		return;
	}


	//충돌 판정
	for (Actor* const enemy : enemies)
	{
		if (enemy->TestIntersect(player))
		{
			//player->Destroy();
			//enemy->OnDamaged();

			Game::Get().ToggleMenu();


			break;
		}
	}

}

void GameLevel::Reset_Level()
{

	std::vector<Enemy*> enemies;


	for (Actor* const actor : actors)
	{



		if (actor->IsTypeOf<Enemy>())
		{
			enemies.emplace_back(actor->As<Enemy>());

		}

	}

	for (Actor* const enemy : enemies)
	{
		enemy->Destroy_only();
	}


	if (m_player)
		m_player->InitData();
	PlayerGui::Get().initScore();

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

				PlayerGui::Get().addScore(1);

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
