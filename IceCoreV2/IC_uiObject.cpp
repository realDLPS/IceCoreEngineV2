#include "IC_uiObject.h"
#include "IC_uiManager.h"

#include "IC_game.h"

IC_uiObject::IC_uiObject()
{
}

IC_uiObject::~IC_uiObject()
{
	if (AutoDraw)
	{
		DisableAutoDraw();
	}
}

void IC_uiObject::EnableAutoDraw()
{
	if(AutoDraw)
	{
		return;
	}
	GetGame()->UiMgr()->Register(this);
	AutoDraw = true;
}

void IC_uiObject::DisableAutoDraw()
{
	if (!AutoDraw)
	{
		return;
	}
	GetGame()->UiMgr()->Unregister(this);
	AutoDraw = false;
}