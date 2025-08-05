#pragma once

#include "Level/Level.h"
#include "Interface/ICanPuyoMove.h"


class SinglePlayLevel : public Level, public ICanPuyoMove
{
	RTTI_DECLARATIONS(SinglePlayLevel, Level)
public:

	void Tick(float deltaTime) override;
	void Render() override;

	void SpawnPuyo();

	// 새로운 위치로 뿌요가 이동 가능한지 확인하는 함수 
	bool CanPuyoMove(const Puyo& puyo, const Vector2& newPosition);

	// 뿌요가 착륙한 후에 Grid에 추가하는 함수
	void PuyoLanded(Puyo* puyo1, Puyo* puyo2);

	// 뿌요 그리드를 탐색하며 중력 적용하는 함수
	void Gravity();

	// 뿌요 그리드를 탐색하며 같은 색 4개가 연결된 경우 터뜨리는 함수
	void Explore();

	// 플레이어가 조작 가능한 공간의 좌표
	int screenMinX = 6;
	int screenMaxX = 35;
	int screenMinY = 3;
	int screenMaxY = 26;


private:
	bool isPuyoLanding = false;

	// 착륙한 뿌요들을 저장하는 함수
	Puyo* puyoGrid[6][12] = { nullptr };
};