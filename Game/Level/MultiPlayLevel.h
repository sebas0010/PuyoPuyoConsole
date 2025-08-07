#pragma once

#include "Level/Level.h"
#include "Interface/IInteractPuyo.h"


class MultiPlayLevel : public Level, public IInteractPuyo
{
	RTTI_DECLARATIONS(MultiPlayLevel, Level)
public:
	MultiPlayLevel();
	void Tick(float deltaTime) override;
	void Render() override;

	// 맵을 그리는 함수
	void DrawMap(Vector2 drawPosition);

	// 뿌요 쌍 추가 함수
	void CreateNextPuyo(int player);

	// 다음 조작될 뿌요를 그리는 함수
	void DrawNextPuyo(Vector2 drawPosition, int player);

	// 예약된 방해 뿌요 개수를 그리는 함수
	void DrawDisturbGauge(Vector2 drawPosition, int player);

	// 방해 뿌요 스폰 함수
	void SpawnDisturbPuyo(int player, int disturbPuyoCount);

	// 뿌요 쌍 스폰 함수
	void SpawnPuyo(int player);

	// 새로운 위치로 뿌요가 이동 가능한지 확인하는 함수 
	bool CanPuyoMove(MultiPlayPuyo* puyo, Vector2 newPosition) override;

	// 뿌요가 착륙한 후에 Grid에 추가하는 함수
	void PuyoLanded(MultiPlayPuyo* puyo1, MultiPlayPuyo* puyo2) override;

	// 뿌요에게 스크린의 가장 위 좌표를 알려주는 함수
	int GetScreenMinY(int player) override;

	// 중력 작용 함수
	void Gravity(int player);
	
	// 모든 중력 작용이 끝났는지 확인하는 함수
	bool AllGravityFinished(int player);

	// 그리드 탐색 후 4개 이상 연결된 뿌요가 있으면 삭제하는 함수
	int Explore(int player);
private:

	// 플레이어가 조작 가능한 공간의 좌표
	int screenMinX[2] = { 6, 60 };
	int screenMaxX[2] = { 35, 89 };
	int screenMinY[2] = { 5, 5 };
	int screenMaxY[2] = { 28, 28 };

	// 뿌요 이미지
	const char* puyoImage1 = "(o_o)";
	const char* puyoImage2 = "(_^_)";

	// 플레이어가 뿌요를 조작 중인지 판단하는 변수
	bool isPuyoLanding[2] = { false };

	// 플레이어의 다음으로 생성될 뿌요 색과 코드
	int nextPuyoCode[2][2] = {0};
	Color nextPuyoColor[2][2] = {Color::White};

	// 착륙한 뿌요들을 저장하는 함수
	MultiPlayPuyo* puyoGrid[2][6][24] = { nullptr };

	// 중력이 작용중임을 나타내는 변수
	bool isGravityProcessing[2] = { false };

	// 뿌요 삭제가 진행중임을 나타내는 변수
	bool isRemoving[2] = {false};

	// 뿌요 삭제 이펙트 대기시간을 위한 타이머
	Timer removingTimer[2];

	// 상대에게 공격하는 대미지
	int attackDamage[2] = { 0 };

	// 현재 연쇄단계 대미지(모든 연쇄가 끝나면 attackDamage로 넘어감)
	int curAttackDamage[2] = { 0 };

	// 방해 뿌요 생성 단계
	bool isDisturbProcessing[2] = { false };
	
	// 방해 뿌요 처리 대기시간
	Timer disturbTimer[2];;

	// 게임 오버 플래그
	int gameOver = -1;

	// 현재 연쇄 레벨
	int chainCount[2] = { 0 };

	int chainBonus[10] = {
	0,   // 1연쇄
	8,   // 2연쇄
	16,  // 3연쇄
	32,  // 4연쇄
	64,  // 5연쇄
	96,  // 6연쇄
	128, // 7연쇄
	160, // 8연쇄
	192, // 9연쇄
	224  // 10연쇄 이상
	};

	// 색상 보너스 테이블
	int colorBonus[4] = {
		0,  // 1색
		3,  // 2색
		6,  // 3색
		12  // 4색
	};

	// 그룹 크기 보너스 테이블
	int groupBonus[6] = {
		0, // 4개
		2, // 5개
		3, // 6개
		4, // 7개
		5, // 8개
		6  // 9개 이상 (이 이후는 필요 시 확장)
	};
};