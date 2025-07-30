#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{

}
Level::~Level()
{
	for (Actor* actor : actors)
	{
		////null 확인 후 액터 제거
		//if (actor)
		//{
		//	//삭제 및 메모리 정리.
		//	delete actor;
		//	actor = nullptr;
		//}
		SafeDelete(actor);
	}

	//std::vector 정리
	actors.clear();
}

// 레벨에 액터를 추가할 때 사용
void Level::AddActor(Actor* newActor)
{
	//예외처리(중복 여부 확인) 필수

	//push_back , emplace_back : 배열 맨 뒤에 새로운 항목 추가하는 변수
	//push_back = && 이중참조, emplace_back = &참조, &&이중참조 
	//&는 복사를 함, &&는 복사도 안함 즉 &&가 더 빠름

	actors.emplace_back(newActor);
	//actors.push_back(newActor);

	//오너십 설정
	newActor->SetOwner(this);
}

// 엔진 이벤트 함수
void Level::BeginPlay()
{
	for (Actor* actor : actors)
	{
		//이미 호출 된 개체는 건너뛰기
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
	//그리기 전에 정렬 순서 기준으로 재배치(정렬).
	SortActorsBySortingOrder();

	for (Actor* actor : actors)
	{
		Actor* searchedActor = nullptr;
		//검사 (같은 위치에 정렬 순서 높은 액터가 있는지 확인!)
		for (Actor* const otherActor : actors)
		{
			//같은 액터 무시
			if (actor == otherActor)
			{
				continue;
			}

			if (actor->Position() == otherActor->Position())
			{
				// 정렬 순서 비교 후 액터 저장
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					//저장 및 루프 종료
					searchedActor = otherActor;
					break;
				}
			}
		}

		//어떤 액터와 같은 위치에 정렬 순서가 더 높은 액터가 있으면,
		//그리지 않고 건너뛰기
		if (searchedActor)
		{
			continue;
		}

		//드로우콜
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
