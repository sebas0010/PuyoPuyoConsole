#include "MultiGameOverLevel.h"
#include "Game/Game.h"
#include "Math/Vector2.h"
#include <string>
MultiGameOverLevel::MultiGameOverLevel(int player)
	:player(player)
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

MultiGameOverLevel::~MultiGameOverLevel()
{
	for (MenuItem* item : items)
	{
		SafeDelete(item);
	}

	items.clear();
}

void MultiGameOverLevel::Tick(float deltaTime)
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

void MultiGameOverLevel::Render()
{
	Vector2 showPosition(0, 0);
	Color color = Color::Red;

	switch (player)
	{
	case 0:
		Game::Get().WriteToBuffer(showPosition, "Player 2 Win!", color);
		break;
	case 1:
		Game::Get().WriteToBuffer(showPosition, "Player 1 Win!", color);
		break;
	}

	showPosition.y += 2;
	for (int ix = 0; ix < length; ++ix)
	{
		color = ix == currentIndex ? selectedColor : unselectedColor;
		Game::Get().WriteToBuffer(showPosition, items[ix]->menuText, color);
		showPosition.y++;
	}
}
