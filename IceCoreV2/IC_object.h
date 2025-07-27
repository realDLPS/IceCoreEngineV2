#pragma once

// Forward declarations
class IC_objectSystem;
class IC_game;

// Most things in IceCore are objects.
// Some exceptions are the engine systems, like input system, graphics manager and object system.
// Spawn using the object system.
class IC_object
{
	friend class IC_objectSystem;

public:
	IC_object() = default;

	virtual ~IC_object() = default;

	// Gets delta time multiplied by time dilation for this object.
	float GetObjectDeltaTime();

	// Call to destroy this object.
	// All pointers and references to this object should be
	// considered invalid after calling destroy.
	// Calls EndPlay on this object.
	void Destroy();

	bool IsBeingDestroyed();

	int GetId();

protected:
	// Called after the object system is done with this object.
	// In theory this should always be called before the first tick, but who knows.
	virtual void BeginPlay() = 0;

	// By default never called, unless ticking is enabled. Then called depending on maxTickFrequency.
	virtual void Tick(float deltaTime) = 0;

	// Called after destroy is called on this object.
	virtual void EndPlay() = 0;

private:
	
	// Returns true if this object was ticked.
	// Called by the object system. The expectation is that this function will be called once per frame for ticking objects.
	bool TryTick();

	// Called by TryTick if TryTick returns true.
	void SubTick(float deltaTime);

	// Set by the object system.
	IC_objectSystem* objectSystem = nullptr;

	// Set to true when BeginPlay is called.
	bool inPlay = false;

	// Set to true when destroy is called.
	bool pendingDestroy = false;

	// If false this object will not be added to the tick list.
	bool canEverTick = false;

	// Should this object persist through levels.
	// Useful for things like music you'd want to keep playing while changing levels.
	bool persistent = false;
public:
	// Can be changed at any time to enable of disable ticking.
	// Even if false this object will be added to the tick list.
	bool ticking = false;

	// Is this object affected by time dilation?
	// Change customTimeDilation if you only want to affect this object. (And set this to false)
	// Also not affected by pausing if set to false.
	bool affectedByTimeDilation = true;

	// How often can this object tick?
	// 0.0f = each frame, 1.0f = every second and so on.
	float maxTickFrequency = 0.0f;

	// Only used if affectedByTimeDilation is false.
	float customTimeDilation = 1.0f;
private:
	// Set by the object system.
	// -1 signifies that this object is not fully initialized yet.
	int id = -1;
	// Affected by time dilation.
	float timeSinceLastTick = 0.0f;
};