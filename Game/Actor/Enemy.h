#pragma once

#include "Actor/Actor.h"
#include "Utils/Timer.h"
/*
* �̵� ����(�¿�)
* - �����ʿ��� �¾���� �������� �̵�
* - ���ʿ��� �¾���� ���������� �̵�
*/
class Enemy : public Actor
{
	//�̵� ���� ������
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

	// �̵��� �ʿ��� ����
	//�̵�����
	MoveDirection direction = MoveDirection::None;

	//�ӷ��� ����� �̵� ��ġ ����� ���� float ����
	float xPosition = 0.0f;

	Timer timer;

	//�̵� ������
	float movespeed = 5.0f;

	////Ÿ�̸� ����� ���� ����
	////1.��� �ð� ����
	//float elaspedTime = 0.0f;
	////2.��ǥ �ð� ��
	//float targetTime = 0.0f;
};