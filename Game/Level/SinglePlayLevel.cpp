#include "SinglePlayLevel.h"
#include "Game/Game.h"
#include "Math/Vector2.h"
#include "Math/Color.h"

void SinglePlayLevel::Tick(float deltaTime)
{
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		dynamic_cast<Game*>(&Game::Get())->Pause();
	}
}

void SinglePlayLevel::Render()
{
	// ¸Ê ±×¸®±â
	Vector2 position1(screenMinX - 1, screenMinY - 1);
	Game::Get().WriteToBuffer(position1, "################################", Color::White);
	position1.y++;
	Vector2 position2(screenMaxX + 1, screenMinY);

	for (int ix = 0; ix < 24; ++ix)
	{
		Game::Get().WriteToBuffer(position1, "#", Color::White);
		Game::Get().WriteToBuffer(position2, "#", Color::White);
		position1.y++;
		position2.y++;
	}
	Game::Get().WriteToBuffer(position1, "################################", Color::White);
	super::Render();

	
}
