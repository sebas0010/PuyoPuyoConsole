#pragma once

#include "Level/Level.h"
#include "Interface/ICanPuyoMove.h"


class SinglePlayLevel : public Level, public ICanPuyoMove
{
	RTTI_DECLARATIONS(SinglePlayLevel, Level)
public:

	void Tick(float deltaTime) override;
	void Render() override;

	void SpawnPuyo();

	// ���ο� ��ġ�� �ѿ䰡 �̵� �������� Ȯ���ϴ� �Լ� 
	bool CanPuyoMove(const Puyo& puyo, const Vector2& newPosition);

	// �ѿ䰡 ������ �Ŀ� Grid�� �߰��ϴ� �Լ�
	void PuyoLanded(Puyo* puyo1, Puyo* puyo2);

	// �ѿ� �׸��带 Ž���ϸ� �߷� �����ϴ� �Լ�
	void Gravity();

	// �ѿ� �׸��带 Ž���ϸ� ���� �� 4���� ����� ��� �Ͷ߸��� �Լ�
	void Explore();

	// �÷��̾ ���� ������ ������ ��ǥ
	int screenMinX = 6;
	int screenMaxX = 35;
	int screenMinY = 3;
	int screenMaxY = 26;


private:
	bool isPuyoLanding = false;

	// ������ �ѿ���� �����ϴ� �Լ�
	Puyo* puyoGrid[6][12] = { nullptr };
};