#pragma once

// Raylib
#include "raylib.h"
#include "raymath.h"

// Standard libraries
#include <vector>
#include <string>
#include <set>

// Other includes
#include "IC_graphicsStructs.h"
#include "vectorHelpers.h"

#include "IC_uiObject.h"

class IC_game;

class IC_uiManager
{
	friend class IC_game;

public:
	IC_uiManager();

	void Register(IC_uiObject* uiObject);
	void Unregister(IC_uiObject* uiObject);

protected:
	void Draw(float deltaTime);
private:
	IC_game* game = nullptr;

	// UI objects registered for auto draw.
	std::set<IC_uiObject*> uiObjects;
};