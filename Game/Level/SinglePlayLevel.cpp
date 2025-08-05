#include "SinglePlayLevel.h"
#include "Game/Game.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Actor/Puyo.h"
#include "Utils/Utils.h"


SinglePlayLevel::SinglePlayLevel()
{
	CreateNextPuyo();
}

void SinglePlayLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		dynamic_cast<Game*>(&Game::Get())->Pause();
	}
	if (isPuyoLanding == false) SpawnPuyo();
}

void SinglePlayLevel::Render()
{
	// 맵 그리기
	DrawMap(Vector2(screenMinX - 1, screenMinY - 1));
	DrawNextPuyo(Vector2(screenMaxX+5, screenMinY));
	super::Render();
}

void SinglePlayLevel::DrawMap(Vector2 drawPosition)
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

void SinglePlayLevel::CreateNextPuyo()
{
	nextPuyoCode1 = Utils::Random(1, 5);
	switch (nextPuyoCode1)
	{
	case 1:
		nextPuyoColor1 = Color::Red;
		break;
	case 2:
		nextPuyoColor1 = Color::Blue;
		break;
	case 3:
		nextPuyoColor1 = Color::Green;
		break;
	case 4:
		nextPuyoColor1 = Color::Yellow;
		break;
	case 5:
		nextPuyoColor1 = Color::Magneta;
		break;
	default:
		nextPuyoColor1 = Color::White;
		break;
	}

	nextPuyoCode2 = Utils::Random(1, 5);
	switch (nextPuyoCode2)
	{
	case 1:
		nextPuyoColor2 = Color::Red;
		break;
	case 2:
		nextPuyoColor2 = Color::Blue;
		break;
	case 3:
		nextPuyoColor2 = Color::Green;
		break;
	case 4:
		nextPuyoColor2 = Color::Yellow;
		break;
	case 5:
		nextPuyoColor2 = Color::Magneta;
		break;
	default:
		nextPuyoColor2 = Color::White;
		break;
	}
}

void SinglePlayLevel::DrawNextPuyo(Vector2 drawPosition)
{
	Vector2 curPosition = drawPosition;
	Game::Get().WriteToBuffer(curPosition, image1, nextPuyoColor1);
	curPosition.y++;
	Game::Get().WriteToBuffer(curPosition, image2, nextPuyoColor1);

	curPosition.y++;
	Game::Get().WriteToBuffer(curPosition, image1, nextPuyoColor2);
	curPosition.y++;
	Game::Get().WriteToBuffer(curPosition, image2, nextPuyoColor2);
}

void SinglePlayLevel::SpawnPuyo()
{
	Vector2 spawnPosition((screenMinX + screenMaxX)/2 + 1, screenMinY);

	Puyo* puyo = new Puyo(spawnPosition, nextPuyoCode1, true);
	spawnPosition.y += 2;
	Puyo* puyo2 = new Puyo(spawnPosition, nextPuyoCode2, false);

	puyo->SetSibling(puyo2);
	puyo2->SetSibling(puyo);
	AddActor(puyo);
	AddActor(puyo2);

	CreateNextPuyo();

	isPuyoLanding = true;
}

bool SinglePlayLevel::CanPuyoMove(const Puyo& puyo, const Vector2& newPosition)
{
	// 뿌요가 내려갈 위치가 스크린을 벗어나면 못움직인다고 리턴
	if (newPosition.y+1 > screenMaxY || newPosition.x < screenMinX || newPosition.x > screenMaxX)
	{
		return false;
	}

	// 현재 레벨에 있는 뿌요 탐색
	std::vector<Puyo*> puyoActors;
	for (Actor* const actor : actors)
	{
		Puyo* puyo = actor->As<Puyo>();
		if (puyo)
		{
			puyoActors.emplace_back(puyo);
		}
	}

	if (newPosition.y % 2 == 0)
	{
		Vector2 newPositionNext(newPosition.x, newPosition.y+1);
		for (Puyo* const puyoActor : puyoActors)
		{
			if (puyoActor->Position() == newPositionNext)
			{
				if (puyoActor != puyo.GetSibling()) return false;
			}
		}
	}
	else
	{
		for (Puyo* const puyoActor : puyoActors)
		{
			if (puyoActor->Position() == newPosition)
			{
				if (puyoActor != puyo.GetSibling()) return false;
			}
		}
	}
	
	return true;
}

void SinglePlayLevel::PuyoLanded(Puyo* puyo1, Puyo* puyo2)
{
	puyoGrid[puyo1->Position().x / 5 - 1][(25 - puyo1->Position().y) / 2] = puyo1;
	puyoGrid[puyo2->Position().x / 5 - 1][(25 - puyo2->Position().y) / 2] = puyo2;

	Gravity();

	isPuyoLanding = false;
}

void SinglePlayLevel::Gravity()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (puyoGrid[i][j] == nullptr)
			{
				int k;
				for (k = j + 1; k < 12; k++)
				{
					if (puyoGrid[i][k] != nullptr)
					{
						// 뿌요 중력 적용
						puyoGrid[i][j] = puyoGrid[i][k];
						puyoGrid[i][j]->ApplyGravity(25 - 2*j);
						puyoGrid[i][k] = nullptr;
						break;
					}
				}
				if (k == 12) break;
			}
		}
	}
}

void SinglePlayLevel::Explore()
{
}
