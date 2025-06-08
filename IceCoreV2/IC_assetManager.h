#pragma once

#include "raylib.h"

// Standard library
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

// Other
#include "IC_graphicsStructs.h"
#include "IC_font.h"

// Size is rounded to reduce amount of variants that get created
#define ICFONT(name, size) game->AstMgr()->GetICFont(name, std::round(size * 2.f) / 2.f).nkFont

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
	Font GetFont();

	static std::map<std::string, std::string> ParseStringToConfig(std::string configString);

	static std::string LoadFileAsText(std::string path);

	// Loads a font and adds it to the available fonts
	// Returns true if the font was added
	//
	// The parameter name is expected to have a corresponding [name].ictxt in Assets/Fonts/
	bool LoadFont(std::string name, float size);


	IC_font GetICFont(std::string name, float size);

private:
	Texture2D missingTexture = LoadTexture("Assets/MissingTexture.png");
	Sound missingSound = LoadSound("Assets/MissingSound.wav");

	IC_uiStyle uiStyle = IC_uiStyle();
	std::unordered_map<std::string, std::unordered_map<float, IC_font>> fonts;
	std::map<std::string, Font*> raylibFonts;

	const std::string textureExtensions[12] = { ".png", ".bmp", ".tga", ".jpg", ".psd", ".qoi", ".dds", ".hdr", ".ktx", ".astc", ".pkm", ".pvr" };
	const std::string soundExtensions[7] = { ".wav", ".ogg", ".mp3", ".flac", ".xm", ".mod", ".qoa" };

	std::unordered_map<std::string, Texture2D> commonTextures;
	std::unordered_map<std::string, Sound> commonSounds;

	// Loads all files in a directory to a map
	// 
	// Key is file name, value is file path
	std::map<std::string, std::string> LoadDirFileList(const char* path, const char* filter, bool scanSubdirs);

	void LoadTextures(std::string assetFolder, bool common = false);
	void LoadSounds(std::string assetFolder, bool common = false);
	void LoadUIStyle(std::string assetFolder);
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