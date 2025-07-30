#pragma once
#include "Actor/Actor.h"
/*
* ���
* - �¿� �̵� (Ű �Է� ���)
* - ź�� �߻�(���� ����) (Ű �Է� ���)
*	- �ܹ� Frie()
*	- ���� FrieInterval(float deltaTime)
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
	//���� ���� (����: ��) Ÿ�̸� ����
	float fireInterval = 0.15f;
};