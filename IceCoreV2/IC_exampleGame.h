#pragma once

#include "IC_game.h"

class IC_exampleGame : public IC_game
{
public:
	IC_exampleGame() {};

	bool ToggleCursor(float value);

	// Assets
	// To be replaced by the asset manager, where you can access sprites, textures, sounds, etc easily.
    // In the future it would be preferrable to automatically load assets from the assets folder and a level folder. 
    // Also automatically unloading level assets would be nice.
    IC_sprite explosionSprite = IC_sprite();
    IC_sprite fireSprite = IC_sprite();
    IC_sprite smokeSprite = IC_sprite();

protected:
	void Tick(float deltaTime) override;
    void BeginPlay() override;
    void EndPlay() override;
};