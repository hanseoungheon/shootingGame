#pragma once
#include "Level/Level.h"


/*
* 게임 레벨의 책임
* - 적생성: 약간의 랜덤성을 가미해서 일정 시간마다 적 생성
* - 충돌처리: 플레이어 - 적 탄약 사이의 충돌/ 적-플레이어 탄약의 충돌 처리(AAAB)
* - 점수관리: 플레이어가 적을 없애면 1점씩 획득함.
* - 게임판정: 플레이어가 죽으면 게임 종료.
* - 게임목표: 서바이벌? maybe.
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