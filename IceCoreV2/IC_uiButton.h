#pragma once

#include "IC_uiObject.h"

class IC_uiButton : public IC_uiObject
{
public:
	IC_uiButton();
	~IC_uiButton();

	void Draw(float deltaTime) override;
};