#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "RTTI.h"
#include <Windows.h>
//#include "Input.h"
//��ü �� �ؾ��ұ�?�� ����.
//��ġ ����.
//�ܼ� â�� �׸���(How?What?).
//������ �̺�Ʈ �Լ� ȣ��.
//BeginPlay/Tick/Draw.

//����
enum class Color : int
{
	Blue = 1,
	Green = 2,
	Red = 4,
	White = Red | Green | Blue,
	Intensity = 8,
};

//���漱��
class Level;

class Engine_API Actor : public RTTI
{
	friend class Level;

	RTTI_DECLARATIONS(Actor, RTTI);
public:
	Actor(const char image = ' ',Color color = Color::White,
		const Vector2& position = Vector2::Zero);
	virtual ~Actor();

	//�̺�Ʈ �Լ�

	//��ü �����ֱ�(LifeTime)�� 1���� ȣ��� (�ʱ�ȭ�� ������)
	virtual void BeginPlay();

	//������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�)
	virtual void Tick(float deltaTime);

	//�׸��� �Լ�
	virtual void Render();

	// BeginPlay ȣ�⿩�� Ȯ��.
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	void SetPosition(const Vector2& newPosition);
	Vector2 Position() const;

	//Sorting Order ����
	void SetSortingOrder(unsigned int sortingOrder);
	
	//���ʽ� ����
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	//���� ���� ��û
	void QuitGame();

private:
	//��ü�� ��ġ
	Vector2 position;

	//�׸� ��
	char image = ' ';

	//�ؽ�Ʈ ����
	Color color;

	//BeginPlay ȣ���� �Ǿ����� Ȯ��
	bool hasBeganPlay = false;

	// ���� ����
	unsigned int sortingOrder = 0;

	//���� ����.
	Level* owner = nullptr;
};