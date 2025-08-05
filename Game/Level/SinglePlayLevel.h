#pragma once

#include "Level/Level.h"
#include "Interface/ICanPuyoMove.h"


class SinglePlayLevel : public Level, public ICanPuyoMove
{
	RTTI_DECLARATIONS(SinglePlayLevel, Level)
public:
	SinglePlayLevel();
	void Tick(float deltaTime) override;
	void Render() override;

	// ���� �׸��� �Լ�
	void DrawMap(Vector2 drawPosition);

	// ���� ���۵� �ѿ並 �����ϴ� �Լ�
	void CreateNextPuyo();

	// ���� ���۵� �ѿ並 �׸��� �Լ�
	void DrawNextPuyo(Vector2 drawPosition);

	// �ѿ� ���� �Լ�
	void SpawnPuyo();

	// ���ο� ��ġ�� �ѿ䰡 �̵� �������� Ȯ���ϴ� �Լ� 
	bool CanPuyoMove(const Puyo& puyo, const Vector2& newPosition);

	// �ѿ䰡 ������ �Ŀ� Grid�� �߰��ϴ� �Լ�
	void PuyoLanded(Puyo* puyo1, Puyo* puyo2);

	// �ѿ� �׸��带 Ž���ϸ� �߷� �����ϴ� �Լ�
	void Gravity();

	// ��� �ѿ� �׸����� �߷� �ۿ��� �������� �����ϴ� �Լ�
    bool AllGravityFinished();

	// �ѿ� �׸��带 Ž���ϸ� ���� �� 4���� ����� ��� �Ͷ߸��� �Լ�
	void Explore();

	// �÷��̾ ���� ������ ������ ��ǥ
	int screenMinX = 6;
	int screenMaxX = 35;
	int screenMinY = 3;
	int screenMaxY = 26;

private:
	// �ѿ並 ���� ������ �Ǵ��ϱ� ���� ����
	bool isPuyoLanding = false;

	// �ѿ� ���� �ĸ� ó�������� �Ǵ��ϱ� ���� ����
	bool isProcessing = false;

	// ������ �ѿ���� �����ϴ� �Լ�
	Puyo* puyoGrid[6][12] = { nullptr };

	// �ѿ� �̹���
	const char* image1 = "(o_o)";
	const char* image2 = "(_^_)";

	// ���� ������ �ѿ��� ���� �ڵ�
	int nextPuyoCode1 = 0;
	int nextPuyoCode2 = 0;
	Color nextPuyoColor1 = Color::White;
	Color nextPuyoColor2 = Color::White;
};