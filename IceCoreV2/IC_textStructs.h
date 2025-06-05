#pragma once

#include <raylib.h>

#include <string>
#include <cassert>

// Just a fair warning to anyone reading this code:
// I wrote this at 12 pm so only god knows what happened here

// Creates an UTF8 strings quickly
#define U8(input) std::string(reinterpret_cast<const char*>(u8##input))

// Returns a localised text quickly
// Preview value is interpreted as UTF8
#define TEXT(id) IC_text(id).str()
// Returns a localised text quickly as a c string
// Preview value is interpreted as UTF8
//
// WARNING
// THE VALUE RETURNED HERE SHOULD BE COPIED
#define TEXTc(id) IC_text(id).c_str()

// Cached version of TEXT macro
// Reduces hashes that need to be done
#define TEXTCache(id, name)						\
static IC_text name##_cache = IC_text(id);		\
std::string name = name##_cache.str();

// Cached version of TEXTc macro
// Reduces hashes that need to be done
#define TEXTcCache(id, name)					\
static IC_text name##_cache = IC_text(id);		\
const char* name = name##_cache.c_str();

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
	IC_text(std::string Identifier)
	{
		assert(Identifier != "NULL" && "IC_text identifier must not be NULL");
		identifier = Identifier;
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
	std::string* stringPointer = nullptr;
	// Previous generation when the string pointer was fetched
	int gen = 0;
};