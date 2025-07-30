#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const Vector2& position)
	:Actor("M", Color::Green, position), yPosition((float)position.y)
{

}

void PlayerBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//�̵� ó��

	yPosition -= movespeed * deltaTime;
	//yPosition = yPosition - movespeed * deltaTime

	Vector2 position = Position();
	//position.y = position.y - 1.0f * movespeed * deltaTime;
	position.y = (int)yPosition;

	// ��� ���� ȭ���� �� ����� ź�� ����
	if (yPosition < 0.0f)
	{
		Destroy();
		return;
	}

	SetPosition(position);
}
