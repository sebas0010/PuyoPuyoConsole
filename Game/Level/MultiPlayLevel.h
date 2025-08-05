#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"

class MultiPlayLevel : public Level
{
	RTTI_DECLARATIONS(MultiPlayLevel, Level)
public:
	void Tick(float deltaTime) override;
	void Render() override;

	// 맵을 그리는 함수
	void DrawMap(Vector2 drawPosition);
private:

	// 플레이어1이 조작 가능한 공간의 좌표(왼쪽)
	int screen1MinX = 6;
	int screen1MaxX = 35;
	int screen1MinY = 6;
	int screen1MaxY = 29;

	// 플레이어2가 조작 가능한 공간의 좌표(오른쪽)
	int screen2MinX = 50;
	int screen2MaxX = 79;
	int screen2MinY = 6;
	int screen2MaxY = 29;
};