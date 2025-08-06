#include "MultiPlayPuyo.h"
#include "Input.h"
#include "Interface/IInteractPuyo.h"
#include "Game/Game.h"

#include <Windows.h>

MultiPlayPuyo::MultiPlayPuyo(Vector2 spawnPosition, int code, bool isMain, int player)
	: code(code), isMain(isMain), player(player)
{
	position = spawnPosition;
	color = CodeToColor(code);

	// 더미 뿌요일 경우
	if (code == 0)
	{
		isControlling = false;
		isLanding = false;
		landingSpeed = 0.05f;
		landingSpeedFast = 0.05f;
	}

	switch (player)
	{
	case 0:
		leftButton = 'A';
		rightButton = 'D';
		downButton = 'S';
		clockWise = 'Q';
		counterClockWise = 'E';
		break;
	case 1:
		leftButton = VK_LEFT;
		rightButton = VK_RIGHT;
		downButton = VK_DOWN;
		clockWise = 'K';
		counterClockWise = 'L';
		break;
	}
}

void MultiPlayPuyo::BeginPlay()
{
	super::BeginPlay();
	// 인터페이스 얻어오기.
	if (GetOwner())
	{
		ownerInterface
			= dynamic_cast<IInteractPuyo*>(GetOwner());
		screenMinY = ownerInterface->GetScreenMinY(player);
	}
	// 타이머 설정, 하강 속도 설정
	timer.Reset();
	timer.SetTargetTime(landingSpeed);

}

void MultiPlayPuyo::Tick(float deltaTime)
{
	// 삭제될 액터일 때 삭제 이펙트
	if (isDestroying)
	{
		if (effectCount >= 20) Destroy();
		effectCode++;
		color = CodeToColor(effectCode);
		if (effectCode > 5) effectCode = 0;
		effectCount++;
		return;
	}
	
	
	// 조작 중이지 않은 뿌요일 경우 레벨의 중력 명령에 따라 행동
	if (isControlling == false)
	{
		if (!isLanding) return;
		if (position == landingTarget)
		{
			isLanding = false;
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

	if (Input::Get().GetKeyDown(leftButton))
	{
		if (ownerInterface->CanPuyoMove(this, Vector2(position.x - 5, position.y)))
		{
			if (sibling->ownerInterface->CanPuyoMove(sibling, Vector2(sibling->position.x - 5, sibling->position.y)))
			{
				SetPosition(Vector2(position.x - 5, position.y));
				sibling->SetPosition(Vector2(sibling->position.x - 5, sibling->position.y));
			}
		}
	}
	else if (Input::Get().GetKeyDown(rightButton))
	{
		if (ownerInterface->CanPuyoMove(this, Vector2(position.x + 5, position.y)))
		{
			if (sibling->ownerInterface->CanPuyoMove(sibling, Vector2(sibling->position.x + 5, sibling->position.y)))
			{
				SetPosition(Vector2(position.x + 5, position.y));
				sibling->SetPosition(Vector2(sibling->position.x + 5, sibling->position.y));
			}
		}
	}
	else if (Input::Get().GetKeyDown(counterClockWise))
	{
		switch (subPuyoDirection)
		{
		case 0: // 서브 뿌요를 메인 뿌요의 오른쪽으로 이동
			if (sibling->ownerInterface->CanPuyoMove(sibling, Vector2(position.x + 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x + 5, position.y));
				subPuyoDirection = 3;
			}
			break;
		case 1: // 서브 뿌요를 메인 뿌요의 아래로 이동
			if (sibling->ownerInterface->CanPuyoMove(sibling, Vector2(position.x, position.y + 2)))
			{
				sibling->SetPosition(Vector2(position.x, position.y + 2));
				subPuyoDirection = 0;
			}
			break;
		case 2: // 서브 뿌요를 메인 뿌요의 왼쪽으로 이동
			if (sibling->ownerInterface->CanPuyoMove(sibling, Vector2(position.x - 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x - 5, position.y));
				subPuyoDirection = 1;
			}
			break;
		case 3: // 서브 뿌요를 메인 뿌요의 위로 이동
			if (sibling->ownerInterface->CanPuyoMove(sibling, Vector2(position.x, position.y - 2)))
			{
				sibling->SetPosition(Vector2(position.x, position.y - 2));
				subPuyoDirection = 2;
			}
			break;
		}
	}
	else if (Input::Get().GetKeyDown(clockWise))
	{
		switch (subPuyoDirection)
		{
		case 0: // 서브 뿌요를 메인 뿌요의 왼쪽으로 이동
			if (sibling->ownerInterface->CanPuyoMove(sibling, Vector2(position.x - 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x - 5, position.y));
				subPuyoDirection = 1;
			}
			break;
		case 1: // 서브 뿌요를 메인 뿌요의 위로 이동
			if (sibling->ownerInterface->CanPuyoMove(sibling, Vector2(position.x, position.y - 2)))
			{
				sibling->SetPosition(Vector2(position.x, position.y - 2));
				subPuyoDirection = 2;
			}
			break;
		case 2: // 서브 뿌요를 메인 뿌요의 오른쪽으로 이동
			if (sibling->ownerInterface->CanPuyoMove(sibling, Vector2(position.x + 5, position.y)))
			{
				sibling->SetPosition(Vector2(position.x + 5, position.y));
				subPuyoDirection = 3;
			}
			break;
		case 3: // 서브 뿌요를 메인 뿌요의 아래로 이동
			if (sibling->ownerInterface->CanPuyoMove(sibling, Vector2(position.x, position.y + 2)))
			{
				sibling->SetPosition(Vector2(position.x, position.y + 2));
				subPuyoDirection = 0;
			}
			break;
		}
	}
	// 아래 방향키를 누르면 하강 속도 가속
	if (Input::Get().GetKeyDown(downButton))
	{
		timer.SetTargetTime(landingSpeedFast);
	}
	// 아래 방향키를 떼면 하강 속도 복원
	if (Input::Get().GetKeyUp(downButton))
	{
		timer.SetTargetTime(landingSpeed);
	}
	timer.Tick(deltaTime);

	// 타이머에 맞춰서 하강
	if (!timer.IsTimeout())
	{
		return;
	}

	timer.Reset();
	if (ownerInterface->CanPuyoMove(this, Vector2(position.x, position.y + 1))
		&& sibling->ownerInterface->CanPuyoMove(sibling, Vector2(sibling->position.x, sibling->position.y + 1)))
	{
		SetPosition(Vector2(position.x, position.y + 1));
		sibling->SetPosition(Vector2(sibling->position.x, sibling->position.y + 1));
		canMoveDown = true;
	}
	else
	{
		if (canMoveDown == false)
		{
			isControlling = false;
			sibling->isControlling = false;
			ownerInterface->PuyoLanded(this, sibling);
			return;
		}
		canMoveDown = false;
	}
}

void MultiPlayPuyo::Render()
{
	Vector2 curPosition = position;
	if(curPosition.y >= screenMinY) Game::Get().WriteToBuffer(curPosition, image1, color);
	curPosition.y++;
	if (curPosition.y >= screenMinY) Game::Get().WriteToBuffer(curPosition, image2, color);
}

void MultiPlayPuyo::ApplyGravity(int newY)
{
	isLanding = true;
	landingTarget = Vector2(position.x, newY);
	timer.SetTargetTime(landingSpeedFast);
}

void MultiPlayPuyo::WillDestroyed()
{
	isDestroying = true;
}

Color MultiPlayPuyo::CodeToColor(int code)
{
	switch (code)
	{
	case 1:
		return Color::Red;
		break;
	case 2:
		return Color::Blue;
		break;
	case 3:
		return Color::Green;
		break;
	case 4:
		return Color::Yellow;
		break;
	case 5:
		return Color::Magneta;
		break;
	}
	return Color::White;
}

void MultiPlayPuyo::SetSibling(MultiPlayPuyo* sibling)
{
	this->sibling = sibling;
}

MultiPlayPuyo* MultiPlayPuyo::GetSibling() const
{
	return sibling;
}

int MultiPlayPuyo::GetPlayer()
{
	return player;
}

bool MultiPlayPuyo::GetIsLanding()
{
	return isLanding;
}

int MultiPlayPuyo::GetCode()
{
	return code;
}