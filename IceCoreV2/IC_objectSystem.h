#pragma once

#include "raylib.h"

// Standard library
#include <memory>
#include <unordered_map>

// IceCore
#include "IC_object.h"

// Forward declarations
class IC_game;

// Manages all objects, is in charge of creating, destroying, ticking, etc.
// Ticking order for objects isn't guaranteed, do not rely on it being.
class IC_objectSystem
{
	friend class IC_game;
	friend class IC_object;

public:
	IC_objectSystem() {};

	// Expects class to be derived from IC_object.
	// Pass false to autoFinish if you want to change object variables before BeginPlay is called. Remember to call FinishSpawn if you set autoFinish to false.
	template <class SpawnedClass>
	SpawnedClass* SpawnObject(bool canEverTick = true, bool ticking = false, float maxTickFrequency = 0.0f, bool persistent = false, bool autoFinish = true);

	// Call to finish spawning an object.
	// Only needs to be called if autoFinish was set to false on the SpawnObject call.
	void FinishSpawn(int id, bool persistent);

private:
	// All objects that are level specific and the subset of these objects that are ticking.
	std::unordered_map<int, std::unique_ptr<IC_object>> objects = std::unordered_map<int, std::unique_ptr<IC_object>>();
	std::unordered_map<int, IC_object*> tickingObjects = std::unordered_map<int, IC_object*>();

	// All objects that persist through switching levels and the subset of these persistent objects that are ticking.
	std::unordered_map<int, std::unique_ptr<IC_object>> persistentObjects = std::unordered_map<int, std::unique_ptr<IC_object>>();
	std::unordered_map<int, IC_object*> persistentTickingObjects = std::unordered_map<int, IC_object*>();

	// Set by the game.
	IC_game* game = nullptr;

	// Called by the game each frame.
	void Update();

	// Called by the game when the level changes.
	void ChangeLevel();

	// Called by the game when the game is being closed.
	void Unload();

	// Called by IC_object to destroy itself.
	void RequestDestroy(IC_object* object);

	// Statistics

	// How many objects were ticked last update?
	int tickedCount = 0;

	// Also functions as the id of the next spawned object.
	int spawnedCount = 0;

	// Also functions as the id of the next spawned persistent object.
	int spawnedPersistentCount = 0;
};

template<class SpawnedClass>
inline SpawnedClass* IC_objectSystem::SpawnObject(bool canEverTick, bool ticking, float maxTickFrequency, bool persistent, bool autoFinish)
{
	static_assert(std::is_base_of<IC_object, SpawnedClass>::value, "SpawnedClass must be derived from IC_object.");

	//SpawnedClass* spawnedObject = new SpawnedClass();

	std::unique_ptr<IC_object> spawnedObject = std::make_unique<SpawnedClass>();
	auto spawnedObjectPtr = spawnedObject.get();

	//IC_object* castObject = static_cast<IC_object*>(spawnedObject);

	if (persistent)
	{
		spawnedObject.get()->id = spawnedPersistentCount;
		spawnedPersistentCount++;

		// Insert all persistent objects into the persistent object set.
		persistentObjects.insert({ spawnedObjectPtr->id, move(spawnedObject) });
		if (canEverTick)
		{
			// Also add it to the persistent ticking object set if it can ever tick.
			persistentTickingObjects.insert({ spawnedObjectPtr->id, spawnedObjectPtr });
		}
	}
	else
	{
		spawnedObject.get()->id = spawnedCount;
		spawnedCount++;
		// Insert all non-persistent objects into the non-persistent object set.
		objects.insert({ spawnedObjectPtr->id, move(spawnedObject) });
		if (canEverTick)
		{
			// Also add it to the non-persistent ticking object set if it can ever tick.
			tickingObjects.insert({ spawnedObjectPtr->id, spawnedObjectPtr });
		}
	}

	// Set variables for the spawned object.
	spawnedObjectPtr->canEverTick = canEverTick;
	spawnedObjectPtr->ticking = ticking;
	spawnedObjectPtr->maxTickFrequency = maxTickFrequency;
	spawnedObjectPtr->persistent = persistent;
	spawnedObjectPtr->game = game;
	spawnedObjectPtr->objectSystem = this;

	if (autoFinish)
	{
		spawnedObjectPtr->inPlay = true;
		spawnedObjectPtr->BeginPlay();
	}

	return static_cast<SpawnedClass*>(spawnedObjectPtr);
}
