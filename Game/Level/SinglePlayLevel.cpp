#include "SinglePlayLevel.h"
#include "Game/Game.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Actor/Puyo.h"
#include "Utils/Utils.h"

#undef min
#undef max

#include <queue>
#include <set>
#include <algorithm>
#include <string>


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
	if (isPuyoLanding == false && !isRemoving) SpawnPuyo();

	if (isRemoving)
	{
		removingTimer.Tick(deltaTime);
		if (removingTimer.IsTimeout())
		{
			isRemoving = false;
			Gravity();
		}
		return;
	}

	if (!isProcessing) return;
	if (AllGravityFinished()) gameScore += Explore();
}

void SinglePlayLevel::Render()
{
	// 맵 그리기
	DrawMap(Vector2(screenMinX - 1, screenMinY - 1));
	DrawNextPuyo(Vector2(screenMaxX+5, screenMinY));

	std::string scoreText = std::to_string(gameScore);

	Game::Get().WriteToBuffer(Vector2::Zero, scoreText.c_str(), Color::White);
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
	if (puyoGrid[3][10] != nullptr)
	{
		dynamic_cast<Game*>(&Game::Get())->GameOver(gameScore);
		return;
	}
	
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
	if (newPosition.y < screenMinY || newPosition.y+1 > screenMaxY || newPosition.x < screenMinX || newPosition.x > screenMaxX)
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
	isProcessing = true;
}

bool SinglePlayLevel::AllGravityFinished()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (puyoGrid[i][j] && puyoGrid[i][j]->GetGravityFlag())
				return false;
		}
	}
	return true;
}

int SinglePlayLevel::Explore()
{
	bool visited[6][12] = { false };
	std::vector<Vector2> removeList;
	std::set<int> colorSet; // 색상 종류
	std::vector<int> groupSizes; // 그룹 크기 저장

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (!puyoGrid[i][j] || visited[i][j])
				continue;

			int targetCode = puyoGrid[i][j]->GetCode();
			std::vector<Vector2> group;
			std::queue<Vector2> q;

			q.push({ i, j });
			visited[i][j] = true;

			while (!q.empty())
			{
				Vector2 cur = q.front(); q.pop();
				group.push_back(cur);

				static const int dx[4] = { 1, -1, 0, 0 };
				static const int dy[4] = { 0, 0, 1, -1 };

				for (int dir = 0; dir < 4; dir++)
				{
					int nx = cur.x + dx[dir];
					int ny = cur.y + dy[dir];

					if (nx < 0 || nx >= 6 || ny < 0 || ny >= 12) continue;
					if (visited[nx][ny]) continue;
					if (!puyoGrid[nx][ny]) continue;

					if (puyoGrid[nx][ny]->GetCode() == targetCode)
					{
						visited[nx][ny] = true;
						q.push({ nx, ny });
					}
				}
			}

			if (group.size() >= 4)
			{
				// 그룹 정보 저장
				colorSet.insert(targetCode);
				groupSizes.push_back((int)group.size());
				removeList.insert(removeList.end(), group.begin(), group.end());
			}
		}
	}
	if (removeList.empty())
	{
		isPuyoLanding = false;
		isProcessing = false;
		chainCount = 0;
		return 0;
	}

	// === 점수 계산 ===
	int colors = (int)colorSet.size();
	int chainB = chainBonus[std::min(chainCount - 1, 9)];
	int colorB = colorBonus[std::min(colors - 1, 3)];

	int groupB = 0;
	for (int size : groupSizes)
	{
		int idx = std::min(size - 4, 5);
		groupB += groupBonus[std::max(0, idx)];
	}

	int bonus = chainB + colorB + groupB;
	if (bonus < 1) bonus = 1;

	int totalRemoved = (int)removeList.size();
	int score = totalRemoved * 10 * bonus;

	// === 삭제 실행 ===
	for (auto& pos : removeList)
	{
		puyoGrid[pos.x][pos.y]->WillDestroyed();
		puyoGrid[pos.x][pos.y] = nullptr;
	}

	isRemoving = true;
	removingTimer.Reset();
	removingTimer.SetTargetTime(0.3f);


	chainCount++;
	return score; // 이번 Explore에서 얻은 점수
}