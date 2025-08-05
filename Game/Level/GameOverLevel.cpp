#include "GameOverLevel.h"
#include "Game/Game.h"
#include "Math/Vector2.h"
#include <string>

GameOverLevel::GameOverLevel()
{
	// �޴� ������ �߰� -> �̱�, ��Ƽ, ���� ����
	// �޴� ������ �߰�
	items.emplace_back(new MenuItem(
		"Return to Main Menu",
		[]() { dynamic_cast<Game*>(&Game::Get())->ReturnToMainMenu(); }
	));
	items.emplace_back(new MenuItem(
		"Quit Game",
		[]() { Game::Get().Quit(); }
	));
	// ������ �� �̸� ����
	length = static_cast<int>(items.size());
}

GameOverLevel::~GameOverLevel()
{
	for (MenuItem* item : items)
	{
		SafeDelete(item);
	}

	items.clear();
}

void GameOverLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// �Է� ó��
	if (Input::Get().GetKeyDown(VK_UP))
	{
		if (currentIndex <= 0) return;
		currentIndex--;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		if (currentIndex >= length - 1) return;
		currentIndex++;
	}

	// Enter Ű �Է�
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// �޴� �������� �����ϰ� �ִ� �Լ� ȣ��
		items[currentIndex]->onSelected();
		currentIndex = 0;
	}
}

void GameOverLevel::Render()
{
	score = dynamic_cast<Game*>(&Game::Get())->GetPreviousScore();
	std::string scoreText = std::to_string(score);

	Vector2 showPosition(0, 0);
	Color color = Color::Red;
	Game::Get().WriteToBuffer(showPosition, "Game Over", color);

	showPosition.y += 2;
	Game::Get().WriteToBuffer(showPosition, "Score : ", color);
	showPosition.x += 8;
	Game::Get().WriteToBuffer(showPosition, scoreText.c_str(), color);
	showPosition.x = 0;

	showPosition.y += 2;
	for (int ix = 0; ix < length; ++ix)
	{
		color = ix == currentIndex ? selectedColor : unselectedColor;
		Game::Get().WriteToBuffer(showPosition, items[ix]->menuText, color);
		showPosition.y++;
	}
}
