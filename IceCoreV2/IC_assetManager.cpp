#include "IC_assetManager.h"

#include "IC_game.h"

#include "IC_fontConfig.h"

void IC_assetManager::ReloadAllAssets()
{
	UnloadAssets();

	LoadCommonAssets();
}

Texture2D IC_assetManager::GetTexture(std::string name)
{
	// In the future check the level assets first

	if (commonTextures.contains(name))
	{
		return commonTextures[name];
	}

	game->ICLog("Warning: Texture with name " + name + " does not exist.");
	return missingTexture;
}

Sound IC_assetManager::GetSound(std::string name)
{
	// In the future check the level assets first

	if (commonTextures.contains(name))
	{
		return commonSounds[name];
	}

	game->ICLog("Warning: Sound with name " + name + " does not exist.");
	return missingSound;
}

Font IC_assetManager::GetFont()
{
	return uiStyle.font;
}

std::map<std::string, std::string> IC_assetManager::ParseStringToConfig(std::string configString)
{
	std::istringstream stream(configString);
	std::string line;

	std::map<std::string, std::string> configMap;

	while (std::getline(stream, line))
	{
		// Remove whitespace
		line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; }), line.end());
		// Remove end comments
		if (auto pos = line.find('#'); pos != std::string::npos)
		{
			line.erase(pos);
		}

		if (auto pos = line.find('='); pos != std::string::npos)
		{
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1);
			configMap.insert({ key, value });
		}
	}

	return configMap;
}

std::string IC_assetManager::LoadFileAsText(std::string path)
{
	char* temp = LoadFileText(path.c_str());
	std::string str = temp;
	UnloadFileText(temp);
	return str;
}

bool IC_assetManager::LoadFont(std::string name, float size)
{
	Font* font;
	auto iter_0 = raylibFonts.find(name);
	if (iter_0 == raylibFonts.end()) // Font hasn't been loaded
	{
		auto pathsMap = LoadDirFileList("Assets/Fonts/", NULL, true);

		if (pathsMap.contains(name + ".ictxt"))
		{
			auto fontConfig = ParseStringToConfig(LoadFileAsText(pathsMap[name + ".ictxt"]));

			int loadSize = 64; // Default size
			if (fontConfig.contains("size"))
			{
				loadSize = std::stoi(fontConfig["size"]);
			}

			if (!fontConfig.contains("font"))
			{
				game->ICLog("Missing font parameter in font config for font " + name);
				return false;
			}

			std::vector<int> codePoints = std::vector(CODEPOINTSCPP.begin(), CODEPOINTSCPP.end());

			Font* tempFont = new Font();

			*tempFont = LoadFontEx(pathsMap[fontConfig["font"]].c_str(), loadSize, codePoints.data(), CODEPOINTCOUNT);

			raylibFonts.emplace(name, tempFont);
			font = tempFont;
		}
		else
		{
			game->ICLog("Missing font config for font " + name);
			return false;
		}
	}
	else
	{
		font = iter_0->second;
	}

	IC_font newIC_Font = IC_font();

	newIC_Font.nkFont = NuklearFontFromRaylibFont(font, size);

	if (fonts.contains(name))
	{
		auto& sizes = fonts[name];
		if (sizes.contains(size))
		{
			// Font already exists with the correct size
			return true;
		}

		sizes.emplace(size, std::move(newIC_Font));
		return true;
	}
	else
	{
		fonts[name].emplace(size, std::move(newIC_Font));
		return true;
	}

	return false;
}

IC_font IC_assetManager::GetICFont(std::string name, float size)
{
	auto iter_0 = fonts.find(name);
	if (iter_0 != fonts.end())
	{
		auto& sizes = iter_0->second;

		auto iter_1 = sizes.find(size);
		if (iter_1 != sizes.end())
		{
			return iter_1->second;
		}
	}

	// Font doesn't exist yet
	LoadFont(name, size);

	// Reload
	iter_0 = fonts.find(name);
	if (iter_0 != fonts.end())
	{
		auto& sizes = iter_0->second;

		auto iter_1 = sizes.find(size);
		if (iter_1 != sizes.end())
		{
			return iter_1->second;
		}
	}
}

std::map<std::string, std::string> IC_assetManager::LoadDirFileList(const char* path, const char* filter, bool scanSubdirs)
{
	FilePathList paths = LoadDirectoryFilesEx(path, filter, scanSubdirs);

	// Key is file name, value is file path
	std::map<std::string, std::string> pathsMap;

	// Adding all paths to the set for clarity
	for (size_t i = 0; i < paths.count; i++)
	{
		std::string fullPath = paths.paths[i];

		auto fileNameStart = fullPath.find_last_of('\\');

		if (fileNameStart != std::string::npos)
		{
			std::string fileName = fullPath.substr(fileNameStart + 1);
			//std::string path = fullPath.substr(0, fileNameStart + 1);

			pathsMap.insert({ fileName, fullPath });
		}
	}

	UnloadDirectoryFiles(paths);
	return pathsMap;
}

void IC_assetManager::LoadTextures(std::string assetFolder, bool common)
{
	FilePathList paths = LoadDirectoryFilesEx(assetFolder.c_str(), NULL, true);

	// Loop over all paths
	for (size_t i = 0; i < paths.count; i++)
	{
		std::string path = paths.paths[i];

		for (const auto& extension : textureExtensions)
		{
			// Check if file has valid extension.
			if (path.ends_with(extension))
			{
				Texture2D texture = LoadTexture(path.c_str());

				// File could be in subfolder
				size_t fileNameStart = path.find_last_of("/\\");

				if(fileNameStart == std::string::npos)
				{
					// No subfolder, so file name starts at 0, set to -1 to compensate for offset.
					fileNameStart = -1;
				}

				// Offsetting file name start to not include /
				fileNameStart++;

				// File name without the extension
				std::string fileName = path.substr(fileNameStart, path.size() - extension.size() - fileNameStart);

				if (common)
				{
					commonTextures.insert({ fileName, texture });
				}
				else
				{
					// Not added anywhere as levels aren't supported yet.
					// levelTextures.insert({ fileName, texture });
				}

				break; // File cannot have multiple extensions
			}
		}
		
	}

	UnloadDirectoryFiles(paths);
}

void IC_assetManager::LoadSounds(std::string assetFolder, bool common)
{
	FilePathList paths = LoadDirectoryFilesEx(assetFolder.c_str(), NULL, true);

	// Loop over all paths
	for (size_t i = 0; i < paths.count; i++)
	{
		std::string path = paths.paths[i];

		for (const auto& extension : soundExtensions)
		{
			// Check if file has valid extension.
			if (path.ends_with(extension))
			{
				Sound sound = LoadSound(path.c_str());
				SetSoundVolume(sound, 0.5f);

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
				std::string fileName = path.substr(fileNameStart, path.size() - extension.size() - fileNameStart);

				if (common)
				{
					commonSounds.insert({ fileName, sound });
				}
				else
				{
					// Not added anywhere as levels aren't supported yet.
					// levelSounds.insert({ fileName, sound });
				}

				break; // File cannot have multiple extensions
			}
		}

	}

	UnloadDirectoryFiles(paths);
}

void IC_assetManager::LoadUIStyle(std::string assetFolder)
{
	std::map<std::string, std::string> pathsMap = LoadDirFileList(assetFolder.c_str(), NULL, false);

	// Loading button
	if (pathsMap.contains("Button.png") && pathsMap.contains("Button.ictxt"))
	{
		IC_sprite buttonSprite = IC_sprite(LoadTexture((pathsMap["Button.png"]).c_str()));

		std::string buttonConfig = LoadFileAsText(pathsMap["Button.ictxt"]);

		std::map<std::string, std::string> buttonConfigMap = ParseStringToConfig(buttonConfig);

		if (buttonConfigMap.contains("useSlicing"))
		{
			if (buttonConfigMap["useSlicing"] == "true")
			{
				buttonSprite.UseSlicing = true;
			}
			else
			{
				buttonSprite.UseSlicing = false;
			}
		}
		else
		{
			game->ICLog("Warning: Invalid config for button in: " + assetFolder + "Button.ictxt. Missing useSlicing");
		}

		if (buttonConfigMap.contains("slicingType"))
		{
			buttonSprite.SlicingType = std::stoi(buttonConfigMap["slicingType"]);
		}
		else
		{
			game->ICLog("Warning: Invalid config for button in: " + assetFolder + "Button.ictxt. Missing slicingType");
		}

		if(buttonConfigMap.contains("left"))
		{
			buttonSprite.Left = std::stoi(buttonConfigMap["left"]);
		}
		else
		{
			game->ICLog("Warning: Invalid config for button in: " + assetFolder + "Button.ictxt. Missing left margin");
		}

		if (buttonConfigMap.contains("top"))
		{
			buttonSprite.Top = std::stoi(buttonConfigMap["top"]);
		}
		else
		{
			game->ICLog("Warning: Invalid config for button in: " + assetFolder + "Button.ictxt. Missing top margin");
		}

		if (buttonConfigMap.contains("right"))
		{
			buttonSprite.Right = std::stoi(buttonConfigMap["right"]);
		}
		else
		{
			game->ICLog("Warning: Invalid config for button in: " + assetFolder + "Button.ictxt. Missing right margin");
		}

		if (buttonConfigMap.contains("bottom"))
		{
			buttonSprite.Bottom = std::stoi(buttonConfigMap["bottom"]);
		}
		else
		{
			game->ICLog("Warning: Invalid config for button in: " + assetFolder + "Button.ictxt. Missing bottom margin");
		}

		uiStyle.button = buttonSprite;
	}

	if (pathsMap.contains("Font.ictxt"))
	{
		char* temp = LoadFileText((pathsMap.at("Font.ictxt")).c_str());
		std::string fontConfig = temp;
		UnloadFileText(temp);

		std::map<std::string, std::string> fontConfigMap = ParseStringToConfig(fontConfig);

		// Just some default
		int fontSize = 128;

		if (fontConfigMap.contains("size"))
		{
			fontSize = std::stoi(fontConfigMap["size"]);
		}
		else
		{
			game->ICLog("Warning: Invalid config for font in: " + assetFolder + "Font.ictxt. Missing size, assuming font size to be 128");
		}

		if (fontConfigMap.contains("font"))
		{
			std::vector<int> codePoints = std::vector(CODEPOINTSCPP.begin(), CODEPOINTSCPP.end());

			uiStyle.font = LoadFontEx((pathsMap[fontConfigMap["font"]] + fontConfigMap["font"]).c_str(), fontSize, codePoints.data(), CODEPOINTCOUNT);
		}
		else
		{
			game->ICLog("Warning: Invalid config for font in: " + assetFolder + "Font.ictxt. Missing font");
		}
	}
}

void IC_assetManager::LoadCommonAssets()
{
	LoadTextures("Assets/Common/", true);
	LoadUIStyle("Assets/CommonUI/");
}

void IC_assetManager::UnloadAssets()
{
	for (const auto& texture : commonTextures)
	{
		UnloadTexture(texture.second);
	}
	for (const auto& sound : commonSounds)
	{
		UnloadSound(sound.second);
	}
}
