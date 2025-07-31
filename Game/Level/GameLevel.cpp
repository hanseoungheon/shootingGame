#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Utils/Utils.h"

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
	int index = Utils::Random(0, length - 1);
	int yPosition = Utils::Random(2, 10);
	AddActor(new Enemy(enemyType[index],yPosition));
}

void GameLevel::Render()
{
	super::Render();
}
