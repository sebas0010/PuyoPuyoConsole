#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"

class MultiPlayLevel : public Level
{
	RTTI_DECLARATIONS(MultiPlayLevel, Level)
public:
	void Tick(float deltaTime) override;
	void Render() override;

	// ���� �׸��� �Լ�
	void DrawMap(Vector2 drawPosition);
private:

	// �÷��̾�1�� ���� ������ ������ ��ǥ(����)
	int screen1MinX = 6;
	int screen1MaxX = 35;
	int screen1MinY = 6;
	int screen1MaxY = 29;

	// �÷��̾�2�� ���� ������ ������ ��ǥ(������)
	int screen2MinX = 50;
	int screen2MaxX = 79;
	int screen2MinY = 6;
	int screen2MaxY = 29;
};