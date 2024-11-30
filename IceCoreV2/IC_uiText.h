#pragma once

#pragma once

#include "IC_uiObject.h"

#include <string>

class IC_uiButton : public IC_uiObject
{
public:
	IC_uiButton() = default;
	~IC_uiButton() = default;

	void Draw(float deltaTime) override;
	void Tick(float deltaTime) override;
	void BeginPlay() override;
	void EndPlay() override;

	std::string text = "Button";
};