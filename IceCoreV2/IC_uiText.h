#pragma once

#pragma once

#include "IC_uiObject.h"

#include <string>

class IC_uiText : public IC_uiObject
{
public:
	IC_uiText() = default;
	~IC_uiText() = default;

	void Draw(float deltaTime) override;
	void Tick(float deltaTime) override;
	void BeginPlay() override;
	void EndPlay() override;

	std::string Text = "Button";
	int FontSize = 20;
	int Spacing = 0;
};