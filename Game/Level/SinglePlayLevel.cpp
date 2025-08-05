#include "SinglePlayLevel.h"
#include "Game/Game.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Actor/Puyo.h"

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

void SinglePlayLevel::SpawnPuyo()
{
	Vector2 spawnPosition((screenMinX + screenMaxX)/2 + 1, screenMinY);
	int code = 1;

	Puyo* puyo = new Puyo(spawnPosition, code, true);
	spawnPosition.y += 2;
	code = 3;
	Puyo* puyo2 = new Puyo(spawnPosition, code, false);

	puyo->SetSibling(puyo2);
	puyo2->SetSibling(puyo);
	AddActor(puyo);
	AddActor(puyo2);

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
