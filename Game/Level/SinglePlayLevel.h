#pragma once

#include "Level/Level.h"
#include "Interface/ICanPuyoMove.h"


class SinglePlayLevel : public Level, public ICanPuyoMove
{
	RTTI_DECLARATIONS(SinglePlayLevel, Level)
public:
	SinglePlayLevel();
	void Tick(float deltaTime) override;
	void Render() override;

	// 맵을 그리는 함수
	void DrawMap(Vector2 drawPosition);

	// 다음 조작될 뿌요를 생성하는 함수
	void CreateNextPuyo();

	// 다음 조작될 뿌요를 그리는 함수
	void DrawNextPuyo(Vector2 drawPosition);

	// 뿌요 스폰 함수
	void SpawnPuyo();

	// 새로운 위치로 뿌요가 이동 가능한지 확인하는 함수 
	bool CanPuyoMove(const Puyo& puyo, const Vector2& newPosition);

	// 뿌요가 착륙한 후에 Grid에 추가하는 함수
	void PuyoLanded(Puyo* puyo1, Puyo* puyo2);

	// 뿌요 그리드를 탐색하며 중력 적용하는 함수
	void Gravity();

	// 모든 뿌요 그리드의 중력 작용이 끝났는지 감지하는 함수
    bool AllGravityFinished();

	// 뿌요 그리드를 탐색하며 같은 색 4개가 연결된 경우 터뜨리는 함수
	void Explore();

	// 플레이어가 조작 가능한 공간의 좌표
	int screenMinX = 6;
	int screenMaxX = 35;
	int screenMinY = 3;
	int screenMaxY = 26;

private:
	// 뿌요를 조작 중인지 판단하기 위한 변수
	bool isPuyoLanding = false;

	// 뿌요 착륙 후를 처리중인지 판단하기 위한 변수
	bool isProcessing = false;

	// 착륙한 뿌요들을 저장하는 함수
	Puyo* puyoGrid[6][12] = { nullptr };

	// 뿌요 이미지
	const char* image1 = "(o_o)";
	const char* image2 = "(_^_)";

	// 다음 생성될 뿌요의 색과 코드
	int nextPuyoCode1 = 0;
	int nextPuyoCode2 = 0;
	Color nextPuyoColor1 = Color::White;
	Color nextPuyoColor2 = Color::White;
};