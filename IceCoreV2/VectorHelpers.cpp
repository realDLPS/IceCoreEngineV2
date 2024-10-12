#include "vectorHelpers.h"

Vector2 Vec2(float x, float y)
{
	Vector2 v;
	v.x = x;
	v.y = y;
	return v;
}
Vector2 Vec2(float x)
{
	Vector2 v;
	v.x = x;
	v.y = x;
	return v;
}
Vector2 operator*(const Vector2& lhs, const float& rhs)
{
	return Vec2(lhs.x * rhs, lhs.y * rhs);
}
Vector2 operator*(const Vector2& lhs, const Vector2& rhs)
{
	return Vec2(lhs.x * rhs.x, lhs.y * rhs.y);
}
Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2 rotVec2(Vector2 v, float angle)
{
	// Constant is defined as 1/(180/pi)
	return Vector2Rotate(v, angle*0.01745329251994329577f);
}
