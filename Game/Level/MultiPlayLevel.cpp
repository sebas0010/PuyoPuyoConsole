#include "MultiPlayLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Actor/MultiPlayPuyo.h"
#include <set>
#include <queue>
#undef min
#undef max
#include <algorithm>

MultiPlayLevel::MultiPlayLevel()
{
	CreateNextPuyo(0);
	CreateNextPuyo(1);
}

void MultiPlayLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	// ESC 키 누르면 일시정지
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		dynamic_cast<Game*>(&Game::Get())->Pause();
	}

	for (int ix = 0; ix < 2; ++ix)
	{
		if (isPuyoLanding[ix] == false)
		{
			// 방해뿌요 처리 중
			if (isDisturbProcessing[ix])
			{
				disturbTimer[ix].Tick(deltaTime);
				if (disturbTimer[ix].IsTimeout())
				{
					// 대기 후 다음 뿌요 스폰
					isDisturbProcessing[ix] = false;
					SpawnPuyo(ix);
				}
				continue;
			}

			// 방해뿌요 생성 조건
			int disturbCount = attackDamage[(ix + 1) % 2] / 70;
			if (disturbCount > 0)
			{
				SpawnDisturbPuyo(ix, disturbCount);
				attackDamage[(ix + 1) % 2] %= 70; // 방해 점수 정산
				// 방해뿌요 떨어질 때 까지 대기
				disturbTimer[ix].Reset();
				disturbTimer[ix].SetTargetTime(1.0f);
				isDisturbProcessing[ix] = true;
				continue;
			}
			
			SpawnPuyo(ix);
			continue;
		}
		// 삭제 진행중
		if (isRemoving[ix])
		{
			removingTimer[ix].Tick(deltaTime);
			if (removingTimer[ix].IsTimeout())
			{
				isRemoving[ix] = false;
				Gravity(ix);
			}
			continue;
		}

		// 중력 작용 중 신호가 들어옴
		if (!isGravityProcessing[ix]) continue;
		if(AllGravityFinished(ix))
		{
			isGravityProcessing[ix] = false;
			curAttackDamage[ix] += Explore(ix);
			// 상쇄로 인한 점수로 상대에게 방해뿌요 생성
			int opponent = (ix + 1) % 2;
			int tmp = std::min(attackDamage[ix], attackDamage[opponent]);
			attackDamage[ix] -= tmp;
			attackDamage[opponent] -= tmp;
		}
	}
}

void MultiPlayLevel::Render()
{
	DrawMap(Vector2(screenMinX[0] - 1, screenMinY[0] - 1));

	DrawMap(Vector2(screenMinX[1] - 1, screenMinY[1] - 1));

	DrawNextPuyo(Vector2(screenMaxX[0] + 4, screenMinY[0]), 0);
	DrawNextPuyo(Vector2(screenMinX[1] - 10, screenMinY[1]), 1);

	DrawDisturbGauge(Vector2(screenMinX[0], screenMinY[0] - 4), 0);
	DrawDisturbGauge(Vector2(screenMinX[1], screenMinY[1] - 4), 1);
	super::Render();
}

void MultiPlayLevel::DrawMap(Vector2 drawPosition)
{
	Game::Get().WriteToBuffer(drawPosition, "################################", Color::White);
	drawPosition.y++;
	Vector2 drawposition2(drawPosition.x + 31, drawPosition.y);

	Vector2 endLine(drawPosition.x + 1, drawPosition.y - 1);
	Game::Get().WriteToBuffer(endLine, "##############################", Color::RedIntensity);

	for (int ix = 0; ix < 24; ++ix)
	{
		Game::Get().WriteToBuffer(drawPosition, "#", Color::White);
		Game::Get().WriteToBuffer(drawposition2, "#", Color::White);
		drawPosition.y++;
		drawposition2.y++;
	}
	Game::Get().WriteToBuffer(drawPosition, "################################", Color::White);
}

void MultiPlayLevel::CreateNextPuyo(int player)
{
	for (int i = 0; i < 2; ++i)
	{
		nextPuyoCode[player][i] = Utils::Random(1, 5);
		switch (nextPuyoCode[player][i])
		{
		case 1:
			nextPuyoColor[player][i] = Color::Red;
			break;
		case 2:
			nextPuyoColor[player][i] = Color::Blue;
			break;
		case 3:
			nextPuyoColor[player][i] = Color::Green;
			break;
		case 4:
			nextPuyoColor[player][i] = Color::Yellow;
			break;
		case 5:
			nextPuyoColor[player][i] = Color::Magneta;
			break;
		default:
			nextPuyoColor[player][i] = Color::White;
			break;
		}
	}
}

void MultiPlayLevel::DrawNextPuyo(Vector2 drawPosition, int player)
{
	Game::Get().WriteToBuffer(drawPosition, puyoImage1, nextPuyoColor[player][0]);
	drawPosition.y++;
	Game::Get().WriteToBuffer(drawPosition, puyoImage2, nextPuyoColor[player][0]);
	drawPosition.y++;
	Game::Get().WriteToBuffer(drawPosition, puyoImage1, nextPuyoColor[player][1]);
	drawPosition.y++;
	Game::Get().WriteToBuffer(drawPosition, puyoImage2, nextPuyoColor[player][1]);
}

void MultiPlayLevel::DrawDisturbGauge(Vector2 drawPosition, int player)
{
	int opponent = (player + 1) % 2;
	int damage = attackDamage[opponent];

	Game::Get().WriteToBuffer(drawPosition, "Disturb Gauge", Color::White);
	drawPosition.y++;

	while (damage >= 70)
	{
		Game::Get().WriteToBuffer(drawPosition, "@@", Color::Yellow);
		drawPosition.x += 2;
		damage -= 70;
	}
}

void MultiPlayLevel::SpawnDisturbPuyo(int player, int disturbPuyoCount)
{
	Vector2 spawnPosition(screenMinX[player], screenMinY[player] - 2);
	std::vector<MultiPlayPuyo*> newDumy;
	while (disturbPuyoCount > 0)
	{
		newDumy.emplace_back(new MultiPlayPuyo(spawnPosition, 0, false, player));
		AddActor(newDumy.back());
		spawnPosition.x += 5;
		if (spawnPosition.x > screenMaxX[player])
		{
			spawnPosition.x = screenMinX[player];
			spawnPosition.y -= 2;
		}
		disturbPuyoCount--;
	}
	int tmp = 0;
	while (!newDumy.empty())
	{
		for (int i = 0; i < 12; i++) {
			if (puyoGrid[player][tmp][i] == nullptr)
			{
				puyoGrid[player][tmp][i] = newDumy.front();
				puyoGrid[player][tmp][i]->ApplyGravity(screenMaxY[player] - 2 * i - 1);
				newDumy.erase(newDumy.begin());
				break;
			}
		}
		tmp++;
		if (tmp > 5) tmp = 0;
	}
}

void MultiPlayLevel::SpawnPuyo(int player)
{
	if (gameOver != -1)
	{
		dynamic_cast<Game*>(&Game::Get())->MultiGameOver(gameOver);
		return;
	}
	attackDamage[player] += curAttackDamage[player];
	curAttackDamage[player] = 0;

	Vector2 spawnPosition((screenMinX[player] + screenMaxX[player]) / 2 + 1, screenMinY[player] - 4);

	MultiPlayPuyo* puyo = new MultiPlayPuyo(spawnPosition, nextPuyoCode[player][0], true, player);
	spawnPosition.y += 2;
	MultiPlayPuyo* puyo2 = new MultiPlayPuyo(spawnPosition, nextPuyoCode[player][1], false, player);

	puyo->SetSibling(puyo2);
	puyo2->SetSibling(puyo);
	AddActor(puyo);
	AddActor(puyo2);

	CreateNextPuyo(player);

	isPuyoLanding[player] = true;
}

bool MultiPlayLevel::CanPuyoMove(MultiPlayPuyo* puyo, Vector2 newPosition)
{
	int player = puyo->GetPlayer();

	// 뿌요가 움직일 위치가 스크린을 벗어나면 못움직인다고 리턴
	if (newPosition.y + 1 > screenMaxY[player]
		|| newPosition.x < screenMinX[player]
		|| newPosition.x > screenMaxX[player])
	{
		return false;
	}

	// 현재 레벨에 있는 플레이어의 뿌요 탐색
	std::vector<MultiPlayPuyo*> puyoActors;
	for (Actor* const actor : actors)
	{
		MultiPlayPuyo* tmpPuyo = actor->As<MultiPlayPuyo>();
		if (tmpPuyo && tmpPuyo->GetPlayer() == player)
		{
			puyoActors.emplace_back(tmpPuyo);
		}
	}

	// 이동할 곳에 뿌요가 있으면 불가하다고 판단
	// 이미 착륙한 모든 뿌요들은 홀수 좌표에 있기 때문에 y좌표 짝수 홀수 나눠서 판단
	if (newPosition.y % 2 == 0)
	{
		Vector2 newPositionNext(newPosition.x, newPosition.y + 1);
		for (MultiPlayPuyo* const puyoActor : puyoActors)
		{
			if (puyoActor->Position() == newPositionNext)
			{
				if (puyoActor != puyo->GetSibling()) return false;
			}
		}
	}
	else
	{
		for (MultiPlayPuyo* const puyoActor : puyoActors)
		{
			if (puyoActor->Position() == newPosition)
			{
				if (puyoActor != puyo->GetSibling()) return false;
			}
		}
	}

	return true;
}

void MultiPlayLevel::PuyoLanded(MultiPlayPuyo* puyo1, MultiPlayPuyo* puyo2)
{
	int player = puyo1->GetPlayer();
	puyoGrid[player][(puyo1->Position().x - screenMinX[player]) / 5][(screenMaxY[player] - 1 - puyo1->Position().y) / 2] = puyo1;
	puyoGrid[player][(puyo2->Position().x - screenMinX[player]) / 5][(screenMaxY[player] - 1 - puyo2->Position().y) / 2] = puyo2;

	Gravity(player);
}

int MultiPlayLevel::GetScreenMinY(int player)
{
	return screenMinY[player];
}

void MultiPlayLevel::Gravity(int player)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (puyoGrid[player][i][j] == nullptr)
			{
				int k;
				for (k = j + 1; k < 24; k++)
				{
					if (puyoGrid[player][i][k] != nullptr)
					{
						// 뿌요 중력 적용
						puyoGrid[player][i][j] = puyoGrid[player][i][k];
						puyoGrid[player][i][j]->ApplyGravity(screenMaxY[player] - 2 * j - 1);
						puyoGrid[player][i][k] = nullptr;
						break;
					}
				}
				if (k == 12) break;
			}
		}
	}
	isGravityProcessing[player] = true;
	gameOver = -1;
	for (int i = 0; i < 6; i++)
	{
		if (puyoGrid[player][i][12] != nullptr) gameOver = player;
	}
}

bool MultiPlayLevel::AllGravityFinished(int player)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (puyoGrid[player][i][j] && puyoGrid[player][i][j]->GetIsLanding())
				return false;
		}
	}
	return true;
}

int MultiPlayLevel::Explore(int player)
{
	bool visited[6][12] = { false };
	std::vector<Vector2> removeList;
	std::set<int> colorSet; // 색상 종류
	std::vector<int> groupSizes; // 그룹 크기 저장

	static const int dx[4] = { 1, -1, 0, 0 };
	static const int dy[4] = { 0, 0, 1, -1 };

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (!puyoGrid[player][i][j] || visited[i][j])
				continue;

			int targetCode = puyoGrid[player][i][j]->GetCode();

			// 방해뿌요 제외
			if (targetCode == 0)
				continue;

			std::vector<Vector2> group;
			std::queue<Vector2> q;

			q.push({ i, j });
			visited[i][j] = true;

			while (!q.empty())
			{
				Vector2 cur = q.front(); q.pop();
				group.push_back(cur);

				for (int dir = 0; dir < 4; dir++)
				{
					int nx = cur.x + dx[dir];
					int ny = cur.y + dy[dir];

					if (nx < 0 || nx >= 6 || ny < 0 || ny >= 12) continue;
					if (visited[nx][ny]) continue;
					if (!puyoGrid[player][nx][ny]) continue;

					if (puyoGrid[player][nx][ny]->GetCode() == targetCode)
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
		isPuyoLanding[player] = false;
		chainCount[player] = 0;
		return 0;
	}

	// === 점수 계산 ===
	int colors = (int)colorSet.size();
	int chainB = chainBonus[std::min(chainCount[player] - 1, 9)];
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
		for (int dir = 0; dir < 4; ++dir)
		{
			int nx = pos.x + dx[dir];
			int ny = pos.y + dy[dir];

			// 경계 체크
			if (nx < 0 || nx >= 6 || ny < 0 || ny >= 12)
				continue;

			// 주변이 방해뿌요(code == 0)면 제거
			if (puyoGrid[player][nx][ny] != nullptr &&
				puyoGrid[player][nx][ny]->GetCode() == 0)
			{
				puyoGrid[player][nx][ny]->WillDestroyed();
				puyoGrid[player][nx][ny] = nullptr;
			}
		}

		// 원래 그룹에 포함된 뿌요 제거
		if (puyoGrid[player][pos.x][pos.y] != nullptr)
		{
			puyoGrid[player][pos.x][pos.y]->WillDestroyed();
			puyoGrid[player][pos.x][pos.y] = nullptr;
		}
	}

	isRemoving[player] = true;
	removingTimer[player].Reset();
	removingTimer[player].SetTargetTime(0.3f);

	chainCount[player]++;
	return score; // 이번 Explore에서 얻은 점수
}
