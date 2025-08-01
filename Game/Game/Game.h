#pragma once

#include "Engine.h"

class Game : public Engine
{
public:
	Game();
	~Game();
	void AddSinglePlayLevel();
	void AddMultiPlayLevel();
	void ReturnToMainMenu();
	void ToggleMenu();

	void CleanUp() override;

	static Game& Get();
private:
	// 메뉴 레벨
	Level* menuLevel = nullptr;
	// 게임 레벨
	Level* gameLevel = nullptr;
	// 일시 정지 레벨
	Level* pauseLevel = nullptr;

	// 현재 일시정지 상태인지 나타내는 변수
	bool pause = false;

	static Game* instance;
};