#include "IC_uiText.h"

#include "IC_game.h"

void IC_uiText::Draw(float deltaTime)
{
	IC_uiStyle style = GetGame()->GetUiStyle();

	int realFontSize = FontSize;

	Vector2 Test = GetAnchorMultiplier();

	switch(Scaling)
	{
	case IC_uiScaling::LiteralScaledMax:
		realFontSize *= std::max(GetScreenScaling().x, GetScreenScaling().y);
		break;
	default:
		realFontSize *= std::min(GetScreenScaling().x, GetScreenScaling().y);
		break;
	}

	DrawTextPro(style.font, Text.c_str(), GetScreenPosition(), MeasureTextEx(style.font, Text.c_str(), realFontSize, Spacing) * GetAnchorMultiplier(), Rotation, realFontSize, Spacing, WHITE);
}

void IC_uiText::Tick(float deltaTime)
{
}

void IC_uiText::BeginPlay()
{
}

void IC_uiText::EndPlay()
{
}
