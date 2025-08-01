#pragma once

#include "Level/Level.h"

class SinglePlayLevel : public Level
{
	RTTI_DECLARATIONS(SinglePlayLevel, Level)
		
public:

	virtual void Tick(float deltaTime) override;
	virtual void Render() override;
private:
};