#include "Puyo.h"
#include "Utils/Utils.h"

#include <iostream>

Puyo::Puyo(Vector2 position, int code)
	:position(position), code(code)
{
	switch (code)
	{
	case 1:
		color = Color::Red;
		break;
	case 2:
		color = Color::Blue;
		break;
	case 3:
		color = Color::Green;
		break;
	case 4:
		color = Color::Yellow;
		break;
	case 5:
		color = Color::Magneta;
		break;
	default:
		color = Color::White;
		break;
	}
}

void Puyo::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}

void Puyo::Render()
{
	Utils::SetConsolePosition(position);
	std::cout << image1;
	position.y++;
	Utils::SetConsolePosition(position);
	std::cout << image2;
	position.y--;
}
