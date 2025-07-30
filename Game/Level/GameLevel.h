#pragma once
#include "Level/Level.h"


/*
* ���� ������ å��
* - ������: �ణ�� �������� �����ؼ� ���� �ð����� �� ����
* - �浹ó��: �÷��̾� - �� ź�� ������ �浹/ ��-�÷��̾� ź���� �浹 ó��(AAAB)
* - ��������: �÷��̾ ���� ���ָ� 1���� ȹ����.
* - ��������: �÷��̾ ������ ���� ����.
* - ���Ӹ�ǥ: �����̹�? maybe.
*/

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

private:
	//std::vector<Actor*> player;

};