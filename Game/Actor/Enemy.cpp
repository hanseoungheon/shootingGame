#include "Enemy.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Actor/Enemy_Bullet.h"

Enemy::Enemy(const char* image,int yPosition)
	: Actor(image)
{
	int random = Utils::Random(1, 10);

	if (random % 2 == 0)
	{
		//ȭ�� ������ ������ �����ǵ��� ��ġ / �̵����� ����
		direction = MoveDirection::Left;
		xPosition = static_cast<float>(Engine::Get().Width()) - width;
	}
	else
	{
		//ȭ�� ���� ������ �����ǵ��� ��ġ
		direction = MoveDirection::Right;
		xPosition = 0.0f;
	}

	position.x = static_cast<int>(xPosition);
	position.y = yPosition;

	timer.SetTargetTime(Utils::RandomFloat(1.0f, 3.0f));
}

void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//�̵� (�¿�)
	float dir = direction == MoveDirection::Left ? -1.0f : 1.0f;

	//�̵� ó�� (���ӵ� �, �̵��Ÿ� = �ӵ� x �ð�; �ӵ�->������ x����)
	xPosition = xPosition + (movespeed * dir) * deltaTime;

	if (xPosition < 0.0f || (int)xPosition > Engine::Get().Width() - width)
	{
		//ȭ�鿡�� ����� ���� ����
		Destroy();
		return;
	}
	
	//����� �ʾҴٸ�

	SetPosition(Vector2((int)xPosition, position.y));

	//�ð��� �� �Ŀ� ź�� �߻�
	timer.Tick(deltaTime);

	if (!timer.IsTimeout())
	{
		return;
	}

	
	//���� �ڵ�--------------------------------------------
	//elaspedTime += deltaTime;

	////�߻� ���� �ð���ŭ ����ߴ��� Ȯ��.
	//if (elaspedTime < targetTime)
	//{
	//	return;
	//}
	//------------------------------------------------------

	//�߻�
	//�� ź�� ���� ��û
	owner->AddActor(new Enemy_Bullet(
		Vector2(position.x + width / 2, position.y + 1),
		Utils::RandomFloat(10.0f, 20.0f))
	);
//Ÿ�̸� ���� ����
	timer.Reset();
	timer.SetTargetTime(Utils::RandomFloat(1.0f, 3.0f));

	//���� �ڵ�--------------------------------------------
	//elaspedTime = 0.0f;
	//targetTime = Utils::RandomFloat(1.0f, 3.0f);
	//------------------------------------------------------
	

}