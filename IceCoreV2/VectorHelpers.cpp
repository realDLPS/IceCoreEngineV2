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
Vector2 Vec2(double x, double y)
{
	Vector2 v;
	v.x = (float)x;
	v.y = (float)y;
	return v;
}
Vector2 Vec2(double x)
{
	Vector2 v;
	v.x = (float)x;
	v.y = (float)x;
	return v;
}
Vector2 Vec2(int x, int y)
{
	Vector2 v;
	v.x = (float)x;
	v.y = (float)y;
	return v;
}
Vector2 Vec2(int x)
{
	Vector2 v;
	v.x = (float)x;
	v.y = (float)x;
	return v;
}

Vector2 rotVec2(Vector2 v, float angle)
{
	// Constant is defined as 1/(180/pi)
	return Vector2Rotate(v, angle*0.01745329251994329577f);
}
