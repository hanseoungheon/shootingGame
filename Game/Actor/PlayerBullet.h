#pragma once
#include "Actor/Actor.h"


// cmd���� ��ǥ�� 1�������� ó��(������ �׳� ĭ int, float�� �ȴ�)
// ������ ó�� �������� Ȯ���ؾ��Ұ�-> �޼���ǥ���ΰ�?������ ��ǥ���ΰ�?
//
/*
* �÷��̾ �߻��ϴ� ź��
* - ȭ�� ���� �̵�
*	- �̵��ӷ�(�ӵ��� ����, �ӷ��� ��Į��), ������ ����
*	- 
*/
class PlayerBullet : public Actor
{
	RTTI_DECLARATIONS(PlayerBullet,Actor)

public:
	PlayerBullet(const Vector2& position);

	virtual void Tick(float deltaTime) override;



private:
	//�ʴ� 1ĭ ����.
	float movespeed = 30.0f;

	float yPosition = 0.0f;
};