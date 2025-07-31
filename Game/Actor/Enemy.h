#pragma once

#include "Actor/Actor.h"
#include "Utils/Timer.h"
/*
* 이동 패턴(좌우)
* - 오른쪽에서 태어났으면 왼쪽으로 이동
* - 왼쪽에서 태어났으면 오른쪽으로 이동
*/
class Enemy : public Actor
{
	//이동 방향 열거형
	enum class MoveDirection
	{
		None = -1,
		Left,
		Right,
		Length
	};

	RTTI_DECLARATIONS(Enemy,Actor)

public:
	Enemy(const char* image = "<-=->", int yPosition = 5);

	virtual void Tick(float deltaTime) override;

private:

	// 이동에 필요한 변수
	//이동방향
	MoveDirection direction = MoveDirection::None;

	//속력을 고려한 이동 위치 계산을 위한 float 변수
	float xPosition = 0.0f;

	Timer timer;

	//이동 빠르기
	float movespeed = 5.0f;

	////타이머 계산을 위한 변수
	////1.경과 시간 변수
	//float elaspedTime = 0.0f;
	////2.목표 시간 값
	//float targetTime = 0.0f;
};