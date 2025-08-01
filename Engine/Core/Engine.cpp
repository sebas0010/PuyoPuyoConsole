#include "Engine.h"
#include <iostream>
#include <Windows.h>

#include "Level/Level.h"
#include "Utils/Utils.h"
#include "Input.h"

// 정적 변수 초기화.
Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		// Engine의 메모리 해제.
		//Engine::Get().~Engine();
		Engine::Get().CleanUp();
		return false;
	}

	return false;
}

Engine::Engine()
{
	instance = this;

	// 콘솔 커서 끄기.
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	// 콘솔 창 이벤트 등록.
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);

	// 랜덤 종자값(seed) 설정.
	srand(static_cast<unsigned int>(time(nullptr)));
}

Engine::~Engine()
{
	CleanUp();
}

void Engine::Run()
{
	// 밀리 세컨드 단위로 현재 시간을 알려줌.
	//float currentTime = timeGetTime();
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// 하드웨어 시계의 정밀도(주파수) 가져오기.
	// 나중에 초로 변환하기 위해.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 타겟 프레임.
	float targetFrameRate 
		= settings.framerate == 0.0f ? 60.0f : settings.framerate;

	// 타겟 한 프레임 시간.
	float oneFrameTime = 1.0f / targetFrameRate;

	// GameLoop.
	while (true)
	{
		// 엔진 종료 여부 확인.
		if (isQuit)
		{
			// 루프 종료.
			break;
		}

		// 프레임 시간 계산.
		// (현재 시간 - 이전 시간) / 주파수 = 초단위.
		QueryPerformanceCounter(&currentTime);

		// 프레임 시간.
		float deltaTime = 
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)frequency.QuadPart;

		// 입력은 최대한 빨리.
		input.ProcessInput();

		// 고정 프레임.
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// 시간 업데이트.
			previousTime = currentTime;

			// 현재 프레임의 입력을 기록.
			input.SavePreviouseKeyStates();

			// 이전 프레임에 추가 및 삭제 요청된 액터 처리.
			if (mainLevel)
			{
				mainLevel->ProcessAddAndDestroyActors();
			}
		}
	}

	// 정리(텍스트 색상 원래대로 돌려놓기).
	Utils::SetConsoleTextColor(
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);
}

void Engine::AddLevel(Level* newLevel)
{
	mainLevel = newLevel;
}

void Engine::CleanUp()
{
	// 레벨 삭제.
	SafeDelete(mainLevel);
}

void Engine::Quit()
{
	// 종료 플래그 설정.
	isQuit = true;
}

Engine& Engine::Get()
{
	return *instance;
}

void Engine::BeginPlay()
{
	if (mainLevel)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	// 레벨 업데이트.
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}
}

void Engine::Render()
{
	Utils::SetConsoleTextColor(
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);

	if (mainLevel)
	{
		mainLevel->Render();
	}
}