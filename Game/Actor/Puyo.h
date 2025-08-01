#pragma once
#include "Actor/Actor.h"

class Puyo : public Actor
{
	RTTI_DECLARATIONS(Puyo, Actor)
public:
	Puyo(Vector2 position, int code);

	void Tick(float deltaTime) override;
	void Render() override;
private:
	
	// 땅에 이미 떨어졌는지 여부
	bool isLanded = false;

	// 액터의 현재 위치
	Vector2 position;

	// 액터의 이미지
	const char* image1 = "(o_o)";
	const char* image2 = "( ∆ )";
	
	// 액터의 가로 너비
	int width = 5;

	// 액터의 세로 너비
	int height = 2;

	// 액터의 식별코드. 1 : 빨강, 2 : 파랑, 3 : 초록, 4 : 노랑, 5 : 보라
	int code = 0;

	// 액터의 색깔
	Color color;
};