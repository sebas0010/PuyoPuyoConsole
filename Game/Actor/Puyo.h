#pragma once

#include "Actor/Actor.h"
#include "Math/Color.h"
#include "Utils/Timer.h"

class Puyo : public Actor
{
	RTTI_DECLARATIONS(Puyo, Actor)
public:
	Puyo(Vector2 spawnPosition, int code, bool isMain);

	void BeginPlay() override;
	void Tick(float deltaTime) override;
	void Render() override;

	// 공중에 떠 있을 때 아래로 안착
	void ApplyGravity(int newY);

	// 액터의 식별코드 Getter
	int GetCode();

	// 파트너 액터 Getter, Setter
	void SetSibling(Puyo* sibling);
	Puyo* GetSibling() const;
private:

	// 바닥에 착지한 뿌요인지 확인
	bool isLanded = false;

	// 조작 가능한 뿌요인지 확인
	bool isControlling = true;

	// 액터의 이미지
	const char* image1 = "(o_o)";
	const char* image2 = "(_^_)";

	// 액터의 식별코드. 1 : 빨강, 2 : 파랑, 3 : 초록, 4 : 노랑, 5 : 보라
	int code = 0;

	// 액터의 색깔
	Color color = Color::White;

	// 아래 방향키를 누르고 있지 않은 경우 하강 속도 : 0.8초에 한칸
	float landingSpeed = 0.8f;

	// 아래 방향키를 누르고 있는 경우 하강 속도 : 0.1초에 한칸
	float landingSpeedFast = 0.1f;

	// Owner 레벨의 특정 함수를 사용하기 위한 인터페이스
	class ICanPuyoMove* canPuyoMoveInterface = nullptr;

	// 뿌요 쌍 파트너의 포인터
	Puyo* sibling = nullptr;

	// 뿌요가 메인인지 서브인지 저장
	bool isMain = false;

	// 서브뿌요의 위치관계를 나타내는 변수 0 : 아래, 1 : 왼쪽, 2 : 위, 3 : 오른쪽
	int subPuyoDirection = 0;

	// 공중에 떠있지 않도록 하는 변수
	bool gravityFlag = false;

	// 떨어질 위치를 저장하는 변수
	Vector2 targetPosition = Vector2::Zero;

	// 한 칸 이동하는데 걸리는 시간을 가지고 있는 타이머
	Timer timer;
};