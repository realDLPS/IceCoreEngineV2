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

void IC_uiObject::AddChild(IC_uiObject* child)
{
	if (child->Parent)
	{
		if(child->Parent == this)
		{
			return;
		}
		child->Parent->RemoveChild(child);
	}
	child->Parent = this;
	Children.insert(child);
}

void IC_uiObject::RemoveChild(IC_uiObject* child)
{
	Children.erase(child);
}

void IC_uiObject::DrawChildren(float deltaTime)
{
	for (auto iter = Children.begin(); iter != Children.end(); ++iter)
	{
		(*iter)->Draw(deltaTime);
	}
}

Vector2 IC_uiObject::GetScreenPosition()
{
	Vector2 AlignmentMultiplier = GetAlignmentMultiplier();

	// Multiplied by -1 to move the alignment in the expected way.
	// For example if you choose the alignment to be center you would expect the ui object to move
	Vector2 AlignmentOffset = GetScreenSize() * AlignmentMultiplier * -1;

	if (!Parent)
	{
		// Calculating the anchor offset based on the screen size and the chozen anchor
		Vector2 AnchorOffset = Vec2(float(GetScreenWidth()), float(GetScreenHeight())) * GetAnchorMultiplier();

		return Offset + AnchorOffset + AlignmentOffset;
	}

	// Calculating the anchor offset based on the screen size and the chozen anchor
	Vector2 AnchorOffset = Parent->GetScreenSize() * GetAnchorMultiplier();

	return Offset + AnchorOffset + AlignmentOffset + Parent->GetScreenPosition();
}

Vector2 IC_uiObject::GetScreenSize()
{
	Vector2 ScreenScaling = GetScreenScaling();
	if(!Parent)
	{
		switch (Scaling)
		{
		case IC_uiScaling::Literal:
			return Scale;
		case IC_uiScaling::Relative:
			return Vec2(float(GetScreenWidth()), float(GetScreenHeight())) * Scale;
		case IC_uiScaling::LiteralScaledMin:
			return Scale * std::min(ScreenScaling.x, ScreenScaling.y);
		case IC_uiScaling::LiteralScaledMax:
			return Scale * std::max(ScreenScaling.x, ScreenScaling.y);
		case IC_uiScaling::LiteralScaled:
			return Scale * ScreenScaling;
		default:
			return Scale;
		}
	}
	switch (Scaling)
	{
	case IC_uiScaling::Literal:
		return Scale;
	case IC_uiScaling::Relative:
		return Parent->GetScreenSize() * Scale;
	case IC_uiScaling::LiteralScaledMin:
		return Scale * std::min(ScreenScaling.x, ScreenScaling.y);
	case IC_uiScaling::LiteralScaledMax:
		return Scale * std::max(ScreenScaling.x, ScreenScaling.y);
	case IC_uiScaling::LiteralScaled:
		return Scale * ScreenScaling;
	default:
		return Scale;
	}
}

Vector2 IC_uiObject::GetScreenScaling()
{
	return Vec2(float(GetScreenWidth()) / 1920, float(GetScreenHeight()) / 1080);;
}

Vector2 IC_uiObject::GetAnchorMultiplier()
{
	switch (Anchor)
	{
	case IC_uiAlignment::TopLeft:
		return Vec2(0, 0);
	case IC_uiAlignment::TopCenter:
		return Vec2(0.5, 0);
	case IC_uiAlignment::TopRight:
		return Vec2(1, 0);
	case IC_uiAlignment::CenterLeft:
		return Vec2(0, 0.5);
	case IC_uiAlignment::Center:
		return Vec2(0.5, 0.5);
	case IC_uiAlignment::CenterRight:
		return Vec2(1, 0.5);
	case IC_uiAlignment::BottomLeft:
		return Vec2(0, 1);
	case IC_uiAlignment::BottomCenter:
		return Vec2(0.5, 1);
	case IC_uiAlignment::BottomRight:
		return Vec2(1, 1);
	default:
		return Vec2(0, 0);
	}
}

Vector2 IC_uiObject::GetAlignmentMultiplier()
{
	switch (Alignment)
	{
	case IC_uiAlignment::TopLeft:
		return Vec2(0, 0);
	case IC_uiAlignment::TopCenter:
		return Vec2(0.5, 0);
	case IC_uiAlignment::TopRight:
		return Vec2(1, 0);
	case IC_uiAlignment::CenterLeft:
		return Vec2(0, 0.5);
	case IC_uiAlignment::Center:
		return Vec2(0.5, 0.5);
	case IC_uiAlignment::CenterRight:
		return Vec2(1, 0.5);
	case IC_uiAlignment::BottomLeft:
		return Vec2(0, 1);
	case IC_uiAlignment::BottomCenter:
		return Vec2(0.5, 1);
	case IC_uiAlignment::BottomRight:
		return Vec2(1, 1);
	default:
		return Vec2(0, 0);
	}
}
