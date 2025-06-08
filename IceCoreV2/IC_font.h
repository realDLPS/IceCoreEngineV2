#pragma once

#include <raylib.h>

#include "raylib-nuklear.h"

// Simple wrapper for fonts
struct IC_font
{
	IC_font() = default;

	nk_user_font* nkFont = nullptr;
};

// You have to keep the raylib font alive for the nk_user_font to stay valid.
nk_user_font* NuklearFontFromRaylibFont(Font* font, float fontSize);