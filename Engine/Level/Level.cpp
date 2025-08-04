#include "Level.h"
#include "Actor/Actor.h"
#include "Utils/Utils.h"
#include <iostream>

Level::Level()
{
}

Level::~Level()
{
	// �޸� ����.
	for (Actor* actor : actors)
	{
		SafeDelete(actor);
	}

	// std::vector ����.
	actors.clear();
}

// ������ ���͸� �߰��� �� ���.
void Level::AddActor(Actor* newActor)
{
	// ����ó��(�ߺ� ���� Ȯ��) �ʿ���.

	// ��� �迭�� �߰�.
	addRequstedActors.emplace_back(newActor);
	
	// ���ʽ� ����.
	//newActor->SetOwner(this);
}

void Level::DestroyActor(Actor* destroyedActor)
{
	// �ߺ� �˻�.
	if (destroyRequstedActors.size() > 0)
	{
		for (const Actor* const actor : destroyRequstedActors)
		{
			if (actor == destroyedActor)
			{
				return;
			}
		}
	}

	// ��� �迭�� �߰�.
	destroyRequstedActors.emplace_back(destroyedActor);
}

// ���� �̺�Ʈ �Լ�.
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		// ���� ó�� ���� Ȯ��.
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		// �̹� ȣ��� ��ü�� �ǳʶٱ�.
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
		// ���� ó�� ���� Ȯ��.
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		// ���� �ֱ� Ȯ�� �� ó��.
		if (actor->autoDestroy)
		{
			// ���� �ֱ� ���� ó��.
			actor->lifetime -= deltaTime;

			// ������ ���ߴ��� Ȯ��.
			if (actor->lifetime <= 0.0f)
			{
				// ���� ���� ��û�ϰ�, ���� ���� ó��.
				actor->lifetime = 0.0f;
				actor->Destroy();
				continue;
			}
		}

		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	// Render Pass.
	for (Actor* const actor : actors)
	{
		// ��ο� ��.
		actor->Render();
	}
}

void Level::ProcessAddAndDestroyActors()
{
	// actors �迭���� ���� ó��.
	for (auto iterator = actors.begin(); iterator != actors.end();)
	{
		// ���� ��û�� �������� Ȯ�� �� �迭���� ����
		if ((*iterator)->isExpired)
		{
			// erase �Լ��� ����ϸ� iterator�� ��ȿȭ�Ǳ� ������
			// ��ȯ�Ǵ� ���� �����ؾ���.
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}
	
	// destroyRequstedActors �迭�� ��ȸ�ϸ鼭 ���� delete.
	for (auto*& actor : destroyRequstedActors)
	{
		// ���Ͱ� �׷ȴ� �� �����.
		Utils::SetConsolePosition(actor->position);

		// �ֿܼ� ���� ����ؼ� �����.
		//for (int ix = 0; ix < actor->width; ++ix)
		//{
		//	std::cout << " ";
		//}

		// ���ҽ� ����.
		SafeDelete(actor);
	}

	// �迭 �ʱ�ȭ -> ũ�Ⱑ 0.
	destroyRequstedActors.clear();

	// addRequstedActors �迭�� ��ȸ�ϸ鼭 ���ο� ���� �߰�.
	for (auto* const actor : addRequstedActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}

	// �迭 �ʱ�ȭ.
	addRequstedActors.clear();
}

void Level::SortActorsBySortingOrder()
{
	// ���� ����.
	for (int ix = 0; ix < (int)actors.size(); ++ix)
	{
		for (int jx = 0; jx < (int)actors.size() - 1; ++jx)
		{
			// sortingOrder ���� Ŭ���� �� �ʿ� ��ġ.
			if (actors[jx]->sortingOrder > actors[jx + 1]->sortingOrder)
			{
				// �� ���� ��ġ ��ȯ.
				std::swap(actors[jx], actors[jx + 1]);
			}
		}
	}
}