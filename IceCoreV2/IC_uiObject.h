#pragma once

// Raylib
#include "raylib.h"
#include "raymath.h"

// Standard libraries
#include <vector>
#include <set>

// Other includes
#include "IC_graphicsStructs.h"
#include "vectorHelpers.h"

#include "IC_object.h"
#include "IC_uiEnums.h"

class IC_uiManager;

class IC_uiObject : public IC_object
{
	friend class IC_uiManager;

public:
	IC_uiObject();

	~IC_uiObject();

	IC_uiVisibility Visibility = uiVis::Visible;
	IC_uiState State = uiState::Idle;

	// How the ui object is aligned compared to its anchor.
	IC_uiAlignment Alignment = uiAlign::TopLeft;
	// How the ui is anchored to its parent
	IC_uiAlignment Anchor = uiAnchor::TopLeft;

	

	// Offset from anchor based on alignment
	Vector2 Offset = Vec2(0.0f);
	// Scale
	Vector2 Scale = Vec2(1.0f);
	// Should the scale be treated as a pixel value or a multiplier 
	IC_uiScaling Scaling = IC_uiScaling::Relative;
	// Rotation
	float Rotation = 0.0f;
	// Parent ui object
	IC_uiObject* Parent = nullptr;
	// Child ui objects
	std::set<IC_uiObject*> Children;

	// Enables automatically calling draw on this ui object
	void EnableAutoDraw();
	// Disables automatically calling draw on this ui object
	void DisableAutoDraw();

	// Adds a ui object as a child of this ui object
	// If the ui object already has a parent it will be removed from that parent and then added to this ui object
	void AddChild(IC_uiObject* child);
	// Removes a child from this ui object
	void RemoveChild(IC_uiObject* child);
	// Draws all children
	void DrawChildren(float deltaTime);

	// Automatically calculates the screen position of this ui object relative to its parents.
	Vector2 GetScreenPosition();
	// Automatically calculates the size of this ui object on the screen in pixels.
	Vector2 GetScreenSize();

	// Gets scaling based on the screen size
	Vector2 GetScreenScaling();

	// (0, 0) if top left
	// (1, 1) if bottom right
	// (0.5, 0.5) if center
	// So on
	Vector2 GetAnchorMultiplier();
	// (0, 0) if top left
	// (1, 1) if bottom right
	// (0.5, 0.5) if center
	// So on
	Vector2 GetAlignmentMultiplier();
protected:
	// Always call with the delta time of the current frame
	// If not using auto draw you are expected to call this every frame.
	virtual void Draw(float deltaTime) = 0;
private:
	bool AutoDraw = false;
};