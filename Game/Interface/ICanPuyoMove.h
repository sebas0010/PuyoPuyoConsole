#pragma once

#include "Math/Vector2.h"
#include "Actor/Puyo.h"

// �ѿ䰡 �̵��� �� �ִ��� Ȯ���� �� ����� �������̽�.
class ICanPuyoMove
{
public:
	virtual bool CanPuyoMove(const Puyo& puyo, const Vector2& newPosition) = 0;
	virtual void PuyoLanded(Puyo* puyo1, Puyo* puyo2) = 0;
};