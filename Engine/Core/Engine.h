#pragma once

#include "Core.h"
#include "Input.h"
#include <Windows.h>

// 엔진 설정 구조체.
struct EngineSettings
{
	// 타겟 프레임 속도.
	float framerate = 120.0f;
};

class Level;
class Engine_API Engine
{
public:

	// 생성자.
	Engine();

	// 소멸자.
	virtual ~Engine();

	// 엔진 실행 함수.
	void Run();

	// 레벨 추가 함수.
	void AddLevel(Level* newLevel);

	// 메모리 해제 함수.
	virtual void CleanUp();

	// 종료 함수.
	void Quit();

	// 싱글톤 접근 함수.
	static Engine& Get();

private:
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();


protected:
	// 엔진 종료 플래그.
	bool isQuit = false;

	// 메인 레벨.
	Level* mainLevel = nullptr;

	// 입력 관리자.
	Input input;

	// 엔진 설정.
	EngineSettings settings;

	// 싱글톤 변수.
	static Engine* instance;
};