#pragma once

// This header holds all UI primitives (like canvas, text, etc)
// /
// Also includes shorthand definitions for the primitives
// IC_uiCanvas = CANVAS

#include <raylib.h>
#include "raylib-nuklear.h"

#include "IC_uiObject.h"

#include "IC_globalVariables.h"

// This just saves me from writing these damn default functions over and over again
#define DEFAULT_UI_FUNCTIONS	void Draw(float deltaTime) override;	\
								void Tick(float deltaTime) override;	\
								void BeginPlay() override;				\
								void EndPlay() override;

#define CANVAS = IC_uiCanvas

class IC_uiCanvas : public IC_uiObject
{
public:
	IC_uiCanvas() = default;
	~IC_uiCanvas() = default;

	DEFAULT_UI_FUNCTIONS

	// X and Y position
	Vector2 position = Vec2(0.0f);
	// Width and Height
	Vector2 size = Vec2(0.0f);
};