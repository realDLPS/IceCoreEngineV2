#pragma once

// Raylib
#include "raylib.h"

// Standard libraries
#include <vector>
#include <functional>

// Other includes
#include "vectorHelpers.h"

// So, for now this "delegate" typedef can be here, but if more are introduced I may move them to their own header file.

// Return true if the input was consumed.
// In case this is an action mapping, -1 is released and 1 is pressed.
// In case this is an axis mapping the value can basically be anything.
typedef std::function<bool (float value)> IC_inputDelegate;

// Something like a keyboard key, mouse button, controller button, mouse x-axis or controller stick.
struct IC_binding
{
	IC_binding(KeyboardKey key, float multiplier = 1.0f) {this->bindingType = 0; this->key = key; this->multiplier = multiplier;};
	IC_binding(MouseButton mouseButton, float multiplier = 1.0f) {this->bindingType = 1; this->mouseButton = mouseButton; this->multiplier = multiplier;};
	IC_binding(GamepadButton gamepadButton, float multiplier = 1.0f) {this->bindingType = 2; this->gamepadButton = gamepadButton; this->multiplier = multiplier;};
	IC_binding(GamepadAxis gamepadAxis, float multiplier = 1.0f) {this->bindingType = 3; this->gamepadAxis = gamepadAxis; this->multiplier = multiplier;}

	// Set by constructors.
	uint8_t bindingType = 0; // 0 = key, 1 = mouse button, 2 = gamepad button, 3 = gamepad axis
	
	// The value of a binding is multiplied by this value.
	float multiplier = 1.0f;

	KeyboardKey key = KEY_NULL;
	MouseButton mouseButton = MOUSE_BUTTON_LEFT;
	GamepadButton gamepadButton = GAMEPAD_BUTTON_UNKNOWN;
	GamepadAxis gamepadAxis = GAMEPAD_AXIS_LEFT_X;

	bool operator==(const IC_binding& other) const
	{
		switch (bindingType)
		{
			case 0:
				return key == other.key && multiplier == other.multiplier;
			case 1:
				return mouseButton == other.mouseButton && multiplier == other.multiplier;
			case 2:
				return gamepadButton == other.gamepadButton && multiplier == other.multiplier;
			case 3:
				return gamepadAxis == other.gamepadAxis && multiplier == other.multiplier;
			default:
				return false;
		}
	}
};
// Something like jump, shoot or walk forward.
struct IC_mapping
{
	// All bindings that are a part of this mapping.
	std::vector<IC_binding> bindings;
	// Delegates are called in order until one of them consumes the input.
	std::vector<IC_inputDelegate> delegates;

	IC_mapping() {};
	IC_mapping(IC_binding binding) {this->bindings = {binding};}
	IC_mapping(std::vector<IC_binding> bindings) {this->bindings = bindings;}

	// Modification
	void AddBinding(IC_binding binding) {this->bindings.push_back(binding);}
	void RemoveBinding(IC_binding binding) 
	{
		int32_t index = this->GetBindingIndex(binding);
		if(index == -1) {return;}
		this->bindings.erase(this->bindings.begin() + index);
	}
	void ClearBindings() {this->bindings.clear();}
	void AddDelegate(IC_inputDelegate delegate) {this->delegates.push_back(delegate);}
	void ClearDelegates() {this->delegates.clear();}
private:
	int32_t GetBindingIndex(IC_binding binding)
	{
		for (int i = 0; i < this->bindings.size(); i++)
		{
			if (this->bindings[i] == binding)
			{
				return i;
			}
		}
		return -1;
	};
};

struct IC_inputState
{
	IC_inputState() {};

	bool keyboardState[110] = {false};
	bool mouseState[7] = {false};
	bool gamepadState[18] = {false};
	float gamepadAxis[6] = {0.0f};
	Vector2 mouseDelta = Vec2(0.0f);
};