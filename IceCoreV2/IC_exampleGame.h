#pragma once

#include "IC_game.h"

class IC_exampleGame : public IC_game
{
public:
	IC_exampleGame() {};

	static bool ToggleCursor(float value);

	// Assets
	// To be replaced by the asset manager, where you can access sprites, textures, sounds, etc easily.
    // In the future it would be preferrable to automatically load assets from the assets folder and a level folder. 
    // Also automatically unloading level assets would be nice.
    Texture2D circle = Texture2D();
    Texture2D explosion = Texture2D();
    IC_sprite explosionSprite = IC_sprite();
    Texture2D fire = Texture2D();
    IC_sprite fireSprite = IC_sprite();
    Texture2D smoke = Texture2D();
    IC_sprite smokeSprite = IC_sprite();

protected:
	void Tick(float deltaTime) override;
    void BeginPlay() override;
};