#pragma once

#include "raylib.h"

// Creates a vector2 using 2 floats
Vector2 Vec2(float x, float y);
// Creates a vector2 using 1 float
Vector2 Vec2(float x);
Vector2 operator*(const Vector2& lhs, const float& rhs);
Vector2 operator*(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator+(const Vector2& lhs, const Vector2& rhs);