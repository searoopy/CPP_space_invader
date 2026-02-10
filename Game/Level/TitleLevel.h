#pragma once

#include "Level/Level.h"

using namespace wanted;

class TitleLevel : public Level
{



	// RTTI µî·Ï.
	RTTI_DECLARATIONS(TitleLevel, Level)

public:
	TitleLevel();
	~TitleLevel();

	virtual void Tick(float dtime) override;


private:

};

