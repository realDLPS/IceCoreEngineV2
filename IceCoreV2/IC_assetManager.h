#pragma once

#include "raylib.h"

// Standard library
#include <string>
#include <unordered_map>
#include <vector>

// Forward declarations
class IC_game;

// Manages assets for you.
// Multiple assets of the same type (Texture and Sound) cannot share a name.
class IC_assetManager
{
	friend class IC_game;

public:
	IC_assetManager() {};
	~IC_assetManager() { UnloadTexture(missingTexture); UnloadSound(missingSound); };

	// Unloads all assets before loading them again.
	// Loads common and level assets (once implemented).
	void ReloadAllAssets();

	// Returns the texture with the specified name.
	Texture2D GetTexture(std::string name);
	Sound GetSound(std::string name);

private:
	// Set by the game.
	IC_game* game = nullptr;

	Texture2D missingTexture = LoadTexture("Assets/MissingTexture.png");
	Sound missingSound = LoadSound("Assets/MissingSound.wav");

	const std::string textureExtensions[12] = { ".png", ".bmp", ".tga", ".jpg", ".psd", ".qoi", ".dds", ".hdr", ".ktx", ".astc", ".pkm", ".pvr" };
	const std::string soundExtensions[7] = { ".wav", ".ogg", ".mp3", ".flac", ".xm", ".mod", ".qoa" };

	std::unordered_map<std::string, Texture2D> commonTextures;
	std::unordered_map<std::string, Sound> commonSounds;

	void LoadTextures(std::string assetFolder, bool common = false);
	void LoadSounds(std::string assetFolder, bool common = false);

	// Loads all assets found in the Assets/Common folder.
	void LoadCommonAssets();

	/* To be implemented when levels are added
	// Loads all assets related to a level. Level folder is expected to be in the asset folder.
	// Unloads previously loaded level assets.
	void LoadLevelAssets(std::string levelName);
	*/

	// Unloads all loaded assets.
	// Called at the end of the game or when reloading assets.
	void UnloadAssets();
};