#pragma once

#include "Level/Level.h"
#include "Math/Color.h"

class SinglePlayLevel : public Level
{
	RTTI_DECLARATIONS(SinglePlayLevel, Level)
public:

	void Tick(float deltaTime) override;
	void Render() override;

private:

	// 플레이어가 조작 가능한 공간의 좌표
	int screenMinX = 6;
	int screenMaxX = 35;
	int screenMinY = 3;
	int screenMaxY = 26;
};