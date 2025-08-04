#include "Game.h"
#include "Level/MainMenuLevel.h"
#include "Level/MultiPlayLevel.h"
#include "Level/SinglePlayLevel.h"
#include "Level/PauseLevel.h"

Game::Game()
{
	pauseLevel = new PauseLevel;
	mainMenuLevel = new MainMenuLevel;
	mainLevel = mainMenuLevel;
}

Game::~Game()
{
	CleanUp();
	mainLevel = nullptr;
}

void Game::CleanUp()
{
	SafeDelete(mainMenuLevel);
	SafeDelete(pauseLevel);
	SafeDelete(gameLevel);
}

void Game::ReturnToMainMenu()
{
	mainLevel = mainMenuLevel;
	SafeDelete(gameLevel);
	gameLevel = nullptr;
}

void Game::Pause()
{
	mainLevel = pauseLevel;
}

void Game::SinglePlayStart()
{
	gameLevel = new SinglePlayLevel;
	mainLevel = gameLevel;
}

void Game::MultiPlayStart()
{
	gameLevel = new MultiPlayLevel;
	mainLevel = gameLevel;
}

void Game::ResumeGame()
{
	mainLevel = gameLevel;
}
