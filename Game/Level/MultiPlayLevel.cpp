#include "MultiPlayLevel.h"
#include "Game/Game.h"

void MultiPlayLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		dynamic_cast<Game*>(&Game::Get())->Pause();
	}
}

void MultiPlayLevel::Render()
{
	DrawMap(Vector2(screen1MinX - 1, screen1MinY - 1));

	DrawMap(Vector2(screen2MinX - 1, screen2MinY - 1));
	super::Render();
}

void MultiPlayLevel::DrawMap(Vector2 drawPosition)
{
	Game::Get().WriteToBuffer(drawPosition, "################################", Color::White);
	drawPosition.y++;
	Vector2 drawposition2(drawPosition.x + 31, drawPosition.y);

	for (int ix = 0; ix < 24; ++ix)
	{
		Game::Get().WriteToBuffer(drawPosition, "#", Color::White);
		Game::Get().WriteToBuffer(drawposition2, "#", Color::White);
		drawPosition.y++;
		drawposition2.y++;
	}
	Game::Get().WriteToBuffer(drawPosition, "################################", Color::White);
}