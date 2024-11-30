#pragma once

#define uiVis IC_uiVisibility
#define uiAlign IC_uiAlignment
#define uiAnchor IC_uiAlignment
#define uiState IC_uiState

// Different visibility options for UI.
enum class IC_uiVisibility
{
	Visible = 0,
	Hidden = 1
};

enum class IC_uiScaling
{
	Literal = 0, // Scale is a pixel value on screen
	Relative = 1, // Scale is a percentage of the parent size
	LiteralScaledMin = 2, // Scale is a pixel value on screen if the screen were 1920x1080, but scaled scaled according to smallest dimension
	LiteralScaledMax = 3, // Scale is a pixel value on screen if the screen were 1920x1080, but scaled scaled according to largest dimension
	LiteralScaled = 4 // Independently scaled on both dimensions, pixel value is as if the screen were 1920x1080
};

// How the UI is aligned compared to its anchor.
enum class IC_uiAlignment
{
	TopLeft = 0,
	TopCenter = 1,
	TopRight = 2,
	CenterLeft = 3,
	Center = 4,
	CenterRight = 5,
	BottomLeft = 6,
	BottomCenter = 7,
	BottomRight = 8
};

// Provides all states that any UI can be in
// Some states are not applicable to all UI
enum class IC_uiState
{
	Idle = 0, // Base state of UI.
	Hover = 1, // UI is being hovered by the mouse.
	Pressed = 2, // UI is being pressed by the mouse.
	Disabled = 3, // UI is disabled and takes no interaction.
	Focused = 4, // UI is focused in someway, like a text box.
	Unchecked = 5, // Something like a check box or radio button isn't checked.
	Checked = 6, // Something like a check box or radio button is checked.
	Indeterminate = 7 // Something like a check box hasn't been checked or unchecked yet.
};