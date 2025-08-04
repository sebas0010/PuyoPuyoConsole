#pragma once

#include <Windows.h>
#include "Math/Vector2.h"
#include "Math/Color.h"
//#include <iostream>

// ������Ʈ���� �پ��ϰ� ����� ��ƿ��Ƽ �Լ� ����.
namespace Utils
{
	// �� ���� ���� �ٲ� �� ����ϴ� �Լ�.
	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	// �ܼ� ��� �ڵ� �������� �Լ�.
	inline HANDLE GetConsoleHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	// �ܼ� Ŀ�� ��ġ �̵� �Լ�.
	inline void SetConsolePosition(COORD coord)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleCursorPosition(handle, coord);
	}

	inline void SetConsolePosition(const Vector2& position)
	{
		SetConsolePosition(static_cast<COORD>(position));
	}

	// �ܼ� �ؽ�Ʈ ���� ���� �Լ�.
	inline void SetConsoleTextColor(WORD color)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleTextAttribute(handle, color);
	}

	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextColor(static_cast<WORD>(color));
	}

	// ���� ���� �Լ�.
	inline int Random(int min, int max)
	{
		// max�� min�� ���� ���ϱ�.
		int diff = (max - min) + 1;
		return ((diff * rand()) / (RAND_MAX + 1)) + min;
	}

	inline float RandomFloat(float min, float max)
	{
		// 0 ~ 1 ������ ���� ���ϱ�.
		float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		return random * (max - min) + min;
	}
}