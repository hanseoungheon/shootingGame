#pragma once
#include "Actor/Actor.h"


// cmd에서 좌표는 1유닛으로 처리(유닛은 그냥 칸 int, float는 안댐)
// 엔진을 처음 만났을떄 확인해야할것-> 왼손좌표계인가?오른손 좌표계인가?
//
/*
* 플레이어가 발사하는 탄약
* - 화면 위로 이동
*	- 이동속력(속도는 백테, 속력은 스칼라), 방향은 윗쪽
*	- 
*/
class PlayerBullet : public Actor
{
	RTTI_DECLARATIONS(PlayerBullet,Actor)

public:
	PlayerBullet(const Vector2& position);

	virtual void Tick(float deltaTime) override;



private:
	//초당 1칸 간다.
	float movespeed = 30.0f;

	float yPosition = 0.0f;
};