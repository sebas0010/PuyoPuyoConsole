#pragma once

#include "Engine.h"

class Game : public Engine
{
public:
	Game();
	void AddSinglePlayLevel();
	void AddMultiPlayLevel();
	void DeleteLevel(Level* targetLevel);
private:
	// 메뉴 레벨
	Level* menuLevel = nullptr;
	Level* gameLevel = nullptr;
	Level* deleteLevel = nullptr;
};