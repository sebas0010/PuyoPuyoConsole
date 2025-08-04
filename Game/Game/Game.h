#pragma once

#include "Engine.h"
#include "Level/Level.h"

class Game : public Engine
{
public:
	Game();
	~Game() override;

	// 메모리 정리 함수
	void CleanUp() override;

	// 현재 플레이 중인 게임을 종료(레벨 삭제)하고 메인 메뉴로 돌아가기
	void ReturnToMainMenu();

	// 일시정지
	void Pause();

	// 싱글플레이 게임 레벨 생성 
	void SinglePlayStart();

	// 멀티플레이 게임 레벨 생성
	void MultiPlayStart();

	// 게임으로 돌아가는 함수
	void ResumeGame();
private:
	Level* pauseLevel = nullptr;
	Level* mainMenuLevel = nullptr;
	Level* gameLevel = nullptr;
};