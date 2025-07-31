#include "Enemy_Bullet.h"
#include "Engine.h"

Enemy_Bullet::Enemy_Bullet(const Vector2& position, float moveSpeed)
	: Actor("O",Color::Blue,position)
	, yPosition(static_cast<float>(position.y))
	, moveSpeed(moveSpeed)
{

}

void Enemy_Bullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//�Ʒ��� �̵� ó��
	yPosition = yPosition + moveSpeed * deltaTime;

	//ȭ�� ������� Ȯ��
	if (yPosition > Engine::Get().Height())
	{
		Destroy();
		return;
	}

	//����� �ʾ����� ��ġ ����
	SetPosition(Vector2(position.x, (int)yPosition));
}
