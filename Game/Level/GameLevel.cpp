#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Utils/Utils.h"

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
	int index = Utils::Random(0, length - 1);
	int yPosition = Utils::Random(2, 10);
	AddActor(new Enemy(enemyType[index],yPosition));
}

void GameLevel::Render()
{
	super::Render();
}
