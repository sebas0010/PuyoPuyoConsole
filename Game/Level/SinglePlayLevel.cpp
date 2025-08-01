#include "SinglePlayLevel.h"
#include "input.h"
#include "Game/Game.h"
#include "Utils/Utils.h"

#include <iostream>

void SinglePlayLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
		return;
	}
}

void SinglePlayLevel::Render()
{
    DrawMap();
    super::Render();
	
}

void SinglePlayLevel::DrawMap()
{
    // 맵 그리기 시작 위치로 커서 이동
    Vector2 position = Vector2(screenMinX - 1, screenMinY - 1);
    Utils::SetConsolePosition(position);

    // X좌표를 고정하기 위한 공백
    std::string prefix(screenMinX - 1, ' ');

    // 맵 버퍼 크기 계산
    size_t lineLength = prefix.size() + 32 + 1; // prefix + 테두리 + 줄바꿈
    size_t totalLines = 26;                     // 상단 1줄 + 중간 24줄 + 하단 1줄
    size_t totalLength = lineLength * totalLines;

    // 버퍼 생성 (충분한 크기 예약)
    std::string buffer;
    buffer.reserve(totalLength);

    // 상단 테두리
    buffer.append(32, '#');
    buffer += '\n';

    // 중간 줄
    for (int y = 0; y < 24; ++y)
    {
        buffer += prefix;
        buffer += '#';
        buffer.append(30, ' ');
        buffer += '#';
        buffer += '\n';
    }

    // 하단 테두리 (마지막 줄은 줄바꿈 없이)
    buffer += prefix;
    buffer.append(32, '#');

    // 한 번에 출력
    std::cout << buffer;
}
