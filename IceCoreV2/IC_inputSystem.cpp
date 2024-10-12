#include "IC_inputSystem.h"

void IC_inputSystem::UpdateInputs()
{
	IC_inputState currentInputState = GetInputState();

	consumedInputs = {}; // Clear consumed inputs


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


	for (auto const& mapping : axisMappings)
	{

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
		consumedInputs.insert(binding.key);
		return;
	case 1:
		consumedInputs.insert(binding.mouseButton + 1000);
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
