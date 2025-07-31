#pragma once
#include "Level/Level.h"
#include "Utils/Timer.h"
#include "Math/Vector2.h"

/*
* ���� ������ å��
* - ������: �ణ�� �������� �����ؼ� ���� �ð����� �� ����
* - �浹ó��: �÷��̾� - �� ź�� ������ �浹/ ��-�÷��̾� ź���� �浹 ó��(AAAB)
* - ��������: �÷��̾ ���� ���ָ� 1���� ȹ����.
* - ��������: �÷��̾ ������ ���� ����.
* - ���Ӹ�ǥ: �����̹�? maybe.
*/

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	void SpawnEnemies(float deltaTime);
	virtual void Render() override;

private:
	void ProcessCollisionPlayerBulletAndEnemy();
	void ProcessCollisionPlayerAndEnemyBullet();
private:
	//std::vector<Actor*> player;

	//�� ���� �� �ð� ����� ���� Ÿ�̸�
	Timer enemySpawnTimer;

	//���� ����
	int score = 0;

	//�÷��̾��� ����ó���� ���� ����
	bool isPlayerDead = false;

	Vector2 playerDeadPosition;
};