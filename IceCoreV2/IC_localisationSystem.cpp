#include "IC_localisationSystem.h"

IC_localisationSystem::IC_localisationSystem()
{
}

bool IC_localisationSystem::LoadLocale()
{
	FilePathList paths = LoadDirectoryFilesEx("Assets/Languages/", ".csv", true);

	// Check does the locale exist
	if (paths.count > 0)
	{
		std::string path;

		for (size_t i = 0; i < paths.count; i++)
		{
			path = paths.paths[i];

			// File could be in subfolder
			size_t fileNameStart = path.find_last_of("/\\");

			if (fileNameStart == std::string::npos)
			{
				// No subfolder, so file name starts at 0, set to -1 to compensate for offset.
				fileNameStart = -1;
			}

			// Offsetting file name start to not include /
			fileNameStart++;

			// File name without the extension
			std::string fileName = path.substr(fileNameStart, path.size() - 4 /*<--- Size of ".csv"*/ - fileNameStart);

			if (fileName == locale)
			{
				// As the locale exists wipe the current locale
				translations.clear();

				// Load the entire content of the csv
				char* text = LoadFileText(path.c_str());
				std::string rows = text;
				UnloadFileText(text);

				std::replace(rows.begin(), rows.end(), '\r', '\n'); // replace \r with \n

				// Remove duplicate \n\n
				size_t pos;
				while ((pos = rows.find("\n\n")) != std::string::npos) {
					rows.replace(pos, 2, "\n");
				}

				std::istringstream stream(rows);
				std::string line;

				while (std::getline(stream, line))
				{
					size_t comma = line.find_first_of(',');

					translations.emplace(line.substr(0, comma), line.substr(comma + 1, line.length() - comma - 1));
				}
				UnloadDirectoryFiles(paths);
				return true;
			}
		}
	}

	UnloadDirectoryFiles(paths);
	return false;
}

bool IC_localisationSystem::SetLocale(std::string newLocale)
{
	locale = newLocale;

	if (!LoadLocale())
	{
		// Locale couldn't be loaded, loading english locale
		locale = "en";
		LoadLocale();
		return false;
	}
	return true;
}

std::string IC_localisationSystem::GetLocale()
{
	return locale;
}

bool IC_localisationSystem::GetLocalised(std::string key, std::string& out)
{
	if (!translations.contains(key))
	{
		out = "";
		return false;
	}
	out = translations.at(key);
	return true;
}
