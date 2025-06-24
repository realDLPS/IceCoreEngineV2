#pragma once

#include <raylib.h>

#include <functional>

// Creates an IceCore delegate from a function name
#define IC_delegate(method) [this](auto&&... args) -> decltype(auto) { \
    return this->method(std::forward<decltype(args)>(args)...); \
}

// Return true if the input was consumed.
// In case this is an action mapping, -1 is released and 1 is pressed.
// In case this is an axis mapping the value can basically be anything.
typedef std::function<bool(float value)> IC_inputDelegate;

// Called by the localisation system when locale is changed.
// No parameters and no return values.
typedef std::function<void()> IC_localeChangeDelegate;

// Called by a UI button
// 
// Values
// 0: None, button didn't have its state changed this frame (unused currently but reserved)
// 1: Pressed, button has gone down this frame
// 2: Released, button has been released this frame
// 3: Clicked, button has been clicked this frame (a click is a short combination of a press and release determined by a threshold in IC_uiConfig.h)
// 4: Hovered, button has been hovered this frame
// 5: Unhovered, button is no longer hovered
typedef std::function<void(char value)> IC_buttonDelegate;