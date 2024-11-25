#pragma once

#define uiVis IC_uiVisibility
#define uiAlign IC_uiAlignment
#define uiAnchor IC_uiAlignment

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

// Interactive UI states

// What state the button is in
enum class IC_buttonState
{
	Idle = 0,
	Hover = 1,
	Pressed = 2
};

// What state the slider is in
enum class IC_sliderState
{
	Idle = 0,
	Hover = 1,
	Pressed = 2
};

// What state the checkbox is in
enum class IC_checkboxState
{
	Unchecked = 0,
	Checked = 1,
	Indeterminate = 2
};

// What state the radio button is in
enum class IC_radioState
{
	Unchecked = 0,
	Checked = 1
};