#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Actor/PlayerBullet.h"
#include "Actor/Enemy_Bullet.h"
#include "Engine.h"
#include "Utils/Utils.h"
#include <iostream>
//�� ������ �� ����� ���� ��.
static const char* enemyType[] =
{
	"<|o|>",
	"ccTcc",
	"oO@Oo",
	"<=-=>",
	">-|-<",
};

GameLevel::GameLevel()
{
	AddActor(new Player());
	
	//�׽�Ʈ��
	AddActor(new Enemy());

	//Ÿ�̸� ����
	enemySpawnTimer.SetTargetTime(Utils::RandomFloat(2.0f,4.0f));
}

GameLevel::~GameLevel()
{
}

void GameLevel::BeginPlay()
{
	super::BeginPlay();
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	SpawnEnemies(deltaTime);

	ProcessCollisionPlayerBulletAndEnemy();
	ProcessCollisionPlayerAndEnemyBullet();
}

void GameLevel::SpawnEnemies(float deltaTime)
{
	//�� ����.
	enemySpawnTimer.Tick(deltaTime);

	//Ÿ�� �ƿ� Ȯ��
	if (!enemySpawnTimer.IsTimeout())
	{
		return;
	}

	//Ÿ�̸� ����
	enemySpawnTimer.Reset();
	enemySpawnTimer.SetTargetTime(Utils::RandomFloat(2.0f, 4.0f));

	//�� ����
	static int length = sizeof(enemyType) / sizeof(enemyType[0]);

	//�迭 �ε��� �������� ���ϱ�
	int index = Utils::Random(0, length - 1);

	//������ġ y�� ����
	int yPosition = Utils::Random(2, 10);
	AddActor(new Enemy(enemyType[index], yPosition));
}

void GameLevel::Render()
{
	super::Render();

	if (isPlayerDead)
	{
		Utils::SetConsolePosition(Vector2(playerDeadPosition.x, playerDeadPosition.y - 1));
		std::cout << "   .   ";

		Utils::SetConsolePosition(Vector2(playerDeadPosition.x, playerDeadPosition.y));
		std::cout << " .  .  .";

		Utils::SetConsolePosition(Vector2(playerDeadPosition.x, playerDeadPosition.y + 1));
		std::cout << "..:V:..";

		Utils::SetConsolePosition(Vector2(playerDeadPosition.x, playerDeadPosition.y + 2));
		std::cout << "Game Over!";

		//��� ����
		Sleep(2000);
		Engine::Get().Quit();
	}

	//���ھ� �����ֱ�.
	char buffer[20] = {};
	sprintf_s(buffer, 20, "Score: %d", score);

	//���
	Utils::SetConsolePosition(Vector2(1,Engine::Get().Height() + 2));
	Utils::SetConsoleTextColor(Color::White);
	std::cout << buffer;

}

void GameLevel::ProcessCollisionPlayerBulletAndEnemy()
{
	std::vector<PlayerBullet*> bullets;
	std::vector<Enemy*> enemies;

	//���͵� �˻��ϱ�
	for (Actor* const actor : actors)
	{
		PlayerBullet* bullet = actor->As<PlayerBullet>();

		if (bullet)
		{
			bullets.emplace_back(bullet);
			continue;
		}

		Enemy* enemy = actor->As<Enemy>();
		
		if (enemy)
		{
			enemies.emplace_back(enemy);
		}
	}

	//���� ó�� (���ص� ��Ȳ Ȯ��)
	if (bullets.size() == 0 || enemies.size() == 0)
	{
		return;
	}


	for (auto* bullet : bullets)
	{
		for (auto* enemy : enemies)
		{
			//�� ���Ͱ� ���� ���ƴ��� Ȯ��	
   			if (bullet->TestIntersect(enemy))
			{
				enemy->Destroy();
				bullet->Destroy();

				++score;
				continue;
			}
		}
	}

}

void GameLevel::ProcessCollisionPlayerAndEnemyBullet()
{
	Player* player = nullptr;
	std::vector<Enemy_Bullet*> bullets;

	for (Actor* const actor : actors)
	{
		Enemy_Bullet* bullet = actor->As<Enemy_Bullet>();
		if (bullet)
		{
			bullets.emplace_back(bullet);
			continue;
		}

		if (!player)
		{
			player = actor->As<Player>();
		}
	}

	if (bullets.size() == 0 || !player)
	{
		return;
	}

	for (auto* bullet : bullets)
	{
		if (player->TestIntersect(bullet))
		{
			//���� ó�� (���� ����)
			isPlayerDead = true;

			playerDeadPosition.x = player->Position().x + player->Width() / 2;
			playerDeadPosition.y = player->Position().y;

			player->Destroy();
			bullet->Destroy();
			break;
		}
	}
}
