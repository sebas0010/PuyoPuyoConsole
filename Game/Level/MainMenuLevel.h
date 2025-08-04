#pragma once

#include "Level/Level.h"
#include "Math/Color.h"
#include "Common/MenuItem.h"

class MainMenuLevel : public Level
{
	RTTI_DECLARATIONS(MainMenuLevel, Level)
public:
	MainMenuLevel();
	~MainMenuLevel();

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
};