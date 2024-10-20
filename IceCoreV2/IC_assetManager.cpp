#include "IC_assetManager.h"

#include "IC_game.h"

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

	return missingTexture;
}

Sound IC_assetManager::GetSound(std::string name)
{
	// In the future check the level assets first

	if (commonTextures.contains(name))
	{
		return commonSounds[name];
	}

	return missingSound;
}

void IC_assetManager::LoadTextures(std::string assetFolder, bool common)
{
	FilePathList paths = LoadDirectoryFilesEx(assetFolder.c_str(), NULL, true);

	// Loop over all paths
	for (int i = 0; i < paths.count; i++)
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
}

void IC_assetManager::LoadSounds(std::string assetFolder, bool common)
{
	FilePathList paths = LoadDirectoryFilesEx(assetFolder.c_str(), NULL, true);

	// Loop over all paths
	for (int i = 0; i < paths.count; i++)
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
}

void IC_assetManager::LoadCommonAssets()
{
	LoadTextures("Assets/Common/", true);
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
