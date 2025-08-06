#pragma once

#include "Actor/Actor.h"
#include "Math/Color.h"
#include "Utils/Timer.h"

class MultiPlayPuyo : public Actor
{
	RTTI_DECLARATIONS(MultiPlayPuyo, Actor)
public:
	MultiPlayPuyo(Vector2 spawnPosition, int code, bool isMain, int player);

	void BeginPlay() override;
	void Tick(float deltaTime) override;
	void Render() override;

	// �߷� �ۿ� �Լ�
	void ApplyGravity(int newY);

	// 4�� �̻� ���� �Ǿ����Ƿ� ���� ���� ��ȣ�� �޾ƿ��� �Լ�
	void WillDestroyed();

	// code -> color ��ȯ �Լ�
	Color CodeToColor(int code);

	// sibling Getter, Setter
	void SetSibling(MultiPlayPuyo* sibling);
	MultiPlayPuyo* GetSibling() const;

	// player Getter
	int GetPlayer();

	// IsLanding Getter
	bool GetIsLanding();

	// code Getter
	int GetCode();

private:
	// �� ���͸� �����ϰ� �ִ� ������ �Լ��� ����ϱ� ���� �������̽�
	class IInteractPuyo* ownerInterface = nullptr;
	
	// �� �ѿ並 �����ϴ� ����� �÷��̾�1(����) ���� �÷��̾�2(������)���� �Ǵ��ϴ� ����
	int player = 0;

	// ���� ���� ��ư
	int leftButton = 0;

	// ������ ���� ��ư
	int rightButton = 0;

	// �Ʒ� ���� ��ư
	int downButton = 0;
	
	// ���� ���� �ѿ����� Ȯ��
	bool isControlling = true;

	// �Ʒ��� �̵��� �� �ִ��� ������ Ȯ��
	bool canMoveDown = true;

	// �߷��� �ۿ������� Ȯ��
	bool isLanding = false;

	// �߷��� �ۿ��� �� ������ ��ġ
	Vector2 landingTarget = Vector2::Zero;

	// �ѿ䰡 �������� �������� ����
	bool isMain = false;

	// ���� �� �������� ǥ���ϴ� ����
	bool isDestroying = false;

	// ���� ����Ʈ ī��Ʈ
	int effectCount = 0;

	// ���� ���彺 ���� �ڵ�
	int effectCode = 0;

	// ������ �ĺ��ڵ�. 1 : ����, 2 : �Ķ�, 3 : �ʷ�, 4 : ���, 5 : ����
	int code = 0;

	// ������ ����
	Color color = Color::White;

	// ������ �̹���
	const char* image1 = "(o_o)";
	const char* image2 = "(_^_)";

	// ���� ���� ������ �̹���
	const char* removingImage1 = "($_$)";
	const char* removingImage2 = "(_^_)";

	// �Ʒ� ����Ű�� ������ ���� ���� ��� �ϰ� �ӵ� : 0.8�ʿ� ��ĭ
	float landingSpeed = 0.8f;

	// �Ʒ� ����Ű�� ������ �ִ� ��� �ϰ� �ӵ� : 0.1�ʿ� ��ĭ
	float landingSpeedFast = 0.05f;

	// �� ĭ �̵��ϴµ� �ɸ��� �ð��� ������ �ִ� Ÿ�̸�
	Timer timer;

	// �ѿ� �� ��Ʈ���� ������
	MultiPlayPuyo* sibling = nullptr;

	// ����ѿ��� ��ġ���踦 ��Ÿ���� ���� 0 : �Ʒ�, 1 : ����, 2 : ��, 3 : ������
	int subPuyoDirection = 0;

};