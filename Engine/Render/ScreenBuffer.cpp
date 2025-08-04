#include "ScreenBuffer.h"
#include <iostream>

ScreenBuffer::ScreenBuffer(const Vector2& screenSize)
	: screenSize(screenSize)
{
	// ���� ��� ���� (�б�/����).
	unsigned long accessMode = GENERIC_READ | GENERIC_WRITE;

	// ���� ��� ���� (���� �����).
	unsigned long shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;

	// �ܼ� ���� ����.
	buffer = CreateConsoleScreenBuffer(accessMode, shareMode, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// ����ó��: ���� ���� ����.
	if (buffer == INVALID_HANDLE_VALUE)
	{
		//__debugbreak();
		std::cout << "���� ���� ����\n";
		return;
	}

	// �ܼ� ���� ũ�� ����.
	SetConsoleScreenBufferSize(buffer, Vector2(screenSize.x+1, screenSize.y));
	SMALL_RECT rect{ 0, 0, (short)screenSize.x, (short)screenSize.y };

	// �ܼ� â ũ�� ����.
	SetConsoleWindowInfo(buffer, true, &rect);

	// Ŀ�� �Ⱥ��̰� ����.
	CONSOLE_CURSOR_INFO info{ 1, FALSE };
	SetConsoleCursorInfo(buffer, &info);

	// @Test.
	DWORD mode;
	GetConsoleMode(buffer, &mode);
	mode |= ENABLE_QUICK_EDIT_MODE;
	mode |= ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(buffer, mode);
}

ScreenBuffer::ScreenBuffer(HANDLE console, const Vector2& screenSize)
	: screenSize(screenSize), buffer(console)
{
	// Ŀ�� �Ⱥ��̰� ����.
	CONSOLE_CURSOR_INFO cursorInfo{ 1, FALSE };
	SetConsoleCursorInfo(buffer, &cursorInfo);

	// 
	CONSOLE_SCREEN_BUFFER_INFOEX bufferInfo = {};
	GetConsoleScreenBufferInfoEx(buffer, &bufferInfo);
	bufferInfo.dwSize.X = screenSize.x + 1;
	bufferInfo.dwSize.Y = screenSize.y + 1;
	SetConsoleScreenBufferInfoEx(buffer, &bufferInfo);

	// @Test.
	DWORD mode;
	GetConsoleMode(buffer, &mode);
	mode |= ENABLE_QUICK_EDIT_MODE;
	mode |= ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(buffer, mode);
}

ScreenBuffer::~ScreenBuffer()
{
	// ������ �ڵ� ����.
	if (buffer)
	{
		CloseHandle(buffer);
	}
}

void ScreenBuffer::Clear()
{
	// Ŀ�� ��ġ.
	Vector2 position;

	// �ֿܼ� ����� ���� ���� ��ȯ�ޱ� ���� ����.
	DWORD writtenCount = 0;

	// ȭ�� ���� ��ü�� �� ���ڿ� ���.
	// �ܼ� ��ü�� �� ���ڸ� �Է��� �� ��� (memset�� ���).
	FillConsoleOutputCharacter(buffer, ' ', (screenSize.x + 1) * screenSize.y + 1, position, &writtenCount);
}

void ScreenBuffer::Render(CHAR_INFO* charInfo)
{
	// ���� ��ġ �ʱ�ȭ.
	Vector2 bufferPosition;

	// ����� ������ ũ��.
	SMALL_RECT writeRegion{ 0, 0, (short)screenSize.x - 1, (short)screenSize.y - 1 };

	// ���޵� ���� ������ ���ۿ� ���.
	WriteConsoleOutputA(buffer, charInfo, screenSize, bufferPosition, &writeRegion);
}