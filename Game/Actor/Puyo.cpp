#include "Puyo.h"
#include "Game/Game.h"
#include "Math/Vector2.h"
#include "Interface/ICanPuyoMove.h"

Puyo::Puyo(Vector2 spawnPosition, int code, bool isMain)
	: code(code), isMain(isMain)
{
	position = spawnPosition;
	effectCode = code;
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
	// �������̽� ������.
	if (GetOwner())
	{
		canPuyoMoveInterface
			= dynamic_cast<ICanPuyoMove*>(GetOwner());

		landingSpeed = canPuyoMoveInterface->GetLandingSpeed();
	}
	timer.Reset();
	timer.SetTargetTime(landingSpeed);
}

void Puyo::Tick(float deltaTime)
{
	// ������ ������ �� ���� ����Ʈ
	if (isDestroying)
	{
		if (effectCount >= 20) Destroy();
		effectCode++;
		switch (effectCode)
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
			effectCode = 0;
			break;
		}
		effectCount++;
		return;
	}
	
	// �����ϰ� ���� ���� �ѿ��� ��� ������ �߷��ۿ� ��ɿ� ���� �ൿ
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

	// ���� �������� �ִ� �ѿ��� ��� ���� �ѿ�� �������� ����
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
		case 0: // ���� �ѿ並 ���� �ѿ��� ���������� �̵�
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x + 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x + 5, position.y));
				subPuyoDirection = 3;
			}
			break;
		case 1: // ���� �ѿ並 ���� �ѿ��� �Ʒ��� �̵�
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x, position.y + 2)))
			{
				sibling->SetPosition(Vector2(position.x, position.y + 2));
				subPuyoDirection = 0;
			}
			break;
		case 2: // ���� �ѿ並 ���� �ѿ��� �������� �̵�
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x - 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x - 5, position.y));
				subPuyoDirection = 1;
			}
			break;
		case 3: // ���� �ѿ並 ���� �ѿ��� ���� �̵�
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
		case 0: // ���� �ѿ並 ���� �ѿ��� �������� �̵�
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x - 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x - 5, position.y));
				subPuyoDirection = 1;
			}
			break;
		case 1: // ���� �ѿ並 ���� �ѿ��� ���� �̵�
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x, position.y - 2)))
			{
				sibling->SetPosition(Vector2(position.x, position.y - 2));
				subPuyoDirection = 2;
			}
			break;
		case 2: // ���� �ѿ並 ���� �ѿ��� ���������� �̵�
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x + 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x + 5, position.y));
				subPuyoDirection = 3;
			}
			break;
		case 3: // ���� �ѿ並 ���� �ѿ��� �Ʒ��� �̵�
			if (sibling->canPuyoMoveInterface->CanPuyoMove(*sibling, Vector2(position.x, position.y + 2)))
			{
				sibling->SetPosition(Vector2(position.x, position.y + 2));
				subPuyoDirection = 0;
			}
			break;
		}
	}

	// �Ʒ� ����Ű�� ������ �ϰ� �ӵ� ����
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		timer.SetTargetTime(landingSpeedFast);
	}
	// �Ʒ� ����Ű�� ���� �ϰ� �ӵ� ����
	if (Input::Get().GetKeyUp(VK_DOWN))
	{
		timer.SetTargetTime(landingSpeed);
	}


	timer.Tick(deltaTime);

	// Ÿ�̸ӿ� ���缭 �ϰ�
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
		isLanded = false;
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
	if (curPosition.y >= 0)
	{
		if (isDestroying) Game::Get().WriteToBuffer(curPosition, removingImage1, color);
		else Game::Get().WriteToBuffer(curPosition, image1, color);
	}
	curPosition.y++;
	if (curPosition.y >= 0)
	{
		if (isDestroying) Game::Get().WriteToBuffer(curPosition, removingImage2, color);
		else Game::Get().WriteToBuffer(curPosition, image2, color);
	}
}

void Puyo::ApplyGravity(int newY)
{
	gravityFlag = true;
	targetPosition = Vector2(position.x, newY);
	timer.SetTargetTime(landingSpeedFast);
}

int Puyo::GetCode()
{
	return code;
}

void Puyo::SetSibling(Puyo* sibling)
{
	this->sibling = sibling;
}

Puyo* Puyo::GetSibling() const
{
	return sibling;
}

bool Puyo::GetGravityFlag()
{
	return gravityFlag;
}

void Puyo::WillDestroyed()
{
	isDestroying = true;
}
