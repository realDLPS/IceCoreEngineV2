#pragma once


#include "raylib.h"

#include <string>

struct IC_debugString
{
	IC_debugString(std::string str, float duration, Color color) { this->str = str; this->color = color; this->duration = duration; this->creationTime = float(GetTime()); };
	IC_debugString() { this->str = "Hello!"; this->creationTime = float(GetTime()); };
	IC_debugString(std::string str) { this->str = str; this->creationTime = float(GetTime()); };
	IC_debugString(std::string str, Color color) { this->str = str; this->color = color; this->creationTime = float(GetTime()); };
	IC_debugString(std::string str, float duration) { this->str = str; this->duration = duration; this->creationTime = float(GetTime()); };

	std::string str;
	Color color = SKYBLUE;
	float duration = 5.0f;
	// Set automatically
	float creationTime = 0.0f;
};