#pragma once

enum MouseAxis
{
	MOUSE_AXIS_X = 0,
	MOUSE_AXIS_Y = 1
};

enum EInputMode
{
	Game = 0, // Input is never forwarded to the UI.
	UI = 1, // Input is only forwarded to the UI.
	GameAndUI = 2 // Input is first forwarded to the UI and then to the game.
};