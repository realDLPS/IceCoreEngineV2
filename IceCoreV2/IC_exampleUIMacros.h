// Some basic UI macros that make creating UI a lot simpler

#pragma once
#include "raylib.h"
#include "raylib-nuklear.h"

#include "IC_delegates.h"
#include "IC_textStructs.h"

#include "nuklearHelpers.h"

#include "IC_uiConfig.h"

#include "IC_globalVariables.h"

// Internal macro that checks if a delegate is NULL before calling
#define CALLDELEGATE(delegate, input) if(delegate != NULL) {delegate(input);}

#pragma region Markers

// Should the widget rendered before be considered for hovering?
#define HOVERABLE if(nkCtx->last_widget_state == 82 || nkCtx->last_widget_state == 98) {++hoveredElementCount;}

#pragma endregion


#pragma region Elements

#pragma region Button
/// Simple button
///
/// Params
/// textid: id of the text to use in button label, leave blank for no text
/// delegate: delegate to call for all things that could happen to this button, use NULL if you don't want a callback
/// id: id of this button
#define UIBUTTON(textid, delegate, id)						\
static bool id##_pressed = false;							\
static float id##_pressTime = -1.0f;						\
static bool id##_hovered = false;							\
TEXTcCache(textid, id##_text)								\
if(nk_button_label(nkCtx, textid == "" ? "" : id##_text))	\
{															\
	if(!id##_pressed)										\
	{														\
		CALLDELEGATE(delegate, 1)							\
		id##_pressTime = GetTime();							\
	}														\
	id##_pressed = true;									\
}															\
else														\
{															\
	if(id##_pressed)										\
	{														\
		CALLDELEGATE(delegate, 2)							\
		id##_pressed = false;								\
		if(GetTime() - id##_pressTime <= CLICKTHRESHOLD)	\
		{													\
			CALLDELEGATE(delegate, 3)						\
		}													\
	}														\
}															\
if(nk_widget_is_hovered(nkCtx))								\
{															\
	if(!id##_hovered)										\
	{														\
		CALLDELEGATE(delegate, 5)							\
	}														\
	id##_hovered = true;									\
}															\
else														\
{															\
	if(id##_hovered)										\
	{														\
		CALLDELEGATE(delegate, 4)							\
	}														\
	id##_hovered = false;									\
}
#pragma endregion

#pragma endregion

#pragma region Styling

#pragma region Font
#define UISTARTFONT(font) nk_style_push_font(nkCtx, font);
#define UIENDFONT() nk_style_pop_font(nkCtx);
#pragma endregion


#pragma endregion
