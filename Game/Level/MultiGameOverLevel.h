#pragma once
#include "Level/Level.h"
#include "Math/Color.h"
#include "Common/MenuItem.h"

class MultiGameOverLevel : public Level
{
	RTTI_DECLARATIONS(MultiGameOverLevel, Level)
public:
	MultiGameOverLevel(int player);
	~MultiGameOverLevel();

	void Tick(float deltaTime) override;
	void Render() override;

private:

	// 현재 선택된 아이템의 인덱스
	int currentIndex = 0;

	// 아이템 선택 색상
	Color selectedColor = Color::Green;

	// 아이템 미선택 색상
	Color unselectedColor = Color::White;

	// 아이템 배열
	std::vector<MenuItem*> items;

	// 메뉴 아이템 수
	int length = 0;

	// 게임 패자
	int player = 0;
};