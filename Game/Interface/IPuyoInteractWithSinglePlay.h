#pragma once

#include "Math/Vector2.h"
#include "Actor/Puyo.h"

// 뿌요가 레벨의 일정 함수를 사용할 때 사용할 인터페이스.
class IPuyoInteractWithSinglePlay
{
public:
	virtual bool CanPuyoMove(const Puyo& puyo, const Vector2& newPosition) = 0;
	virtual void PuyoLanded(Puyo* puyo1, Puyo* puyo2) = 0;
	virtual float GetLandingSpeed() = 0;
	virtual int GetScreenMinY() = 0;
};