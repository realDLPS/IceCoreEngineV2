#pragma once

// Raylib
#include "raylib.h"

// Standard libraries
#include <vector>
#include <string>
#include <map>
#include <unordered_set>

// Other includes
#include "IC_inputStructs.h"

// Note to self, this entire system is pretty cursed for doing inputs, and has no support for different layouts.
// Including but not limited to my precious ÄÖÅ. Others include AZERTY, QWERTZ etc
//
// I would like to introduce mappings for different layouts, but that's something for the future.
//
// Currently actions can consume inputs, so that other actions aren't called. Axis mappings don't care about consumed inputs,
// they will be called normally.
//
// Mouse axis cannot be used as action.
class IC_inputSystem
{
private:
	
	// Mappings
	std::map<std::string, IC_mapping> actionMappings = {};
	std::map<std::string, IC_mapping> axisMappings = {};
	std::map<std::string, float> axisValues = {};
	
	// State of inputs on the last update
	IC_inputState previousInputState;

	// Consumed inputs
	// Uses a stupid system to store different types of inputs in the same set:
	// Keyboard is just the value
	// Mouse is value + 1000
	// Gamepad is value + 2000
	// GamepadAxis is value + 3000
	std::unordered_set<int> consumedInputs = {};

#pragma region PossibleInputs
	// This pains me to do, but I need to create these arrays manually
	// Here is how you can generate this pretty automatically:
	// 
	// Remove comments (https://www.removecomments.com/)
	// Add prefix (https://www.gillmeister-software.com/online-tools/text/add-prefix-or-suffix-to-lines.aspx) Prefix to add = KeyboardKey::
	// Remove whitespace (https://www.browserling.com/tools/remove-all-whitespace)
	// 
	// These are example websites and I could make a python script to do all of it, but I don't feel like it.
	// 
	// In Python:
	// import re
	// myStr=(the string from delete all whitespace)
	// ''.join(re.sub(r'=[0-9]+','',myStr))
	//
	// And once again, this thing sucks, and is probably inefficient as all hell.
	KeyboardKey keyboardKeys[110] = { KeyboardKey::KEY_NULL,KeyboardKey::KEY_APOSTROPHE,KeyboardKey::KEY_COMMA,KeyboardKey::KEY_MINUS,KeyboardKey::KEY_PERIOD,KeyboardKey::KEY_SLASH,KeyboardKey::KEY_ZERO,KeyboardKey::KEY_ONE,KeyboardKey::KEY_TWO,KeyboardKey::KEY_THREE,KeyboardKey::KEY_FOUR,KeyboardKey::KEY_FIVE,KeyboardKey::KEY_SIX,KeyboardKey::KEY_SEVEN,KeyboardKey::KEY_EIGHT,KeyboardKey::KEY_NINE,KeyboardKey::KEY_SEMICOLON,KeyboardKey::KEY_EQUAL,KeyboardKey::KEY_A,KeyboardKey::KEY_B,KeyboardKey::KEY_C,KeyboardKey::KEY_D,KeyboardKey::KEY_E,KeyboardKey::KEY_F,KeyboardKey::KEY_G,KeyboardKey::KEY_H,KeyboardKey::KEY_I,KeyboardKey::KEY_J,KeyboardKey::KEY_K,KeyboardKey::KEY_L,KeyboardKey::KEY_M,KeyboardKey::KEY_N,KeyboardKey::KEY_O,KeyboardKey::KEY_P,KeyboardKey::KEY_Q,KeyboardKey::KEY_R,KeyboardKey::KEY_S,KeyboardKey::KEY_T,KeyboardKey::KEY_U,KeyboardKey::KEY_V,KeyboardKey::KEY_W,KeyboardKey::KEY_X,KeyboardKey::KEY_Y,KeyboardKey::KEY_Z,KeyboardKey::KEY_LEFT_BRACKET,KeyboardKey::KEY_BACKSLASH,KeyboardKey::KEY_RIGHT_BRACKET,KeyboardKey::KEY_GRAVE,KeyboardKey::KEY_SPACE,KeyboardKey::KEY_ESCAPE,KeyboardKey::KEY_ENTER,KeyboardKey::KEY_TAB,KeyboardKey::KEY_BACKSPACE,KeyboardKey::KEY_INSERT,KeyboardKey::KEY_DELETE,KeyboardKey::KEY_RIGHT,KeyboardKey::KEY_LEFT,KeyboardKey::KEY_DOWN,KeyboardKey::KEY_UP,KeyboardKey::KEY_PAGE_UP,KeyboardKey::KEY_PAGE_DOWN,KeyboardKey::KEY_HOME,KeyboardKey::KEY_END,KeyboardKey::KEY_CAPS_LOCK,KeyboardKey::KEY_SCROLL_LOCK,KeyboardKey::KEY_NUM_LOCK,KeyboardKey::KEY_PRINT_SCREEN,KeyboardKey::KEY_PAUSE,KeyboardKey::KEY_F1,KeyboardKey::KEY_F2,KeyboardKey::KEY_F3,KeyboardKey::KEY_F4,KeyboardKey::KEY_F5,KeyboardKey::KEY_F6,KeyboardKey::KEY_F7,KeyboardKey::KEY_F8,KeyboardKey::KEY_F9,KeyboardKey::KEY_F10,KeyboardKey::KEY_F11,KeyboardKey::KEY_F12,KeyboardKey::KEY_LEFT_SHIFT,KeyboardKey::KEY_LEFT_CONTROL,KeyboardKey::KEY_LEFT_ALT,KeyboardKey::KEY_LEFT_SUPER,KeyboardKey::KEY_RIGHT_SHIFT,KeyboardKey::KEY_RIGHT_CONTROL,KeyboardKey::KEY_RIGHT_ALT,KeyboardKey::KEY_RIGHT_SUPER,KeyboardKey::KEY_KB_MENU,KeyboardKey::KEY_KP_0,KeyboardKey::KEY_KP_1,KeyboardKey::KEY_KP_2,KeyboardKey::KEY_KP_3,KeyboardKey::KEY_KP_4,KeyboardKey::KEY_KP_5,KeyboardKey::KEY_KP_6,KeyboardKey::KEY_KP_7,KeyboardKey::KEY_KP_8,KeyboardKey::KEY_KP_9,KeyboardKey::KEY_KP_DECIMAL,KeyboardKey::KEY_KP_DIVIDE,KeyboardKey::KEY_KP_MULTIPLY,KeyboardKey::KEY_KP_SUBTRACT,KeyboardKey::KEY_KP_ADD,KeyboardKey::KEY_KP_ENTER,KeyboardKey::KEY_KP_EQUAL,KeyboardKey::KEY_BACK,KeyboardKey::KEY_MENU,KeyboardKey::KEY_VOLUME_UP,KeyboardKey::KEY_VOLUME_DOWN };
	MouseButton mouseButtons[7] = { MouseButton::MOUSE_LEFT_BUTTON,MouseButton::MOUSE_BUTTON_RIGHT,MouseButton::MOUSE_BUTTON_MIDDLE,MouseButton::MOUSE_BUTTON_SIDE,MouseButton::MOUSE_BUTTON_EXTRA,MouseButton::MOUSE_BUTTON_FORWARD,MouseButton::MOUSE_BUTTON_BACK };
	GamepadButton gamepadButtons[18] = { GamepadButton::GAMEPAD_BUTTON_UNKNOWN,GamepadButton::GAMEPAD_BUTTON_LEFT_FACE_UP,GamepadButton::GAMEPAD_BUTTON_LEFT_FACE_RIGHT,GamepadButton::GAMEPAD_BUTTON_LEFT_FACE_DOWN,GamepadButton::GAMEPAD_BUTTON_LEFT_FACE_LEFT,GamepadButton::GAMEPAD_BUTTON_RIGHT_FACE_UP,GamepadButton::GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,GamepadButton::GAMEPAD_BUTTON_RIGHT_FACE_DOWN,GamepadButton::GAMEPAD_BUTTON_RIGHT_FACE_LEFT,GamepadButton::GAMEPAD_BUTTON_LEFT_TRIGGER_1,GamepadButton::GAMEPAD_BUTTON_LEFT_TRIGGER_2,GamepadButton::GAMEPAD_BUTTON_RIGHT_TRIGGER_1,GamepadButton::GAMEPAD_BUTTON_RIGHT_TRIGGER_2,GamepadButton::GAMEPAD_BUTTON_MIDDLE_LEFT,GamepadButton::GAMEPAD_BUTTON_MIDDLE,GamepadButton::GAMEPAD_BUTTON_MIDDLE_RIGHT,GamepadButton::GAMEPAD_BUTTON_LEFT_THUMB,GamepadButton::GAMEPAD_BUTTON_RIGHT_THUMB };
	GamepadAxis gamepadAxis[6] = {GamepadAxis::GAMEPAD_AXIS_LEFT_X, GamepadAxis::GAMEPAD_AXIS_LEFT_Y, GamepadAxis::GAMEPAD_AXIS_RIGHT_X, GamepadAxis::GAMEPAD_AXIS_RIGHT_Y, GamepadAxis::GAMEPAD_AXIS_LEFT_TRIGGER, GamepadAxis::GAMEPAD_AXIS_RIGHT_TRIGGER};

#pragma endregion


public:
	void UpdateInputs();
	IC_inputState GetInputState();

#pragma region Mappings
	void AddMapping(std::string name, IC_mapping mapping, bool axis);
	IC_mapping* GetMapping(std::string name, bool axis);
	float GetAxisValue(std::string name);
#pragma endregion

private:
#pragma region Action mapping functions
	// Returns -1 if released, 1 if pressed, 0 if nothing changed.
	float EvaluateBindingAsAction(IC_binding binding);
	// Checks has this binding already been consumed.
	bool CheckIsBindingConsumed(IC_binding binding);
	// Consuming a binding.
	void ConsumeBinding(IC_binding binding);
#pragma endregion
#pragma region Axis mapping functions
	float EvaluateBindingAsAxis(IC_binding binding);
#pragma endregion

};