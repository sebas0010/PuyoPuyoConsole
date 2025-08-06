#pragma once

#include "Actor/Actor.h"
#include "Math/Color.h"
#include "Utils/Timer.h"

class MultiPlayPuyo : public Actor
{
	RTTI_DECLARATIONS(MultiPlayPuyo, Actor)
public:
	MultiPlayPuyo(Vector2 spawnPosition, int code, bool isMain, int player);

	void BeginPlay() override;
	void Tick(float deltaTime) override;
	void Render() override;

	// 중력 작용 함수
	void ApplyGravity(int newY);

	// 4개 이상 연결 되었으므로 삭제 예정 신호를 받아오는 함수
	void WillDestroyed();

	// code -> color 변환 함수
	Color CodeToColor(int code);

	// sibling Getter, Setter
	void SetSibling(MultiPlayPuyo* sibling);
	MultiPlayPuyo* GetSibling() const;

	// player Getter
	int GetPlayer();

	// IsLanding Getter
	bool GetIsLanding();

	// code Getter
	int GetCode();

private:
	// 이 액터를 소유하고 있는 레벨의 함수를 사용하기 위한 인터페이스
	class IInteractPuyo* ownerInterface = nullptr;
	
	// 이 뿌요를 조작하는 사람이 플레이어1(왼쪽) 인지 플레이어2(오른쪽)인지 판단하는 변수
	int player = 0;

	// 왼쪽 조작 버튼
	int leftButton = 0;

	// 오른쪽 조작 버튼
	int rightButton = 0;

	// 아래 조작 버튼
	int downButton = 0;
	
	// 조작 중인 뿌요인지 확인
	bool isControlling = true;

	// 아래로 이동할 수 있는지 없는지 확인
	bool canMoveDown = true;

	// 중력이 작용중인지 확인
	bool isLanding = false;

	// 중력이 작용할 때 착지할 위치
	Vector2 landingTarget = Vector2::Zero;

	// 뿌요가 메인인지 서브인지 저장
	bool isMain = false;

	// 삭제 될 액터임을 표시하는 변수
	bool isDestroying = false;

	// 삭제 이펙트 카운트
	int effectCount = 0;

	// 삭제 이펙스 색깔 코드
	int effectCode = 0;

	// 액터의 식별코드. 1 : 빨강, 2 : 파랑, 3 : 초록, 4 : 노랑, 5 : 보라
	int code = 0;

	// 액터의 색깔
	Color color = Color::White;

	// 액터의 이미지
	const char* image1 = "(o_o)";
	const char* image2 = "(_^_)";

	// 삭제 중인 액터의 이미지
	const char* removingImage1 = "($_$)";
	const char* removingImage2 = "(_^_)";

	// 아래 방향키를 누르고 있지 않은 경우 하강 속도 : 0.8초에 한칸
	float landingSpeed = 0.8f;

	// 아래 방향키를 누르고 있는 경우 하강 속도 : 0.1초에 한칸
	float landingSpeedFast = 0.05f;

	// 한 칸 이동하는데 걸리는 시간을 가지고 있는 타이머
	Timer timer;

	// 뿌요 쌍 파트너의 포인터
	MultiPlayPuyo* sibling = nullptr;

	// 서브뿌요의 위치관계를 나타내는 변수 0 : 아래, 1 : 왼쪽, 2 : 위, 3 : 오른쪽
	int subPuyoDirection = 0;

};