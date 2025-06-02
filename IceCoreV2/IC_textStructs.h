#pragma once

#include <raylib.h>

#include <string>
#include <cassert>

// Just a fair warning to anyone reading this code:
// I wrote this at 12 pm so only god knows what happened here

// Creates an UTF8 strings quickly
#define U8(input) std::string(reinterpret_cast<const char*>(u8##input))

// Text in IceCore refers to a string that can be localized.
// Each piece of text is a combination of an identifier and preview value.
// \n
// The identifier is used by the localisation system to find the correct string for the current language.
// The preview value is used when the localisation system cannot find a match for the current language. (The recommendation is that the preview value is in English)
// \n
// The identifier "NULL" is reserved for instances where no identifier was specified
struct IC_text
{
public:
	IC_text() = default;
	IC_text(std::string Preview, std::string Identifier)
	{
		assert(Identifier != "NULL" && "IC_text identifier must not be NULL");
		identifier = Identifier;
		preview = Preview;
	}
	IC_text(std::string Preview)
	{
		preview = Preview;
	}

	// Gets the localised text as a string.
	std::string str();

	// Gets the localised text as a c string.
	// 
	// WARNING
	// ANY CALLS TO THIS FUNCTION WILL OVERWRITE THE PREVIOUS C STRING RETURNED BY THIS FUNCTION (ON THIS THREAD)
	// COPY IT IF YOU NEED IT LATER
	const char* c_str()
	{
		static thread_local std::string buffer;

		buffer = str();

		return buffer.c_str();
	}

private:
	std::string identifier = "NULL";
	std::string preview = "";
};