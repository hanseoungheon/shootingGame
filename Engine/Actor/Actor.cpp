#include "Actor.h"
#include <Windows.h>
#include <iostream>
#include "Engine.h"
#include "Utils/Utils.h"

Actor::Actor(const char* image,Color color, const Vector2& position) :color(color) , position(position)
{
	//���ڿ� ����
	width = (int)strlen(image);

	//�޸� �Ҵ�
	this->image = new char[width + 1];

	//���ڿ� ����
	strcpy_s(this->image, width + 1,image);
}
Actor::~Actor()
{
	//�޸�����
	SafeDeleteArray(image);
}
//�̺�Ʈ �Լ�

//��ü �����ֱ�(LifeTime)�� 1���� ȣ��� (�ʱ�ȭ�� ������)
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

//������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�)
void Actor::Tick(float deltaTime)
{

}

//�׸��� �Լ�
void Actor::Render()
{
	//Ŀ�� ��ġ �� ����
	//COORD coord; 
	//coord.X = (short)position.x;
	//coord.Y = (short)position.y;

	//Ŀ���̵�
	Utils::SetConsolePosition(position);

	//���� ����
	Utils::SetConsoleTextColor(color);

	//�׸���
	std::cout << image;
}

void Actor::SetPosition(const Vector2& newPosition)
{
	if (position == newPosition)
	{
		return;
	}
	//static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	////Ŀ�� ��ġ �� ����
	//COORD coord;
	//coord.X = (short)position.x;
	//coord.Y = (short)position.y;

	//���� ��ġ Ȯ��
	Vector2 direction = newPosition - position; //�� ��ġ - ������ġ = ���⺤��

	position.x = (direction.x >= 0) ? position.x : position.x + width - 1;

	//Ŀ���̵�
	Utils::SetConsolePosition(position);

	//���ڿ� ���� ����ؼ� ���� ��ġ Ȯ���ؾ���.
	std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}

int Actor::Width() const
{
	return width;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

void Actor::Destroy()
{
	//���� ��û �Ǿ��ٰ� üũ
	isExpired = true;
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}
