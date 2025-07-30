#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "RTTI.h"
#include <Windows.h>
#include "Math/Color.h"
//#include "Input.h"
//��ü �� �ؾ��ұ�?�� ����.
//��ġ ����.
//�ܼ� â�� �׸���(How?What?).
//������ �̺�Ʈ �Լ� ȣ��.
//BeginPlay/Tick/Draw.

//����

//���漱��
class Level;

class Engine_API Actor : public RTTI
{
	friend class Level;

	RTTI_DECLARATIONS(Actor, RTTI);
public:
	Actor(const char* image = " ", Color color = Color::White,
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

	//���ڿ� ���� ��ȯ
	int Width() const;
	
	//Sorting Order ����
	void SetSortingOrder(unsigned int sortingOrder);
	
	//���ʽ� ����
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	//��ü ���� �Լ�
	void Destroy();

	//���� ���� ��û
	void QuitGame();

protected:
	//��ü�� ��ġ
	Vector2 position;

	//�׸� ��
	char* image = nullptr;

	//���ڿ� ����
	int width = 0;


	//�ؽ�Ʈ ����
	Color color;

	//BeginPlay ȣ���� �Ǿ����� Ȯ��
	bool hasBeganPlay = false;

	// ���� ����
	unsigned int sortingOrder = 0;

	// ���Ͱ� Ȱ�� ����
	bool isActive = true;

	//���� ��û�ƴ��� �˷��ִ� ����
	bool isExpired = false;

	//���� ����.
	Level* owner = nullptr;
};