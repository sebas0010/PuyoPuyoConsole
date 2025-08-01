#include "Game.h"
#include "Level/MenuLevel.h"
#include "Level/SinglePlayLevel.h"
#include "Level/MultiPlayLevel.h"

Game::Game()
{
	// 게임을 시작하면 메뉴를 먼저 보여줌
	AddLevel(menuLevel = new MenuLevel());
}

void Game::AddSinglePlayLevel()
{
	AddLevel(gameLevel = new SinglePlayLevel());
}

void Game::AddMultiPlayLevel()
{
	AddLevel(gameLevel = new MultiPlayLevel());
}

void Game::DeleteLevel(Level* targetLevel)
{
	deleteLevel = targetLevel;
}
