#include "Input.h"
#include <Windows.h>

// static ���� ����.
Input* Input::instance = nullptr;

Input::Input()
{
	// �̱��� ������ ���� instance ���� ����.
	instance = this;
}

void Input::ProcessInput()
{
	// Ű �Է� Ȯ��.
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown = GetAsyncKeyState(ix) & 0x8000;
	}
}

void Input::DispatchCallbacks()
{
	// Ű ���� �̺�Ʈ ����.
	if (keydownCallbacks.size() > 0)
	{
		for (std::pair<const int, std::vector<Delegate>>& pair : keydownCallbacks)
		{
			// Ű ���� Ȯ��.
			if (GetKeyDown(pair.first))
			{
				// Ű ���� �̺�Ʈ�� �߻��� ���, �ݹ� �Լ� ȣ��.
				for (Delegate& delegate : pair.second)
				{
					delegate();
				}
			}
		}
	}

	// Ű ���� ���� �̺�Ʈ ����.
	if (keyupCallbacks.size() > 0)
	{
		for (std::pair<const int, std::vector<Delegate>>& pair : keyupCallbacks)
		{
			// Ű ���� ���� Ȯ��.
			if (GetKeyUp(pair.first))
			{
				// Ű ���� ���� �̺�Ʈ�� �߻��� ���, �ݹ� �Լ� ȣ��.
				for (Delegate& delegate : pair.second)
				{
					delegate();
				}
			}
		}
	}

	// Ű ���� �ݺ� �̺�Ʈ ����.
	if (keyrepeatCallbacks.size() > 0)
	{
		for (std::pair<const int, std::vector<Delegate>>& pair : keyrepeatCallbacks)
		{
			// Ű ���� �ݺ� �̺�Ʈ Ȯ��.
			if (GetKey(pair.first))
			{
				// Ű ���� �ݺ� �̺�Ʈ�� �߻��� ���, �ݹ� �Լ� ȣ��.
				for (Delegate& delegate : pair.second)
				{
					delegate();
				}
			}
		}
	}
}

void Input::SavePreviouseKeyStates()
{
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].previouseKeyDown = keyStates[ix].isKeyDown;
	}
}

bool Input::GetKey(int keyCode)
{
	return keyStates[keyCode].isKeyDown;
}

bool Input::GetKeyDown(int keyCode)
{
	return !keyStates[keyCode].previouseKeyDown
		&& keyStates[keyCode].isKeyDown;
}

bool Input::GetKeyUp(int keyCode)
{
	return keyStates[keyCode].previouseKeyDown
		&& !keyStates[keyCode].isKeyDown;
}

Input& Input::Get()
{
	return *instance;
}