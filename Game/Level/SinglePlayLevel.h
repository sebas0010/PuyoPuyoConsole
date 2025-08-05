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
	int Explore();

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

	// ���� ���� ����
	int gameScore = 0;

	// ���� ���� ����
	int chainCount = 0;

	int chainBonus[10] = {
	0,   // 1����
	8,   // 2����
	16,  // 3����
	32,  // 4����
	64,  // 5����
	96,  // 6����
	128, // 7����
	160, // 8����
	192, // 9����
	224  // 10���� �̻�
	};

	// ���� ���ʽ� ���̺�
	int colorBonus[4] = {
		0,  // 1��
		3,  // 2��
		6,  // 3��
		12  // 4��
	};

	// �׷� ũ�� ���ʽ� ���̺�
	int groupBonus[6] = {
		0, // 4��
		2, // 5��
		3, // 6��
		4, // 7��
		5, // 8��
		6  // 9�� �̻� (�� ���Ĵ� �ʿ� �� Ȯ��)
	};
};