#include "MultiPlayLevel.h"
#include "Utils/Utils.h"
#include "Input.h"
#include "Game/Game.h"
#include <iostream>

void MultiPlayLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
		return;
	}
}

void MultiPlayLevel::Render()
{
	Utils::SetConsolePosition(Vector2::Zero);

	std::cout << "This is multiplay screen";

}
