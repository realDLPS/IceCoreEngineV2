#pragma once

#include "raylib.h"
#include "raymath.h"

// Creates a vector2 using 2 floats
Vector2 Vec2(float x, float y);
// Creates a vector2 using 1 float
Vector2 Vec2(float x);
Vector2 rotVec2(Vector2 v, float angle);