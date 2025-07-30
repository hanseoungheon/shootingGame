#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{

}
Level::~Level()
{
	for (Actor* actor : actors)
	{
		////null Ȯ�� �� ���� ����
		//if (actor)
		//{
		//	//���� �� �޸� ����.
		//	delete actor;
		//	actor = nullptr;
		//}
		SafeDelete(actor);
	}

	//std::vector ����
	actors.clear();
}

// ������ ���͸� �߰��� �� ���
void Level::AddActor(Actor* newActor)
{
	//����ó��(�ߺ� ���� Ȯ��) �ʼ�

	//push_back , emplace_back : �迭 �� �ڿ� ���ο� �׸� �߰��ϴ� ����
	//push_back = && ��������, emplace_back = &����, &&�������� 
	//&�� ���縦 ��, &&�� ���絵 ���� �� &&�� �� ����

	actors.emplace_back(newActor);
	//actors.push_back(newActor);

	//���ʽ� ����
	newActor->SetOwner(this);
}

// ���� �̺�Ʈ �Լ�
void Level::BeginPlay()
{
	for (Actor* actor : actors)
	{
		//�̹� ȣ�� �� ��ü�� �ǳʶٱ�
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float deltaTime)
{
	for (Actor* actor : actors)
	{
		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	//�׸��� ���� ���� ���� �������� ���ġ(����).
	SortActorsBySortingOrder();

	for (Actor* actor : actors)
	{
		Actor* searchedActor = nullptr;
		//�˻� (���� ��ġ�� ���� ���� ���� ���Ͱ� �ִ��� Ȯ��!)
		for (Actor* const otherActor : actors)
		{
			//���� ���� ����
			if (actor == otherActor)
			{
				continue;
			}

			if (actor->Position() == otherActor->Position())
			{
				// ���� ���� �� �� ���� ����
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					//���� �� ���� ����
					searchedActor = otherActor;
					break;
				}
			}
		}

		//� ���Ϳ� ���� ��ġ�� ���� ������ �� ���� ���Ͱ� ������,
		//�׸��� �ʰ� �ǳʶٱ�
		if (searchedActor)
		{
			continue;
		}

		//��ο���
		actor->Render();
	}
}

void Level::SortActorsBySortingOrder()
{
	for (int ix = 0; ix < (int)actors.size(); ix++)
	{
		for (int jx = 0; jx < (int)actors.size()-1; jx++)
		{
			if (actors[jx]->sortingOrder < actors[jx + 1]->sortingOrder)
			{
				std::swap(actors[jx], actors[jx + 1]);
			}
		}
	}
}
