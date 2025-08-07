#pragma once

#include "Level/Level.h"
#include "Interface/IInteractPuyo.h"


class MultiPlayLevel : public Level, public IInteractPuyo
{
	RTTI_DECLARATIONS(MultiPlayLevel, Level)
public:
	MultiPlayLevel();
	void Tick(float deltaTime) override;
	void Render() override;

	// ���� �׸��� �Լ�
	void DrawMap(Vector2 drawPosition);

	// �ѿ� �� �߰� �Լ�
	void CreateNextPuyo(int player);

	// ���� ���۵� �ѿ並 �׸��� �Լ�
	void DrawNextPuyo(Vector2 drawPosition, int player);

	// ����� ���� �ѿ� ������ �׸��� �Լ�
	void DrawDisturbGauge(Vector2 drawPosition, int player);

	// ���� �ѿ� ���� �Լ�
	void SpawnDisturbPuyo(int player, int disturbPuyoCount);

	// �ѿ� �� ���� �Լ�
	void SpawnPuyo(int player);

	// ���ο� ��ġ�� �ѿ䰡 �̵� �������� Ȯ���ϴ� �Լ� 
	bool CanPuyoMove(MultiPlayPuyo* puyo, Vector2 newPosition) override;

	// �ѿ䰡 ������ �Ŀ� Grid�� �߰��ϴ� �Լ�
	void PuyoLanded(MultiPlayPuyo* puyo1, MultiPlayPuyo* puyo2) override;

	// �ѿ信�� ��ũ���� ���� �� ��ǥ�� �˷��ִ� �Լ�
	int GetScreenMinY(int player) override;

	// �߷� �ۿ� �Լ�
	void Gravity(int player);
	
	// ��� �߷� �ۿ��� �������� Ȯ���ϴ� �Լ�
	bool AllGravityFinished(int player);

	// �׸��� Ž�� �� 4�� �̻� ����� �ѿ䰡 ������ �����ϴ� �Լ�
	int Explore(int player);
private:

	// �÷��̾ ���� ������ ������ ��ǥ
	int screenMinX[2] = { 6, 60 };
	int screenMaxX[2] = { 35, 89 };
	int screenMinY[2] = { 5, 5 };
	int screenMaxY[2] = { 28, 28 };

	// �ѿ� �̹���
	const char* puyoImage1 = "(o_o)";
	const char* puyoImage2 = "(_^_)";

	// �÷��̾ �ѿ並 ���� ������ �Ǵ��ϴ� ����
	bool isPuyoLanding[2] = { false };

	// �÷��̾��� �������� ������ �ѿ� ���� �ڵ�
	int nextPuyoCode[2][2] = {0};
	Color nextPuyoColor[2][2] = {Color::White};

	// ������ �ѿ���� �����ϴ� �Լ�
	MultiPlayPuyo* puyoGrid[2][6][24] = { nullptr };

	// �߷��� �ۿ������� ��Ÿ���� ����
	bool isGravityProcessing[2] = { false };

	// �ѿ� ������ ���������� ��Ÿ���� ����
	bool isRemoving[2] = {false};

	// �ѿ� ���� ����Ʈ ���ð��� ���� Ÿ�̸�
	Timer removingTimer[2];

	// ��뿡�� �����ϴ� �����
	int attackDamage[2] = { 0 };

	// ���� ����ܰ� �����(��� ���Ⱑ ������ attackDamage�� �Ѿ)
	int curAttackDamage[2] = { 0 };

	// ���� �ѿ� ���� �ܰ�
	bool isDisturbProcessing[2] = { false };
	
	// ���� �ѿ� ó�� ���ð�
	Timer disturbTimer[2];;

	// ���� ���� �÷���
	int gameOver = -1;

	// ���� ���� ����
	int chainCount[2] = { 0 };

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