#include "IC_object.h"

#include "IC_game.h"

float IC_object::GetObjectDeltaTime()
{
	if (affectedByTimeDilation)
	{
		return game->GetDeltaTime();
	}
	else
	{
		return GetFrameTime() * customTimeDilation;
	}
}

void IC_object::Destroy()
{
	// Tell the object that it is being destroyed.
	pendingDestroy = true;
	EndPlay();

	objectSystem->RequestDestroy(this);
}

bool IC_object::IsBeingDestroyed()
{
	return pendingDestroy;
}

bool IC_object::TryTick()
{
	timeSinceLastTick += GetObjectDeltaTime();

	// It's not necessary to check if this object can ever tick, as this function will not be
	// called if canEverTick is false.
	if (/*!canEverTick ||*/ !ticking)
	{
		return false;
	}

	if (timeSinceLastTick < maxTickFrequency)
	{
		return false;
	}

	SubTick(timeSinceLastTick);
	timeSinceLastTick = 0.0f;
	return true;
}

void IC_object::SubTick(float deltaTime)
{
	Tick(deltaTime);

	// This function may do more in the future.
}
