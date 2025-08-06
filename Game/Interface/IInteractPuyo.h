#pragma once

#include "Math/Vector2.h"
#include "Actor/MultiPlayPuyo.h"

// 뿌요가 이동할 수 있는지 확인할 때 사용할 인터페이스.
class IInteractPuyo
{
public:
	virtual bool CanPuyoMove(MultiPlayPuyo* puyo, Vector2 newPosition) = 0;
	virtual void PuyoLanded(MultiPlayPuyo* puyo1, MultiPlayPuyo* puyo2) = 0;
	virtual int GetScreenMinY(int player) = 0;
};