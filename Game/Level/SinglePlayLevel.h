#pragma once

#include "Level/Level.h"

class SinglePlayLevel : public Level
{
	RTTI_DECLARATIONS(SinglePlayLevel, Level)
		
public:

	void Tick(float deltaTime) override;
	void Render() override;


private:

	void DrawMap();

private:
	
	// 플레이어가 조작 가능한 공간의 좌표
	int screenMinX = 6;
	int screanMaxX = 35;
	int screenMinY = 3;
	int screenMaxY = 26;

	// 현재 뿌요가 떨어지고 있는지 여부
	bool isPuyoLanding = false;
};