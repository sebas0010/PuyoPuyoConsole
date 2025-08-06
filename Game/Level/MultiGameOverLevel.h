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

	// ���� ���õ� �������� �ε���
	int currentIndex = 0;

	// ������ ���� ����
	Color selectedColor = Color::Green;

	// ������ �̼��� ����
	Color unselectedColor = Color::White;

	// ������ �迭
	std::vector<MenuItem*> items;

	// �޴� ������ ��
	int length = 0;

	// ���� ����
	int player = 0;
};