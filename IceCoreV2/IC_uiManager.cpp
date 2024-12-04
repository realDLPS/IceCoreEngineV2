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
		if (uiObject->Parent == nullptr)
		{
			uiObject->Draw(deltaTime);

			std::vector<IC_uiObject*> children = std::vector(uiObject->Children.begin(), uiObject->Children.end());
			while (!children.empty())
			{
				children[0]->Draw(deltaTime);
				children.insert(children.begin(), children[0]->Children.begin(), children[0]->Children.end());
				children.erase(children.begin());
			}
		}
	}
}

void IC_uiManager::Unload()
{
	while (!uiObjects.empty())
	{
		(*uiObjects.begin())->Destroy();
	}
}
