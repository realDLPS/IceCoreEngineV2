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