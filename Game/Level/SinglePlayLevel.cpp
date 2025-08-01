#include "SinglePlayLevel.h"
#include "input.h"
#include "Game/Game.h"
#include "Utils/Utils.h"

#include <iostream>

void SinglePlayLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
		return;
	}
}

void SinglePlayLevel::Render()
{
	super::Render();

}
