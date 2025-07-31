#pragma once
#include "Actor/Actor.h"


/*
* �Ʒ��������� �̵�
* �̵� �����⸦ ������ �÷��̾�� �浹 or ȭ���� ����� ���ŵ�
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

	//�ε� �Ҽ������� �̵� ��ġ�� ����Ҷ� ����� ����
	float yPosition = 0.0f;
};