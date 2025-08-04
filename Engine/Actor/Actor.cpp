#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/Level.h"

#include <Windows.h>
#include <iostream>

Actor::Actor(const char* image, Color color, const Vector2& position)
	: color(color), position(position)
{
	// ���ڿ� ����.
	width = (int)strlen(image);

	// �޸� �Ҵ�.
	this->image = new char[width + 1];

	// ���ڿ� ����.
	strcpy_s(this->image, width + 1, image);
}

Actor::~Actor()
{
	// �޸� ����.
	SafeDeleteArray(image);
}

// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����).
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
void Actor::Tick(float deltaTime)
{
}

// �׸��� �Լ�.
void Actor::Render()
{
	// Ŀ�� �̵�.
	//Utils::SetConsolePosition(position);

	// ���� ����.
	//Utils::SetConsoleTextColor(color);

	// �׸���.
	//std::cout << image;

	// ������ �����ϴ� �̹��� ���ۿ� ������ ���ڿ�/���� ���.
	Engine::Get().WriteToBuffer(position, image, color);
}

void Actor::SetPosition(const Vector2& newPosition)
{
	// ����ó�� (ȭ�� ������� Ȯ��).

	// ���� �����ڸ��� ȭ�� ������ �������.
	//if (newPosition.x < 0)
	//{
	//	return;
	//}

	//// ������ �����ڸ��� ȭ�� �������� �������.
	//if (newPosition.x + width > Engine::Get().Width())
	//{
	//	return;
	//}

	//// ���� �����ڸ��� ȭ���� ���� �������
	//if (newPosition.y < 0)
	//{
	//	return;
	//}

	//// ȭ�� �Ʒ��� �������
	//if (newPosition.y - 1 > Engine::Get().Height())
	//{
	//	return;
	//}

	// ������ ������Ʈ ����.
	if (position == newPosition)
	{
		return;
	}

	//// ���� ��ġ Ȯ��.
	//Vector2 direction = newPosition - position;
	//position.x = direction.x >= 0 ? position.x : position.x + width - 1;

	//// Ŀ�� �̵�.
	//Utils::SetConsolePosition(position);

	//// ���ڿ� ���� ����ؼ� ���� ��ġ Ȯ���ؾ� ��.
	//std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}

int Actor::Width() const
{
	return width;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

bool Actor::TestIntersect(const Actor* const other)
{
	// AABB(Axis Aligned Bounding Box).
	// Note: ���� ���� ���� �� ���δ� ũ�Ⱑ ����(ũ�Ⱑ 1).
	//       ���� ������ �ּ�/�ִ� ��ġ�� �� ����ϸ� ��.

	// �� ������ x ��ǥ ����.
	int xMin = position.x;
	int xMax = position.x + width - 1;

	// �浹 ���� �ٸ� ������ x ��ǥ ����.
	int otherXMin = other->position.x;
	int otherXMax = other->position.x + other->width - 1;

	// �Ȱ�ġ�� ���� Ȯ��.

	// �ٸ� ������ ���� ��ǥ�� �� ������ ��ǥ���� �� �����ʿ� ������ �Ȱ�ħ.
	if (otherXMin > xMax)
	{
		return false;
	}

	// �ٸ� ������ ������ ��ǥ�� �� ���� ��ǥ���� �� ���ʿ� ������ �Ȱ�ħ.
	if (otherXMax < xMin)
	{
		return false;
	}

	// y ��ǥ�� ������ ���� Ȯ��.
	return position.y == other->position.y;
}

void Actor::ChangeImage(const char* newImage)
{
	// ���� �̹��� �޸� ����.
	SafeDelete(image);

	// ���ο� ���ڿ� ����.
	size_t length = strlen(newImage) + 1;
	image = new char[length];
	strcpy_s(image, length, newImage);
}

void Actor::Destroy()
{
	// �ߺ� ���� ���� ó��.
	if (isExpired)
	{
		return;
	}

	// ���� ��û �Ǿ��ٰ� ����.
	isExpired = true;

	// ������ ���� ��û.
	owner->DestroyActor(this);

	// ���� ��û�ƴٰ� �˸�.
	OnDestroy();
}

void Actor::OnDestroy()
{

}

void Actor::SetLifetime(float newLifetime)
{
	// �Է°� Ȯ��.
	if (newLifetime <= 0.0f)
	{
		return;
	}

	// ���� �ֱ� ����.
	lifetime = newLifetime;

	// �ڵ� ���� �ɼ� Ȱ��ȭ.
	autoDestroy = true;
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}