#pragma once

#include "Math/Vector2.h"
#include "Actor/Puyo.h"

// 뿌요가 이동할 수 있는지 확인할 때 사용할 인터페이스.
class ICanPuyoMove
{
public:
	virtual bool CanPuyoMove(const Puyo& puyo, const Vector2& newPosition) = 0;
	virtual void PuyoLanded(Puyo* puyo1, Puyo* puyo2) = 0;
};