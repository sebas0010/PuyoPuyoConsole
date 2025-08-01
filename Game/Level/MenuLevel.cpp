#include "MenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"
#include "Math/Vector2.h"
#include <iostream>

MenuLevel::MenuLevel()
{
	// 메뉴 아이템 추가
	items.emplace_back(new MenuItem(
		"Single Play",
		[]() { Game::Get().AddSinglePlayLevel(); }
	));
	items.emplace_back(new MenuItem(
		"1 vs 1",
		[]() { Game::Get().AddMultiPlayLevel(); }
	));
	items.emplace_back(new MenuItem(
		"Quit Game",
		[]() { Game::Get().Quit(); }
	));
	// 아이템 수 미리 저장
	length = static_cast<int>(items.size());
}

MenuLevel::~MenuLevel()
{
	for (MenuItem* item : items)
	{
		SafeDelete(item);
	}

	items.clear();
}

void MenuLevel::Tick(float deltaTime)
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
		currentIndex ++;
	}

	// Enter 키 입력
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// 메뉴 아이템이 저장하고 있는 함수 호출
		items[currentIndex]->onSelected();
	}
}

void MenuLevel::Render()
{
	super::Render();

	// 색상 & 좌표 정리
	Utils::SetConsolePosition(Vector2::Zero);
	Utils::SetConsoleTextColor(static_cast<WORD>(unselectedColor));

	// 메뉴 제목 출력
	std::cout << "Puyo Puyo\n\n";

	//메뉴 아이템 렌더링.
	for (int ix = 0; ix < length; ++ix)
	{
		// 아이템 색상 확인.
		Color textColor = (ix == currentIndex) ? selectedColor : unselectedColor;

		// 색상 설정
		Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

		// 메뉴 텍스트 출력
		std::cout << items[ix]->menuText << "\n";
	}
}
