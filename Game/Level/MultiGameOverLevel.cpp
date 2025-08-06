#include "MultiGameOverLevel.h"
#include "Game/Game.h"
#include "Math/Vector2.h"
#include <string>
MultiGameOverLevel::MultiGameOverLevel(int player)
	:player(player)
{
	// 메뉴 아이템 추가 -> 싱글, 멀티, 게임 종료
	// 메뉴 아이템 추가
	items.emplace_back(new MenuItem(
		"Return to Main Menu",
		[]() { dynamic_cast<Game*>(&Game::Get())->ReturnToMainMenu(); }
	));
	items.emplace_back(new MenuItem(
		"Quit Game",
		[]() { Game::Get().Quit(); }
	));
	// 아이템 수 미리 저장
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

	// 입력 처리
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

	// Enter 키 입력
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// 메뉴 아이템이 저장하고 있는 함수 호출
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
