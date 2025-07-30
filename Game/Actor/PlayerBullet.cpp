#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const Vector2& position)
	:Actor("M", Color::Green, position), yPosition((float)position.y)
{

}

void PlayerBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//이동 처리

	yPosition -= movespeed * deltaTime;
	//yPosition = yPosition - movespeed * deltaTime

	Vector2 position = Position();
	//position.y = position.y - 1.0f * movespeed * deltaTime;
	position.y = (int)yPosition;

	// 계산 값이 화면위 를 벗어나면 탄약 제거
	if (yPosition < 0.0f)
	{
		Destroy();
		return;
	}

	SetPosition(position);
}
