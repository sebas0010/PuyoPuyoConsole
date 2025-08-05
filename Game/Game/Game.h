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
private:
	Level* pauseLevel = nullptr;
	Level* mainMenuLevel = nullptr;
	Level* gameLevel = nullptr;
	Level* gameOverLevel = nullptr;
	
	// ������ ������ ǥ���ϱ� ���� ����
	int previousScore = 0;
};