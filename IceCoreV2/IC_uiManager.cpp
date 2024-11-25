#include "IC_uiManager.h"

IC_uiManager::IC_uiManager()
{
}

void IC_uiManager::Register(IC_uiObject* uiObject)
{
	uiObjects.insert(uiObject);
}

void IC_uiManager::Unregister(IC_uiObject* uiObject)
{
	uiObjects.erase(uiObject);
}

void IC_uiManager::Draw(float deltaTime)
{
	for(const auto& uiObject : uiObjects)
	{
		uiObject->Draw(deltaTime);
	}
}

void IC_uiManager::Unload()
{
	while (!uiObjects.empty())
	{
		(*uiObjects.begin())->Destroy();
	}
}
