#include "Puyo.h"
#include "Game/Game.h"
#include "Math/Vector2.h"
#include "Interface/ICanPuyoMove.h"

Puyo::Puyo(Vector2 spawnPosition, int code, bool isMain)
	: code(code), isMain(isMain)
{
	position = spawnPosition;

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

void Puyo::BeginPlay()
{
	super::BeginPlay();
	// 인터페이스 얻어오기.
	if (GetOwner())
	{
		canPuyoMoveInterface
			= dynamic_cast<ICanPuyoMove*>(GetOwner());
	}
	timer.Reset();
	timer.SetTargetTime(0.8f);
}

void Puyo::Tick(float deltaTime)
{
	// 조작하고 있지 않은 뿌요일 경우 레벨의 중력작용 명령에 따라 행동
	if (!isControlling)
	{
		if(!gravityFlag) return;
		if (position == targetPosition)
		{
			gravityFlag = false;
			return;
		}
		timer.Tick(deltaTime);
		if (!timer.IsTimeout()) return;
		timer.Reset();
		SetPosition(Vector2(position.x, position.y + 1));
		return;
	}

	// 현재 떨어지고 있는 뿌요일 경우 서브 뿌요는 조작하지 않음
	if (!isMain)
	{
		return;
	}

	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		if (canPuyoMoveInterface->CanPuyoMove(*this, Vector2(position.x - 5, position.y)))
		{
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(sibling->position.x - 5, sibling->position.y)))
			{
				SetPosition(Vector2(position.x - 5, position.y));
				sibling->SetPosition(Vector2(sibling->position.x - 5, sibling->position.y));
			}
		}
	}
	else if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		if (canPuyoMoveInterface->CanPuyoMove(*this, Vector2(position.x + 5, position.y)))
		{
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(sibling->position.x + 5, sibling->position.y)))
			{
				SetPosition(Vector2(position.x + 5, position.y));
				sibling->SetPosition(Vector2(sibling->position.x + 5, sibling->position.y));
			}
		}
	}
	else if (Input::Get().GetKeyDown('E'))
	{
		switch (subPuyoDirection)
		{
		case 0: // 서브 뿌요를 메인 뿌요의 오른쪽으로 이동
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x + 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x + 5, position.y));
				subPuyoDirection = 3;
			}
			break;
		case 1: // 서브 뿌요를 메인 뿌요의 아래로 이동
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x, position.y + 2)))
			{
				sibling->SetPosition(Vector2(position.x, position.y + 2));
				subPuyoDirection = 0;
			}
			break;
		case 2: // 서브 뿌요를 메인 뿌요의 왼쪽으로 이동
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x - 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x - 5, position.y));
				subPuyoDirection = 1;
			}
			break;
		case 3: // 서브 뿌요를 메인 뿌요의 위로 이동
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x, position.y - 2)))
			{
				sibling->SetPosition(Vector2(position.x, position.y - 2));
				subPuyoDirection = 2;
			}
			break;
		}
	}
	else if (Input::Get().GetKeyDown('Q'))
	{
		switch (subPuyoDirection)
		{
		case 0: // 서브 뿌요를 메인 뿌요의 왼쪽으로 이동
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x - 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x - 5, position.y));
				subPuyoDirection = 1;
			}
			break;
		case 1: // 서브 뿌요를 메인 뿌요의 위로 이동
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x, position.y - 2)))
			{
				sibling->SetPosition(Vector2(position.x, position.y - 2));
				subPuyoDirection = 2;
			}
			break;
		case 2: // 서브 뿌요를 메인 뿌요의 오른쪽으로 이동
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x + 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x + 5, position.y));
				subPuyoDirection = 3;
			}
			break;
		case 3: // 서브 뿌요를 메인 뿌요의 아래로 이동
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x, position.y + 2)))
			{
				sibling->SetPosition(Vector2(position.x, position.y + 2));
				subPuyoDirection = 0;
			}
			break;
		}
	}


	timer.Tick(deltaTime);

	// 아직 착륙하지 않았기에 하강
	if (!timer.IsTimeout())
	{
		return;
	}

	timer.Reset();
	if (canPuyoMoveInterface->CanPuyoMove(*this, Vector2(position.x, position.y + 1))
		&& sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(sibling->position.x, sibling->position.y + 1)))
	{
		SetPosition(Vector2(position.x, position.y + 1));
		sibling->SetPosition(Vector2(sibling->position.x, sibling->position.y + 1));
	}
	else
	{
		if (isLanded)
		{
			isControlling = false;
			sibling->isControlling = false;
			canPuyoMoveInterface->PuyoLanded(this, sibling);
		}
		isLanded = true;
	}
}

void Puyo::Render()
{
	Vector2 curPosition = position;
	Game::Get().WriteToBuffer(curPosition, image1, color);
	curPosition.y++;
	Game::Get().WriteToBuffer(curPosition, image2, color);
}

void Puyo::ApplyGravity(Vector2 newPosition)
{
	gravityFlag = true;
	targetPosition = newPosition;
	timer.SetTargetTime(0.2f);
}

void Puyo::SetSibling(Puyo* sibling)
{
	this->sibling = sibling;
}

Puyo* Puyo::GetSibling() const
{
	return sibling;
}
