#include "Game.h"
#include "Level/MenuLevel.h"
#include "Level/SinglePlayLevel.h"
#include "Level/MultiPlayLevel.h"
#include "Level/PauseLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;
	// 게임을 시작하면 메뉴를 먼저 보여줌
	AddLevel(menuLevel = new MenuLevel());
	pauseLevel = new PauseLevel();
}
Game::~Game()
{
	CleanUp();
}

void Game::AddSinglePlayLevel()
{
	system("cls");
	pause = false;
	AddLevel(gameLevel = new SinglePlayLevel());
}

void Game::AddMultiPlayLevel()
{
	system("cls");
	pause = false;
	AddLevel(gameLevel = new MultiPlayLevel());
}

void Game::ReturnToMainMenu()
{
	delete gameLevel;
	gameLevel = nullptr;
	system("cls");
	mainLevel = menuLevel;
}

void Game::ToggleMenu()
{
	// 화면 정리
	// clear screen 명령어 실행
	system("cls");

	pause = !pause;

	if (pause)
	{
		mainLevel = pauseLevel;
	}
	else
	{
		// 게임 레벨을 메인 레벨로 설정
		mainLevel = gameLevel;
	}
}

void Game::CleanUp()
{
	SafeDelete(mainLevel);
	SafeDelete(menuLevel);
	SafeDelete(gameLevel);
}

Game& Game::Get()
{
	return *instance;
}