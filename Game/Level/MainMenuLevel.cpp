#include "MainMenuLevel.h"
#include "Game/Game.h"
#include "Math/Vector2.h"


MainMenuLevel::MainMenuLevel()
{
	// �޴� ������ �߰� -> �̱�, ��Ƽ, ���� ����
	// �޴� ������ �߰�
	items.emplace_back(new MenuItem(
		"Single Play",
		[]() { dynamic_cast<Game*>(&Game::Get())->SinglePlayStart(); }
	));
	items.emplace_back(new MenuItem(
		"1 vs 1",
		[]() { dynamic_cast<Game*>(&Game::Get())->MultiPlayStart(); }
	));
	items.emplace_back(new MenuItem(
		"Quit Game",
		[]() { Game::Get().Quit(); }
	));
	// ������ �� �̸� ����
	length = static_cast<int>(items.size());
}

MainMenuLevel::~MainMenuLevel()
{
	for (MenuItem* item : items)
	{
		SafeDelete(item);
	}

	items.clear();
}

void MainMenuLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// �Է� ó��
	if (Input::Get().GetKeyDown(VK_UP))
	{
		if (currentIndex <= 0) return;
		currentIndex--;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		if (currentIndex >= length - 1) return;
		currentIndex++;
	}

	// Enter Ű �Է�
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// �޴� �������� �����ϰ� �ִ� �Լ� ȣ��
		items[currentIndex]->onSelected();
		currentIndex = 0;
	}
}

void MainMenuLevel::Render()
{
	Vector2 showPosition(0, 0);
	Color color = Color :: Blue;
	Game::Get().WriteToBuffer(showPosition, "Puyo Puyo!", color);

	showPosition.y += 2;
	for (int ix = 0; ix < length; ++ix)
	{
		color = ix == currentIndex ? selectedColor : unselectedColor;
		Game::Get().WriteToBuffer(showPosition, items[ix]->menuText, color);
		showPosition.y++;
	}

	showPosition.y += 3;
	color = Color::BlueIntensity;
	Game::Get().WriteToBuffer(showPosition, "Single Play Controls", color);
	showPosition.y += 2;
	color = Color::White;
	Game::Get().WriteToBuffer(showPosition, "Move Left     : Left Arrow Key", color);
	showPosition.y++;
	Game::Get().WriteToBuffer(showPosition, "Move Right    : Right Arrow Key", color);
	showPosition.y++;
	Game::Get().WriteToBuffer(showPosition, "Soft Drop     : Down Arrow Key", color);
	showPosition.y++;
	Game::Get().WriteToBuffer(showPosition, "Rotate        : Q, E", color);

	showPosition.y += 3;
	color = Color::BlueIntensity;
	Game::Get().WriteToBuffer(showPosition, "Multi Play Controls", color);
	showPosition.y += 2;
	color = Color::GreenIntensity;
	Game::Get().WriteToBuffer(showPosition, "Player 1 (Left)", color);
	showPosition.y += 2;
	color = Color::White;
	Game::Get().WriteToBuffer(showPosition, "Move Left     : A", color);
	showPosition.y++;
	Game::Get().WriteToBuffer(showPosition, "Move Right    : D", color);
	showPosition.y++;
	Game::Get().WriteToBuffer(showPosition, "Soft Drop     : S", color);
	showPosition.y++;
	Game::Get().WriteToBuffer(showPosition, "Rotate        : Q, E", color);

	showPosition.y -= 5;
	showPosition.x += 30;
	color = Color::GreenIntensity;
	Game::Get().WriteToBuffer(showPosition, "Player 2 (Right)", color);
	showPosition.y += 2;
	color = Color::White;
	Game::Get().WriteToBuffer(showPosition, "Move Left     : Left Arrow Key", color);
	showPosition.y++;
	Game::Get().WriteToBuffer(showPosition, "Move Right    : Right Arrow Key", color);
	showPosition.y++;
	Game::Get().WriteToBuffer(showPosition, "Soft Drop     : Down Arrow Key", color);
	showPosition.y++;
	Game::Get().WriteToBuffer(showPosition, "Rotate        : K, L", color);
}