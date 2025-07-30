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

	//추가목록 액터배열에 해당 액터추가 -> 대기배열에 추가
	addRequestedActors.emplace_back(newActor);

	//actors.emplace_back(newActor);
	//actors.push_back(newActor);

	//오너십 설정
	//newActor->SetOwner(this);
}

void Level::DestroyActor(Actor* destroyedActor)
{
	//대기배열에 추가
	destroyRequstedActors.emplace_back(destroyedActor);
}

void Level::ProcessAddAndDestroyActors()
{
	// actors 배열에서 삭제 처리
	for (auto iterator = actors.begin(); iterator != actors.end();)
	{
		//삭제 요청된 액터인지 확인 후 배열에서 제외시킴.
		// 포인터를 가르키는 포인터 *iterator = Actor*

		if ((*iterator)->isExpired) 
		{
			//erase함수를 사용시 iterator가 무효화됨
			//즉 반환되는 값을 저장해야됨
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	// destroyRequstedAcotrs 배열을 순회하면서 액터 delete.
	for (auto* actor : destroyRequstedActors)
	{
		//액터가 그려져있으면 지우기
		Utils::SetConsolePosition(actor->position);

		//콘솔에 빈문자 출력해서 지우기
		for (int ix = 0; ix < actor->width; ++ix)
		{
			std::cout << " ";
		}

		//리소스 해제
		SafeDelete(actor);
	}

	//배열 초기화
	destroyRequstedActors.clear();

	// addRequstedActors 배열을 순회하면서 새로운 액터 추가
	for (Actor* const actor : addRequestedActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}

	//배열 초기화
	addRequestedActors.clear();
}

// 엔진 이벤트 함수
void Level::BeginPlay()
{
	for (Actor* actor : actors)
	{
		//액터 처리 여부 확인
		//삭제 요청이 들어온 상태거나(or) 비활성화상태이면 건너뜀
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

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
		//삭제 요청이 들어온 상태거나(or) 비활성화상태이면 건너뜀(Tick에서)
		if (!actor->isActive || actor->isExpired)
		{
			continue;

		}

		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	//그리기 전에 정렬 순서 기준으로 재배치(정렬).
	SortActorsBySortingOrder();

	for (Actor* actor : actors)
	{
		//삭제 요청이 들어온 상태거나(or) 비활성화상태이면 건너뜀
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

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
