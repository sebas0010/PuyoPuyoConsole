#pragma once

#include "Math/Vector2.h"
#include "Actor/Puyo.h"

// �ѿ䰡 ������ ���� �Լ��� ����� �� ����� �������̽�.
class IPuyoInteractWithSinglePlay
{
public:
	virtual bool CanPuyoMove(const Puyo& puyo, const Vector2& newPosition) = 0;
	virtual void PuyoLanded(Puyo* puyo1, Puyo* puyo2) = 0;
	virtual float GetLandingSpeed() = 0;
	virtual int GetScreenMinY() = 0;
};