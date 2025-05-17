#include "IC_inputSystem.h"

void IC_inputSystem::UpdateInputs(float deltaTime)
{
	currentDeltaTime = deltaTime;

	IC_inputState currentInputState = GetInputState();

	consumedInputs = {}; // Clear consumed inputs
	scrollConsumed = false; // Clear scroll consumed

	// Has ui consumed the input?
	bool uiConsumedInput = false;

	// Handling UI
	if (InputMode == EInputMode::UI || InputMode == EInputMode::GameAndUI)
	{
		nk_input_begin(nkCtx);

		nk_input_motion(nkCtx, GetMouseX(), GetMouseY()); // Send mouse position

		if (InputMode == EInputMode::UI || nk_item_is_any_active(nkCtx))
		{
			// Scroll value is always sent in UI mode
			// Scroll value is only sent in GameAndUI mode if something is hovered
			nk_input_scroll(nkCtx, nk_vec2(0.0f, GetMouseWheelMove()));
			scrollConsumed = true;

			// Sending mouse clicks
			nk_input_button(nkCtx, NK_BUTTON_LEFT, GetMouseX(), GetMouseY(), IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT));
			if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT)) ConsumeMouseButton(MouseButton::MOUSE_BUTTON_LEFT); uiConsumedInput = true;

			nk_input_button(nkCtx, NK_BUTTON_RIGHT, GetMouseX(), GetMouseY(), IsMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT));
			if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT)) ConsumeMouseButton(MouseButton::MOUSE_BUTTON_RIGHT); uiConsumedInput = true;

			nk_input_button(nkCtx, NK_BUTTON_MIDDLE, GetMouseX(), GetMouseY(), IsMouseButtonDown(MouseButton::MOUSE_BUTTON_MIDDLE));
			if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_MIDDLE)) ConsumeMouseButton(MouseButton::MOUSE_BUTTON_MIDDLE); uiConsumedInput = true;
		}
		// This other check is stolen from nk_item_is_any_active to check is anything active (not just hovered)
		if (InputMode == EInputMode::UI || (nkCtx->last_widget_state & NK_WIDGET_STATE_MODIFIED)) 
		{
			uiConsumedInput = true; // Either in UI mode or a widget is active so input is consumed.
			
			// Sending keys over if necessary
			nk_input_key(nkCtx, NK_KEY_SHIFT, (IsKeyPressed(KeyboardKey::KEY_LEFT_SHIFT) || IsKeyPressed(KeyboardKey::KEY_RIGHT_SHIFT)));
			nk_input_key(nkCtx, NK_KEY_CTRL, (IsKeyPressed(KeyboardKey::KEY_LEFT_CONTROL) || IsKeyPressed(KeyboardKey::KEY_RIGHT_CONTROL)));
			nk_input_key(nkCtx, NK_KEY_DEL, (IsKeyPressed(KeyboardKey::KEY_DELETE)));
			nk_input_key(nkCtx, NK_KEY_ENTER, (IsKeyPressed(KeyboardKey::KEY_ENTER) || IsKeyPressed(KeyboardKey::KEY_KP_ENTER)));
			nk_input_key(nkCtx, NK_KEY_TAB, (IsKeyPressed(KeyboardKey::KEY_TAB)));
			nk_input_key(nkCtx, NK_KEY_BACKSPACE, (IsKeyPressed(KeyboardKey::KEY_BACKSPACE)));
			

			nk_input_key(nkCtx, NK_KEY_COPY, (IsKeyPressed(KeyboardKey::KEY_C) && ((IsKeyPressed(KeyboardKey::KEY_LEFT_CONTROL) || IsKeyPressed(KeyboardKey::KEY_RIGHT_CONTROL)))));
			nk_input_key(nkCtx, NK_KEY_CUT, (IsKeyPressed(KeyboardKey::KEY_X) && ((IsKeyPressed(KeyboardKey::KEY_LEFT_CONTROL) || IsKeyPressed(KeyboardKey::KEY_RIGHT_CONTROL)))));
			nk_input_key(nkCtx, NK_KEY_PASTE, (IsKeyPressed(KeyboardKey::KEY_V) && ((IsKeyPressed(KeyboardKey::KEY_LEFT_CONTROL) || IsKeyPressed(KeyboardKey::KEY_RIGHT_CONTROL)))));
			nk_input_key(nkCtx, NK_KEY_TEXT_UNDO, (IsKeyPressed(KeyboardKey::KEY_Z) && ((IsKeyPressed(KeyboardKey::KEY_LEFT_CONTROL) || IsKeyPressed(KeyboardKey::KEY_RIGHT_CONTROL)))));
			nk_input_key(nkCtx, NK_KEY_TEXT_REDO, (IsKeyPressed(KeyboardKey::KEY_Y) && ((IsKeyPressed(KeyboardKey::KEY_LEFT_CONTROL) || IsKeyPressed(KeyboardKey::KEY_RIGHT_CONTROL)))));
			nk_input_key(nkCtx, NK_KEY_TEXT_SELECT_ALL, (IsKeyPressed(KeyboardKey::KEY_A) && ((IsKeyPressed(KeyboardKey::KEY_LEFT_CONTROL) || IsKeyPressed(KeyboardKey::KEY_RIGHT_CONTROL)))));
			nk_input_key(nkCtx, NK_KEY_TEXT_WORD_LEFT, (IsKeyPressed(KeyboardKey::KEY_LEFT) && ((IsKeyPressed(KeyboardKey::KEY_LEFT_CONTROL) || IsKeyPressed(KeyboardKey::KEY_RIGHT_CONTROL)))));
			nk_input_key(nkCtx, NK_KEY_TEXT_WORD_RIGHT, (IsKeyPressed(KeyboardKey::KEY_RIGHT) && ((IsKeyPressed(KeyboardKey::KEY_LEFT_CONTROL) || IsKeyPressed(KeyboardKey::KEY_RIGHT_CONTROL)))));

			nk_input_key(nkCtx, NK_KEY_UP, (IsKeyPressed(KeyboardKey::KEY_UP)));
			nk_input_key(nkCtx, NK_KEY_DOWN, (IsKeyPressed(KeyboardKey::KEY_DOWN)));
			nk_input_key(nkCtx, NK_KEY_LEFT, (IsKeyPressed(KeyboardKey::KEY_LEFT)));
			nk_input_key(nkCtx, NK_KEY_RIGHT, (IsKeyPressed(KeyboardKey::KEY_RIGHT)));
			nk_input_key(nkCtx, NK_KEY_TEXT_LINE_START, (IsKeyPressed(KeyboardKey::KEY_HOME)));
			nk_input_key(nkCtx, NK_KEY_TEXT_LINE_END, (IsKeyPressed(KeyboardKey::KEY_END)));

			int inputChar = GetCharPressed();

			while (inputChar != 0)
			{
				nk_glyph glyph;
				int byteCount = nk_utf_encode((nk_rune)inputChar, glyph, NK_UTF_SIZE);
				if (byteCount < NK_UTF_SIZE) glyph[byteCount] = '\0';
				nk_input_glyph(nkCtx, glyph);
				inputChar = GetKeyPressed();
			}
		}

		nk_input_end(nkCtx);
	}

	if (!uiConsumedInput)
	{
		for (auto const& mapping : actionMappings)
		{
			for (auto const& binding : mapping.second.bindings)
			{
				if (!CheckIsBindingConsumed(binding))
				{
					float evaluation = EvaluateBindingAsAction(binding);

					// If the evaluation is 0 nothing has changed, and so we can skip to the next binding.
					if (evaluation == 0.0f) { continue; }

					for (auto const& delegate : mapping.second.delegates)
					{
						if (delegate(evaluation)) // Delegates return true if they consume the input.
						{
							ConsumeBinding(binding);
							goto consumed;
						}
					}

				}
			}
			// We goto here if a delegate consumes the input, as a mapping shouldn't have it's delegates called 
			// multiple times in a single update.
			//
			// Unless someone figures out how I can break multiple for loops at once without using another variable
			// this will be used. I am far too happy about using goto properly in this day and age.
		consumed:
			continue;
		}
	}

	for (auto const& mapping : axisMappings)
	{
		float evaluation = 0.0f;

		if (true/*!uiConsumedInput*/) // Will update all values to 0 if ui consumed input (currently disabled for testing)
		{
			for (auto const& binding : mapping.second.bindings)
			{
				evaluation += EvaluateBindingAsAxis(binding);
			}
		}

		for (auto const& delegate : mapping.second.delegates)
		{
			delegate(evaluation);
		}

		axisValues[mapping.first] = evaluation;
	}

	// Store current state.
	previousInputState = currentInputState;
	return;
}

IC_inputState IC_inputSystem::GetInputState()
{
    IC_inputState inputState = IC_inputState();
	
	// Yes, the array lengths are hardcoded, but I'll fix that if they happen to change in the future, but I doubt it.
	// Probably cursed the project by writing that :|

	// Keyboard
	for (size_t i = 0; i < 110; i++)
	{
		inputState.keyboardState[i] = IsKeyDown(keyboardKeys[i]);
	}
	// Mouse
	for (size_t i = 0; i < 7; i++)
	{
		inputState.mouseState[i] = IsMouseButtonDown(mouseButtons[i]);
	}
	inputState.mouseDelta = GetMouseDelta();

	// Gamepad
	// Sorry split screen devs, gonna fix this if someone complains of if I need it myself.
	if (IsGamepadAvailable(0))
	{
		// Buttons
		for (size_t i = 0; i < 18; i++)
		{
			inputState.gamepadState[i] = IsGamepadButtonDown(0, gamepadButtons[i]);
		}
		// Axes
		for (size_t i = 0; i < 6; i++)
		{
			inputState.gamepadAxis[i] = GetGamepadAxisMovement(0, gamepadAxis[i]);
		}
	}
	
    return inputState;
}

void IC_inputSystem::ChangeInputMode(EInputMode newMode)
{
	InputMode = newMode;
}

void IC_inputSystem::AddMapping(std::string name, IC_mapping mapping, bool axis)
{
	if (axis)
	{
		axisMappings.insert({ name, mapping });
	}
	else
	{
		actionMappings.insert({ name, mapping });
	}
}

IC_mapping* IC_inputSystem::GetMapping(std::string name, bool axis)
{
	if (axis && axisMappings.contains(name))
	{
		return &axisMappings[name];
	}
	else if (actionMappings.contains(name))
	{
		return &actionMappings[name];
	}
	return nullptr;
}

float IC_inputSystem::GetAxisValue(std::string name)
{
	return axisValues[name];
}

float IC_inputSystem::EvaluateBindingAsAction(IC_binding binding)
{
	switch (binding.bindingType)
	{
	default:
		return 0.0f;
	case 0:
		return IsKeyPressed(binding.key) ? 1.0f : (IsKeyReleased(binding.key) ? -1.0f : 0.0f);
	case 1:
		return IsMouseButtonPressed(binding.mouseButton) ? 1.0f : (IsMouseButtonReleased(binding.mouseButton) ? -1.0f : 0.0f);
	case 4:
		return 0.0f; // Sorry, you cannot use a mouse axis as an action
	case 2:
		if (!IsGamepadAvailable) { return 0.0f; } // No gamepad
		return IsGamepadButtonPressed(0, binding.gamepadButton) ? 1.0f : (IsGamepadButtonReleased(0, binding.gamepadButton) ? -1.0f : 0.0f);
	case 3:
		if (!IsGamepadAvailable) { return 0.0f; } // No gamepad
		bool wasPressed = previousInputState.gamepadAxis[binding.gamepadAxis] > 0.0f;
		bool isPressed = GetGamepadAxisMovement(0, binding.gamepadAxis) > 0.0f;
		if (wasPressed == isPressed) { return 0.0f; } // Nothing changed
		if (isPressed) { return 1.0f; } // Pressed
		return -1.0f; // Released
	}

}

bool IC_inputSystem::CheckIsBindingConsumed(IC_binding binding)
{
	switch (binding.bindingType)
	{
	case 0:
		return consumedInputs.contains(binding.key);
	case 1:
		return consumedInputs.contains(binding.mouseButton + 1000);
	case 4:
		return true; // Cannot use mouse axis as action
	case 2:
		if (!IsGamepadAvailable) { return false; } // No gamepad, no sending non-existent inputs
		return consumedInputs.contains(binding.gamepadButton + 2000);
	case 3:
		if (!IsGamepadAvailable) { return true; } // No gamepad, no sending non-existent inputs
		return consumedInputs.contains(binding.gamepadAxis + 3000);
	default:
		return true; // Don't want to send any inputs that don't exist
	}
}

void IC_inputSystem::ConsumeBinding(IC_binding binding)
{
	switch (binding.bindingType)
	{
	case 0:
		ConsumeKey(binding.key);
		return;
	case 1:
		ConsumeMouseButton(binding.mouseButton);
		return;
	case 4:
		return;
	case 2:
		if (!IsGamepadAvailable) { return; } // No gamepad
		consumedInputs.insert(binding.gamepadButton + 2000);
		return;
	case 3:
		if (!IsGamepadAvailable) { return; } // No gamepad
		consumedInputs.insert(binding.gamepadAxis + 3000);
		return;
	default:
		return;
	}
}

void IC_inputSystem::ConsumeKey(KeyboardKey key)
{
	consumedInputs.insert(key);
}

void IC_inputSystem::ConsumeMouseButton(MouseButton button)
{
	consumedInputs.insert(button + 1000);
}

float IC_inputSystem::EvaluateBindingAsAxis(IC_binding binding)
{
	switch (binding.bindingType)
	{
	case 0:
		if (CheckIsBindingConsumed(binding)) { return 0.0f; } // Binding consumed
		return (IsKeyDown(binding.key) ? (binding.useDeltaScaling ? currentDeltaTime : 1.0f) : 0.0f) * binding.multiplier;
	case 1:
		if (CheckIsBindingConsumed(binding)) { return 0.0f; } // Binding consumed
		return (IsMouseButtonDown(binding.mouseButton) ? (binding.useDeltaScaling ? currentDeltaTime : 1.0f) : 0.0f) * binding.multiplier;
	case 2:
		if (!IsGamepadAvailable) { return 0.0f; } // No gamepad
		if (CheckIsBindingConsumed(binding)) { return 0.0f; } // Binding consumed
		return (IsGamepadButtonDown(0, binding.gamepadButton) ? (binding.useDeltaScaling ? currentDeltaTime : 1.0f) : 0.0f) * binding.multiplier;
	case 4:
		if (scrollConsumed) { return 0.0f; } // Scroll has been consumed
		return binding.mouseAxis == 0 ? GetMouseDelta().x * binding.multiplier : GetMouseDelta().y * binding.multiplier;
	case 3:
		if (!IsGamepadAvailable) { return 0.0f; } // No gamepad
		if (CheckIsBindingConsumed(binding)) { return 0.0f; } // Binding consumed
		return GetGamepadAxisMovement(0, binding.gamepadAxis) * binding.multiplier * (binding.useDeltaScaling ? currentDeltaTime : 1.0f);
	default:
		return 0.0f;
	}
}
