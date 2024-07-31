#pragma once

// Raylib
#include "raylib.h"
#include "raymath.h"

// Standard libraries
#include <vector>

// Other includes
#include "IC_debugStructs.h"

class IC_visualDebugger
{
private:
	// Current debug strings
	std::vector<IC_debugString> debugStrings;
public:
	IC_visualDebugger();

	void AddDebugString(const IC_debugString& DebugString, bool Log);
	void DrawDebugStrings();
};