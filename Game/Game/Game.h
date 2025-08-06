#pragma once

#include "Engine.h"
#include "Level/Level.h"

class Game : public Engine
{
public:
	Game();
	~Game() override;

	// �޸� ���� �Լ�
	void CleanUp() override;

	// ���� �÷��� ���� ������ ����(���� ����)�ϰ� ���� �޴��� ���ư���
	void ReturnToMainMenu();

	// �Ͻ�����
	void Pause();

	// �̱��÷��� ���� ���� ���� 
	void SinglePlayStart();

	// ��Ƽ�÷��� ���� ���� ����
	void MultiPlayStart();

	// �������� ���ư��� �Լ�
	void ResumeGame();

	// ���� ���� �Լ�
	void GameOver(int score);

	// ���� ������ �ҷ����� �Լ�
	int GetPreviousScore();

	// ��Ƽ�÷��� ���� ���� �Լ�
	void MultiGameOver(int loser);
private:
	Level* pauseLevel = nullptr;
	Level* mainMenuLevel = nullptr;
	Level* gameLevel = nullptr;
	Level* gameOverLevel = nullptr;
	Level* multiGameOverLevel = nullptr;
	
	// ������ ������ ǥ���ϱ� ���� ����
	int previousScore = 0;
};