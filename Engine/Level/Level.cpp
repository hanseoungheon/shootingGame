#include "Level.h"
#include "Actor/Actor.h"
#include "Utils/Utils.h"
#include <iostream>

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

	//�߰���� ���͹迭�� �ش� �����߰� -> ���迭�� �߰�
	addRequestedActors.emplace_back(newActor);

	//actors.emplace_back(newActor);
	//actors.push_back(newActor);

	//���ʽ� ����
	//newActor->SetOwner(this);
}

void Level::DestroyActor(Actor* destroyedActor)
{
	//���迭�� �߰�
	destroyRequstedActors.emplace_back(destroyedActor);
}

void Level::ProcessAddAndDestroyActors()
{
	// actors �迭���� ���� ó��
	for (auto iterator = actors.begin(); iterator != actors.end();)
	{
		//���� ��û�� �������� Ȯ�� �� �迭���� ���ܽ�Ŵ.
		// �����͸� ����Ű�� ������ *iterator = Actor*

		if ((*iterator)->isExpired) 
		{
			//erase�Լ��� ���� iterator�� ��ȿȭ��
			//�� ��ȯ�Ǵ� ���� �����ؾߵ�
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	// destroyRequstedAcotrs �迭�� ��ȸ�ϸ鼭 ���� delete.
	for (auto* actor : destroyRequstedActors)
	{
		//���Ͱ� �׷��������� �����
		Utils::SetConsolePosition(actor->position);

		//�ֿܼ� ���� ����ؼ� �����
		for (int ix = 0; ix < actor->width; ++ix)
		{
			std::cout << " ";
		}

		//���ҽ� ����
		SafeDelete(actor);
	}

	//�迭 �ʱ�ȭ
	destroyRequstedActors.clear();

	// addRequstedActors �迭�� ��ȸ�ϸ鼭 ���ο� ���� �߰�
	for (Actor* const actor : addRequestedActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}

	//�迭 �ʱ�ȭ
	addRequestedActors.clear();
}

// ���� �̺�Ʈ �Լ�
void Level::BeginPlay()
{
	for (Actor* actor : actors)
	{
		//���� ó�� ���� Ȯ��
		//���� ��û�� ���� ���°ų�(or) ��Ȱ��ȭ�����̸� �ǳʶ�
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

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
		//���� ��û�� ���� ���°ų�(or) ��Ȱ��ȭ�����̸� �ǳʶ�(Tick����)
		if (!actor->isActive || actor->isExpired)
		{
			continue;

		}

		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	//�׸��� ���� ���� ���� �������� ���ġ(����).
	SortActorsBySortingOrder();

	for (Actor* actor : actors)
	{
		//���� ��û�� ���� ���°ų�(or) ��Ȱ��ȭ�����̸� �ǳʶ�
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

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
