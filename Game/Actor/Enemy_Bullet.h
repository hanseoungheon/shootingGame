#pragma once
#include "Actor/Actor.h"


/*
* 아래방향으로 이동
* 이동 빠르기를 가지며 플레이어와 충돌 or 화면을 벗어나면 제거됨
* 
*/
class Enemy_Bullet : public Actor
{
	RTTI_DECLARATIONS(Enemy_Bullet,Actor)

public:
	Enemy_Bullet(const Vector2& position, float moveSpeed = 15.0f);

	virtual void Tick(float deltaTime) override;

private:
	float moveSpeed = 0.0f;

	//부동 소수점으로 이동 위치를 계산할때 사용할 변순
	float yPosition = 0.0f;
};