#include "IC_uiButton.h"

#include "IC_game.h"

void IC_uiButton::Draw(float deltaTime)
{
	IC_uiStyle style = GetGame()->GetUiStyle();
	
	IC_drawable drawable = IC_drawable(style.button, GetScreenPosition(), Vec2(GetScreenSize().x / style.button.frameWidth , GetScreenSize().y / style.button.frameHeight), Rotation);
	drawable.worldSpace = false;

	GetGame()->GfxMgr()->DrawDrawable(drawable);
}

void IC_uiButton::Tick(float deltaTime)
{
}

void IC_uiButton::BeginPlay()
{
}

void IC_uiButton::EndPlay()
{
}
