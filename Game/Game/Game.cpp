#include "Game.h"
#include "Level/MainMenuLevel.h"
#include "Level/MultiPlayLevel.h"
#include "Level/SinglePlayLevel.h"
#include "Level/PauseLevel.h"
#include "Level/GameOverLevel.h"
#include "Level/MultiGameOverLevel.h"

Game::Game()
{
	pauseLevel = new PauseLevel;
	mainMenuLevel = new MainMenuLevel;
	mainLevel = mainMenuLevel;
	gameOverLevel = new GameOverLevel;
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
	SafeDelete(gameOverLevel);
}

void Game::ReturnToMainMenu()
{
	mainLevel = mainMenuLevel;
	SafeDelete(gameLevel);
	SafeDelete(multiGameOverLevel);
	gameLevel = nullptr;
	multiGameOverLevel = nullptr;
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

void Game::GameOver(int score)
{
	previousScore = score;
	mainLevel = gameOverLevel;
}

int Game::GetPreviousScore()
{
	return previousScore;
}

void Game::MultiGameOver(int loser)
{
	multiGameOverLevel = new MultiGameOverLevel(loser);
	mainLevel = multiGameOverLevel;
}
