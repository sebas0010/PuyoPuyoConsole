#pragma once

/*
* Delegate Ŭ����.
* - Ŭ����(�Ǵ� ����ü) �޼ҵ带 ����� �ݹ� ó���� �����ϵ��� ���ִ� Ŭ����.
* - �Ϲ� �Լ��� �޼ҵ� ��� �Ұ�.
* - �Ϲ� �Լ���/Ŭ����(����ü)�� �޼ҵ带 ��� Ȱ���� �� �ְ� �Ϸ��� ������ �������� ������ ��.
*/

#include "Core.h"

// ��������Ʈ���� ����� �Լ� ������ Ÿ�� ����.
using Function = void(*)(void*);

// ��������Ʈ Ŭ����.
struct Engine_API Delegate
{
	// ��������Ʈ���� ������ �ν��Ͻ�.
	void* instance = nullptr;

	// ������ �޼ҵ� ������.
	Function function = nullptr;

	Delegate() = default;

	Delegate(void* const instance, Function function)
		: instance(instance), function(function)
	{
	}

	// ��������Ʈ ȣ�� �Լ�.
	void Invoke()
	{
		// �Լ� ȣ�� ���� ���� Ȯ��.
		if (!instance || !function)
		{
			return;
		}

		// �ݹ� �Լ� ȣ��.
		function(instance);
	}

	// ȣ�� ������ �����ε�.
	void operator()()
	{
		Invoke();
	}
};