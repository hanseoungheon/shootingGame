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
		//화면 오른쪽 끝에서 생성되동록 위치 / 이동방향 설정
		direction = MoveDirection::Left;
		xPosition = static_cast<float>(Engine::Get().Width()) - width;
	}
	else
	{
		//화면 왼쪽 끝에서 생성되도록 위치
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

	//이동 (좌우)
	float dir = direction == MoveDirection::Left ? -1.0f : 1.0f;

	//이동 처리 (동속도 운동, 이동거리 = 속도 x 시간; 속도->빠르기 x방향)
	xPosition = xPosition + (movespeed * dir) * deltaTime;

	if (xPosition < 0.0f || (int)xPosition > Engine::Get().Width() - width)
	{
		//화면에서 벗어나면 액터 제거
		Destroy();
		return;
	}
	
	//벗어나지 않았다면

	SetPosition(Vector2((int)xPosition, position.y));

	//시간을 잰 후에 탄약 발사
	timer.Tick(deltaTime);

	if (!timer.IsTimeout())
	{
		return;
	}

	
	//기존 코드--------------------------------------------
	//elaspedTime += deltaTime;

	////발사 간격 시간만큼 경과했는지 확인.
	//if (elaspedTime < targetTime)
	//{
	//	return;
	//}
	//------------------------------------------------------

	//발사
	//적 탄약 생성 요청
	owner->AddActor(new Enemy_Bullet(
		Vector2(position.x + width / 2, position.y + 1),
		Utils::RandomFloat(10.0f, 20.0f))
	);
//타이머 변수 정리
	timer.Reset();
	timer.SetTargetTime(Utils::RandomFloat(1.0f, 3.0f));

	//기존 코드--------------------------------------------
	//elaspedTime = 0.0f;
	//targetTime = Utils::RandomFloat(1.0f, 3.0f);
	//------------------------------------------------------
	

}