#pragma once
#include "Core.h"
#include <vector> //크기가 알아서 변경되는 동적 배열
//List로 할려했는데 이미 있어서 어쩔수 없이 vector로 했다고함
//즉 수학의 벡터가 아님!
#include "RTTI.h"
class Actor;

class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)
public:
	Level();
	virtual ~Level();

	// 레벨에 액터를 추가할 때 사용
	void AddActor(Actor* newActor);

	// 엔진 이벤트 함수
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

private:
	void SortActorsBySortingOrder();

protected:
	// 레벨에 배치된 모든액터를 관리하는 배열
	std::vector<Actor*> actors;
};