#include "IC_objectSystem.h"

#include "IC_game.h"

void IC_objectSystem::Update()
{
	tickedCount = 0;

	for(const auto& object : tickingObjects)
	{
		if (object.second->TryTick())
		{
			tickedCount++; // Statistics
		}
	}
	for(const auto& persistentObject : persistentTickingObjects)
	{
		if (persistentObject.second->TryTick())
		{
			tickedCount++; // Statistics
		}
	}
}

void IC_objectSystem::ChangeLevel()
{
	// Call destroy for all objects
	for(const auto& object : objects)
	{
		object.second->Destroy();
	}
	// Clear the lists
	objects.clear();
	tickingObjects.clear();
	// Reset spawned count
	spawnedCount = 0;
}

void IC_objectSystem::Unload()
{
	for (const auto& object : objects)
	{
		object.second->Destroy();
	}
	for (const auto& persistentObject : persistentObjects)
	{
		persistentObject.second->Destroy();
	}
	objects.clear();
	persistentObjects.clear();
	tickingObjects.clear();
	persistentTickingObjects.clear();
}

void IC_objectSystem::RequestDestroy(IC_object* object)
{
	int id = object->id;
	if (object->persistent)
	{
		if (object->canEverTick)
		{
			// Remove the object from the persistent ticking list
			persistentTickingObjects.erase(id);
		}
		// Remove from the persistent list
		persistentObjects.find(id)->second.reset();
		persistentObjects.erase(id);
	}
	else
	{
		if(object->canEverTick)
		{
			// Remove the object from the ticking list
			tickingObjects.erase(id);
		}
		// Remove from the list
		objects.find(id)->second.reset();
		objects.erase(id);
	}
}