#pragma once

#include "Core.h"
#include "Delegate.h"
#include <unordered_map>
#include <Windows.h>
#include <vector>

class Engine_API Input
{
	// friend ����.
	friend class Engine;

	// Ű�Է� Ȯ���� ���� ����ü ����.
	struct KeyState
	{
		// ���� �����ӿ� Ű�� ���ȴ��� ����.
		bool isKeyDown = false;

		// ���� �����ӿ� Ű�� ���ȴ��� ����.
		bool previouseKeyDown = false;
	};

public:
	Input();

	// Ű Ȯ�� �Լ�.
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	static Input& Get();

	// Ű ���� �̺�Ʈ�� ������ �Լ��� ����� �� ����� �Լ�.
	template<typename T, void (T::*Method)()>
	void RegisterKeydownEvent(int keyCode, T* object)
	{
		// ��������Ʈ�� ������ ��ü�� Actor�� �ڼ����� Ȯ��.
		if (!object)
		{
			// Visual Studio ���(Output) â�� ���� �޽��� ���.
			OutputDebugStringA("�Ϲ� �Լ��� �޼ҵ� ����� �Ұ����մϴ�.");

			// Debug ��忡�� �Ͻ�������ų �� ����ϴ� �Լ�.
			__debugbreak();
		}

		// ��������Ʈ ��ü ����.
		Delegate delegate(object, [](void* instance)
			{
				// ����ȯ(Down-Casting) �� �޼ҵ� ȣ��.
				T* derived = static_cast<T*>(instance);
				(derived->*Method)();
			});

		// �ݹ鿡 ��������Ʈ �߰�.
		keydownCallbacks[keyCode].emplace_back(delegate);
	}

	// Ű ���� ���� �̺�Ʈ�� ������ �Լ��� ����� �� ����� �Լ�.
	template<typename T, void (T::* Method)()>
	void RegisterKeyupEvent(int keyCode, T* object)
	{
		// ��������Ʈ�� ������ ��ü�� Actor�� �ڼ����� Ȯ��.
		if (!object)
		{
			// Visual Studio ���(Output) â�� ���� �޽��� ���.
			OutputDebugStringA("�Ϲ� �Լ��� �޼ҵ� ����� �Ұ����մϴ�.");

			// Debug ��忡�� �Ͻ�������ų �� ����ϴ� �Լ�.
			__debugbreak();
		}

		// ��������Ʈ ��ü ����.
		Delegate delegate(object, [](void* instance)
			{
				// ����ȯ(Down-Casting) �� �޼ҵ� ȣ��.
				T* derived = static_cast<T*>(instance);
				(derived->*Method)();
			});

		// �ݹ鿡 ��������Ʈ �߰�.
		keyupCallbacks[keyCode].emplace_back(delegate);
	}

	// Ű ���� �ݺ� �̺�Ʈ�� ������ �Լ��� ����� �� ����� �Լ�.
	template<typename T, void (T::* Method)()>
	void RegisterKeyrepeatEvent(int keyCode, T* object)
	{
		// ��������Ʈ�� ������ ��ü�� Actor�� �ڼ����� Ȯ��.
		if (!object)
		{
			// Visual Studio ���(Output) â�� ���� �޽��� ���.
			OutputDebugStringA("�Ϲ� �Լ��� �޼ҵ� ����� �Ұ����մϴ�.");

			// Debug ��忡�� �Ͻ�������ų �� ����ϴ� �Լ�.
			__debugbreak();
		}

		// ��������Ʈ ��ü ����.
		Delegate delegate(object, [](void* instance)
			{
				// ����ȯ(Down-Casting) �� �޼ҵ� ȣ��.
				T* derived = static_cast<T*>(instance);
				(derived->*Method)();
			});

		// �ݹ鿡 ��������Ʈ �߰�.
		keyrepeatCallbacks[keyCode].emplace_back(delegate);
	}

private:
	void ProcessInput();
	void DispatchCallbacks();
	void SavePreviouseKeyStates();

private:

	// Ű �Է� ���� ���� ����.
	KeyState keyStates[256] = { };

	// Ű�Է� ���� �̺�Ʈ.
	std::unordered_map<int, std::vector<Delegate>> keydownCallbacks;
	std::unordered_map<int, std::vector<Delegate>> keyupCallbacks;
	std::unordered_map<int, std::vector<Delegate>> keyrepeatCallbacks;

	static Input* instance;
};