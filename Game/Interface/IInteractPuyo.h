#pragma once

#include "Math/Vector2.h"
#include "Actor/MultiPlayPuyo.h"

// �ѿ䰡 �̵��� �� �ִ��� Ȯ���� �� ����� �������̽�.
class IInteractPuyo
{
public:
	virtual bool CanPuyoMove(MultiPlayPuyo* puyo, Vector2 newPosition) = 0;
	virtual void PuyoLanded(MultiPlayPuyo* puyo1, MultiPlayPuyo* puyo2) = 0;
	virtual int GetScreenMinY(int player) = 0;
};