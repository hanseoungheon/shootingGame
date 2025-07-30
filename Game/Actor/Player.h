#pragma once
#include "Actor/Actor.h"
/*
* 기능
* - 좌우 이동 (키 입력 기반)
* - 탄약 발사(액터 생성) (키 입력 기반)
*	- 단발 Frie()
*	- 연사 FrieInterval(float deltaTime)
* 
*/
class Player : public Actor
{
	RTTI_DECLARATIONS(Player,Actor)

public:
	Player();

	virtual void Tick(float deltaTime) override;

private:
	void Fire();
	void FireInterval(float deltaTime);

private:
	//연사 간격 (단위: 초) 타이머 느낌
	float fireInterval = 0.15f;
};