#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Actor/PlayerBullet.h"
#include "Actor/Enemy_Bullet.h"
#include "Engine.h"
#include "Utils/Utils.h"
#include <iostream>
//적 생성할 때 사용할 글자 값.
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
	
	//테스트용
	AddActor(new Enemy());

	//타이머 설정
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
	//적 생성.
	enemySpawnTimer.Tick(deltaTime);

	//타임 아웃 확인
	if (!enemySpawnTimer.IsTimeout())
	{
		return;
	}

	//타이머 정리
	enemySpawnTimer.Reset();
	enemySpawnTimer.SetTargetTime(Utils::RandomFloat(2.0f, 4.0f));

	//적 생성
	static int length = sizeof(enemyType) / sizeof(enemyType[0]);

	//배열 인덱스 랜덤으로 구하기
	int index = Utils::Random(0, length - 1);

	//생성위치 y축 랜덤
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

		//잠깐 정지
		Sleep(2000);
		Engine::Get().Quit();
	}

	//스코어 보여주기.
	char buffer[20] = {};
	sprintf_s(buffer, 20, "Score: %d", score);

	//출력
	Utils::SetConsolePosition(Vector2(1,Engine::Get().Height() + 2));
	Utils::SetConsoleTextColor(Color::White);
	std::cout << buffer;

}

void GameLevel::ProcessCollisionPlayerBulletAndEnemy()
{
	std::vector<PlayerBullet*> bullets;
	std::vector<Enemy*> enemies;

	//액터들 검사하기
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

	//예외 처리 (안해도 상황 확인)
	if (bullets.size() == 0 || enemies.size() == 0)
	{
		return;
	}


	for (auto* bullet : bullets)
	{
		for (auto* enemy : enemies)
		{
			//두 액터가 서로 겹쳤는지 확인	
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
			//죽음 처리 (게임 종료)
			isPlayerDead = true;

			playerDeadPosition.x = player->Position().x + player->Width() / 2;
			playerDeadPosition.y = player->Position().y;

			player->Destroy();
			bullet->Destroy();
			break;
		}
	}
}
