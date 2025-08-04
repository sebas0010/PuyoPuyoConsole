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
private:
	Level* pauseLevel = nullptr;
	Level* mainMenuLevel = nullptr;
	Level* gameLevel = nullptr;
};