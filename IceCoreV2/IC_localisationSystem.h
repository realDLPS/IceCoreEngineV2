#pragma once

#include <raylib.h>

#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "IC_delegates.h"

class IC_localisationSystem
{
public:
	IC_localisationSystem();

	// Loads all translations key value pairs (translations) from the current locale. Expects a corresponding [locale].csv to exist in Assets/Languages/
	// Can be used to reload the locale if you changed the csv
	//
	// Returns false if loading locale failed.
	bool LoadLocale();

	// Sets the current locale and loads it
	// Default locale is "en"
	//
	// Returns false and changes back to the default locale if the new locale doesn't have a corresponding [locale].csv
	bool SetLocale(std::string newLocale);

	// Gets current locale
	std::string GetLocale();

	// Returns true if the key exists
	// The localised string is set into the out string
	bool GetLocalised(std::string key, std::string*& out);

	int GetGeneration();
private:
	// Key is the key in the csv
	// Value is what is returned
	std::unordered_map<std::string, std::string> translations;
	std::string locale = "en";

	// Delegates to call when locale is changed
	std::vector<IC_localeChangeDelegate> localeChangeDelegates;

	// How many times language has been changed
	uint16_t generation = 0;
};