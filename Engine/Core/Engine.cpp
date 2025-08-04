#include "Engine.h"
#include <iostream>
#include <Windows.h>

#include "Level/Level.h"
#include "Utils/Utils.h"
#include "Input.h"
#include "Render/ScreenBuffer.h"

// ���� ���� �ʱ�ȭ.
Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
		// Engine�� �޸� ����.
		//Engine::Get().~Engine();
		Engine::Get().Quit();
		return true;
	}

	return false;
}

Engine::Engine()
{
	instance = this;

	// �ܼ� Ŀ�� ����.
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);
	
	// ���� ���� �ε�.
	LoadEngineSettings();

	// ���� ���ڰ�(seed) ����.
	srand(static_cast<unsigned int>(time(nullptr)));

	// �̹��� ���� ���� / �ֿܼ� ���� ���� ����.
	Vector2 screenSize(settings.width, settings.height);
	//imageBuffer = new CHAR_INFO[(screenSize.x + 1) * screenSize.y + 1];
	//imageBuffer = new ImageBuffer[(screenSize.x + 1) * screenSize.y + 1];
	imageBuffer = new ImageBuffer((screenSize.x + 1) * screenSize.y + 1);
	//charInfo = new CHAR_INFO[(screenSize.x + 1) * screenSize.y + 1];

	// ���� �ʱ�ȭ (���� ����).
	ClearImageBuffer();

	// �� ���� ���� ����.
	renderTargets[0] = new ScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE), screenSize);
	renderTargets[1] = new ScreenBuffer(screenSize);

	// ���� ��ȯ.
	Present();

	// �ܼ� â �̺�Ʈ ���.
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);

	// cls ȣ��.
	system("cls");
}

Engine::~Engine()
{
	CleanUp();
}

void Engine::Run()
{
	// �и� ������ ������ ���� �ð��� �˷���.
	//float currentTime = timeGetTime();
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// �ϵ���� �ð��� ���е�(���ļ�) ��������.
	// ���߿� �ʷ� ��ȯ�ϱ� ����.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// Ÿ�� ������.
	float targetFrameRate 
		= settings.framerate == 0.0f ? 60.0f : settings.framerate;

	// Ÿ�� �� ������ �ð�.
	float oneFrameTime = 1.0f / targetFrameRate;

	// GameLoop.
	while (true)
	{
		// ���� ���� ���� Ȯ��.
		if (isQuit)
		{
			// ���� ����.
			break;
		}

		// ������ �ð� ���.
		// (���� �ð� - ���� �ð�) / ���ļ� = �ʴ���.
		QueryPerformanceCounter(&currentTime);

		// ������ �ð�.
		float deltaTime = 
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)frequency.QuadPart;

		// �Է��� �ִ��� ����.
		input.ProcessInput();

		// ���� ������.
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			input.DispatchCallbacks();
			Tick(deltaTime);
			Render();

			// �ð� ������Ʈ.
			previousTime = currentTime;

			// ���� �������� �Է��� ���.
			input.SavePreviouseKeyStates();

			// ���� �����ӿ� �߰� �� ���� ��û�� ���� ó��.
			if (mainLevel)
			{
				mainLevel->ProcessAddAndDestroyActors();
			}
		}
	}

	// ����(�ؽ�Ʈ ���� ������� ��������).
	Utils::SetConsoleTextColor(
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);
}

void Engine::WriteToBuffer(
	const Vector2& position, 
	const char* image, 
	Color color, 
	int sortingOrder)
{
	// ���ڿ� ����.
	int length = static_cast<int>(strlen(image));
	int finalLength = length;

	// ���� ��ġ.
	Vector2 finalPosition = position;

	// @Incomplte: ȭ�� ��� ���ڸ� ���� ���� ������.
	// ȭ�� �������� ������� Ȯ��.
	char* finalImage = nullptr;
	bool originalImageChanged = false;
	if (position.x < 0)
	{
		// ���� ��ġ(��� ��ǥ)�� �ִ� ���� �� ���.
		finalLength = length + position.x;

		// �޸� �Ҵ�/�ʱ�ȭ.
		finalImage = new char[finalLength + 1];
		memset(finalImage, 0, finalLength + 1);

		// �ʿ��� ���ڸ� ����.
		strcpy_s(finalImage, finalLength + 1, image + (length - finalLength));

		// ���� ��ġ ����.
		finalPosition.x = 0;

		// ���� �̹���(���ڿ�) ���� ����ƴٰ� ǥ��.
		originalImageChanged = true;
	}

	// @Incomplete: ȭ�� ��� ���ڸ� ���� ���� �ۼ���.
	// ȭ�� ���������� ������� Ȯ��.
	if (position.x + length > settings.width)
	{
		// ���� ��ġ(ȭ�� ����)�� �ִ� ���� �� ���.
		finalLength = settings.width - position.x;

		// �޸� �Ҵ�/�ʱ�ȭ.
		finalImage = new char[finalLength + 1];
		memset(finalImage, 0, finalLength + 1);

		// �ʿ��� ���ڸ� ����.
		memcpy(finalImage, image, finalLength);

		// ���� �̹���(���ڿ�) ���� ����ƴٰ� ǥ��.
		originalImageChanged = true;
	}

	// ���ڿ� ���.
	for (int ix = 0; ix < finalLength; ++ix)
	{
		// ����� ���� ��ġ.
		// @Incomplete: ȭ�� ���� ũ�� �� �Ѿ�� ����ó�� �ʿ���.
		int index = (position.y * (settings.width)) + finalPosition.x + ix;

		// �׸����� ����� sortingOrder�� ���� �׷����ִ� ������ ������ ������ �ȱ׸���. 
		// (���ڰ� ��ġ�� ����� ó��).
		if (imageBuffer->sortingOrderArray[index] > sortingOrder)
		{
			continue;
		}

		// ���ۿ� ���� ���.
		// ���� �̹��� ���� ����� ��쿡�� ����� ���ڿ��� ���ۿ� ���.
		if (originalImageChanged)
		{
			imageBuffer->charInfoArray[index].Char.AsciiChar = finalImage[ix];
		}

		// ���ڿ� ������ �����ٸ� ���� ���ڿ��� ���ۿ� ���.
		else
		{
			imageBuffer->charInfoArray[index].Char.AsciiChar = image[ix];
		}
		
		// ���� ���.
		imageBuffer->charInfoArray[index].Attributes = (WORD)color;
		
		// �X�� ���.
		imageBuffer->sortingOrderArray[index] = sortingOrder;
	}

	// finalImage�� ������ ���, �޸� ����.
	if (originalImageChanged && finalImage)
	{
		SafeDelete(finalImage);
	}
}

void Engine::AddLevel(Level* newLevel)
{
	// ������ �ִ� ������ ����.
	if (mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

void Engine::CleanUp()
{
	// ���� ����.
	SafeDelete(mainLevel);

	// ���� ���� ����.
	//SafeDeleteArray(imageBuffer);
	//SafeDeleteArray(charInfo);
	SafeDelete(imageBuffer);

	// ���� Ÿ�� ����.
	SafeDelete(renderTargets[0]);
	SafeDelete(renderTargets[1]);
}

void Engine::Quit()
{
	// ���� �÷��� ����.
	isQuit = true;
}

Engine& Engine::Get()
{
	return *instance;
}

int Engine::Width() const
{
	return settings.width;
}

int Engine::Height() const
{
	return settings.height;
}

void Engine::OnInitialized()
{

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
	// ���� ������Ʈ.
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}
}

void Engine::Clear()
{
	ClearImageBuffer();
	GetRenderer()->Clear();
}

void Engine::Render()
{
	// ȭ�� �����.
	Clear();

	// ���� �׸���.
	if (mainLevel)
	{
		mainLevel->Render();
	}

	// ����ۿ� ������ ����.
	//GetRenderer()->Render(imageBuffer);
	GetRenderer()->Render(imageBuffer->charInfoArray);

	// ���� ��ȯ.
	Present();
}

void Engine::Present()
{
	// ���� ��ȯ.
	SetConsoleActiveScreenBuffer(GetRenderer()->buffer);

	// �ε��� ������. 1->0, 0->1.
	currentRenderTargetIndex = 1 - currentRenderTargetIndex;
}

void Engine::PresentImmediately()
{
	// ����ۿ� ������ ����.
	//GetRenderer()->Render(imageBuffer);
	GetRenderer()->Render(imageBuffer->charInfoArray);

	Present();
}

void Engine::LoadEngineSettings()
{
	// ���� ���� ���� ����.
	FILE* file = nullptr;
	fopen_s(&file, "../Settings/EngineSettings.txt", "rt");
	if (file == nullptr)
	{
		std::cout << "Failed to load engine settings.\n";
		__debugbreak();
		return;
	}

	// �ε�.

	// FP(File Position) �����͸� ���� �ڷ� �ű��.
	fseek(file, 0, SEEK_END);

	// �� ��ġ ���ϱ�.
	size_t fileSize = ftell(file);

	// �ٽ� ù ��ġ�� �ǵ�����.
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	// ���� ������ ������ ���� �Ҵ�.
	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);

	// ���� �б�.
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// �Ľ�(Parcing, ���� �ؼ�->�ʿ��� ������ ��� ����).
	char* context = nullptr;
	char* token = nullptr;

	token = strtok_s(buffer, "\n", &context);

	// ���� �м�.
	while (token != nullptr)
	{
		// Ű/�� �и�.
		char header[10] = { };

		// �Ʒ� ������ ����� �����Ϸ��� Ű�� �� ������ ��ĭ�� �־�� ��.
		sscanf_s(token, "%s", header, 10);

		// ��� ���ڿ� ��.
		if (strcmp(header, "framerate") == 0)
		{
			sscanf_s(token, "framerate = %f", &settings.framerate);
		}
		else if (strcmp(header, "width") == 0)
		{
			sscanf_s(token, "width = %d", &settings.width);
		}
		else if (strcmp(header, "height") == 0)
		{
			sscanf_s(token, "height = %d", &settings.height);
		}

		// �� ������ �и�.
		token = strtok_s(nullptr, "\n", &context);
	}


	// ���� ����.
	SafeDeleteArray(buffer);

	// ���� �ݱ�.
	fclose(file);
}

ScreenBuffer* Engine::GetRenderer() const
{
	return renderTargets[currentRenderTargetIndex];
}

void Engine::ClearImageBuffer()
{
	// ���� ���� �����.
	for (int y = 0; y < settings.height; ++y)
	{
		for (int x = 0; x < settings.width; ++x)
		{
			int index = (y * (settings.width)) + x;
			CHAR_INFO& buffer = imageBuffer->charInfoArray[index];
			buffer.Char.AsciiChar = ' ';
			buffer.Attributes = 0;
			imageBuffer->sortingOrderArray[index] = -1;
		}

		// �� �� ���� ���� ���� �߰�.
		int index = (y * (settings.width)) + settings.width;
		CHAR_INFO& buffer = imageBuffer->charInfoArray[index];
		buffer.Char.AsciiChar = '\n';
		buffer.Attributes = 0;
		imageBuffer->sortingOrderArray[index] = -1;
	}

	// �������� �� ���� �߰�.
	int index = (settings.width) * settings.height + 1;
	CHAR_INFO& buffer = imageBuffer->charInfoArray[index];
	buffer.Char.AsciiChar = '\0';
	buffer.Attributes = 0;
	imageBuffer->sortingOrderArray[index] = -1;
}