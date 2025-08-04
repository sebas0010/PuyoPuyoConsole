#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "RTTI.h"

// ���� ����.
class Level;
class Engine_API Actor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(
		const char* image = "",
		Color color = Color::White,
		const Vector2& position = Vector2::Zero
	);
	virtual ~Actor();

	// �̺�Ʈ �Լ�.

	// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����).
	virtual void BeginPlay();

	// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
	virtual void Tick(float deltaTime);

	// �׸��� �Լ�.
	virtual void Render();

	// BeginPlay ȣ�� ���� Ȯ��.
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	// ��ġ ����/�� �д� �Լ�.
	void SetPosition(const Vector2& newPosition);
	Vector2 Position() const;

	// ���ڿ� ���� ��ȯ.
	int Width() const;

	// Sorting Order ����.
	void SetSortingOrder(unsigned int sortingOrder);

	// ���ʽ� ����.
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	// �浹 Ȯ�� ��û �Լ� (������ AABB ����).
	bool TestIntersect(const Actor* const other);

	// ������ �̹��� �� ���� �Լ�.
	void ChangeImage(const char* newImage);

	// ��ü ���� �Լ�.
	void Destroy();

	// ��ü�� �����Ǳ� ������ ȣ��Ǵ� �Լ�.
	virtual void OnDestroy();

	// ���� �ֱ� ���� �Լ�.
	void SetLifetime(float newLifetime);

	// ���� ���� ��û �Լ�.
	void QuitGame();

protected:
	// ��ü�� ��ġ.
	Vector2 position;

	// �׸� ��.
	//char image = ' ';
	char* image = nullptr;

	// ���ڿ� ����.
	int width = 0;

	// �ؽ�Ʈ ���� ��.
	Color color;

	// BeginPlay ȣ���� �Ǿ����� Ȯ��.
	bool hasBeganPlay = false;

	// ���� ����.
	unsigned int sortingOrder = 0;

	// ���Ͱ� Ȱ�� �������� �˷��ִ� ����.
	bool isActive = true;

	// ���� ��û�ƴ��� �˷��ִ� ����.
	bool isExpired = false;

	// ���� �ֱ� (����: ��).
	float lifetime = 0.0f;

	// �� �÷��׸� true�� �����ϸ� ���� �ֱ⸦ ����� �ڵ� ����.
	bool autoDestroy = false;

	// ���� ����(���ʽ�).
	Level* owner = nullptr;
};