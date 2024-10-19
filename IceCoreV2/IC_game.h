#pragma once

#include "raylib.h"

// Standard library
#include <memory>

// IceCore classes
#include "IC_graphicsManager.h"
#include "IC_visualDebugger.h"
#include "IC_inputSystem.h"
#include "IC_objectSystem.h"

// This game class creates other IceCore classes for you and gives you access to them.
// Also abstracts some raylib things away to be more similar to Unreal Engine.
//
// This class is somewhat comparable to the game instance in Unreal Engine.
class IC_game
{
public:
	IC_game() {};

private:
	/// IceCore objects
	std::unique_ptr<IC_graphicsManager> graphicsManager;
	std::unique_ptr<IC_inputSystem> inputSystem;
	std::unique_ptr<IC_objectSystem> objectSystem;

	std::unique_ptr<IC_visualDebugger> visualDebugger;

	// Can be used to speed up or slow down the game.
	// 1.0 is normal speed.
	float timeDilation = 1.0f;

	// Can be used to pause the game without messing with time dilation.
	bool paused = false;
public:
	// Call to start the game.
	// Creates IceCore classes and starts ticking.
	//
	// The game loop starts at the end of this function and anything after this will run after the game is stopped.
	void Init(bool debug = false, bool useWindowDefaults = true);

	// Call to stop the game.
	// Anything created by this class will be destroyed.
	void Unload();



	// Returns pointer to the graphics manager, abbr: GfxMgr
	IC_graphicsManager* GetGraphicsManager(); 
	// Shorthand for GetGraphicsManager()
	inline IC_graphicsManager* GfxMgr() { return GetGraphicsManager(); } 

	// Returns pointer to the input system, abbr: InpSys
	IC_inputSystem* GetInputSystem(); 
	// Shorthand for GetInputSystem()
	inline IC_inputSystem* InpSys() { return GetInputSystem(); } 

	// Returns a nullptr if debugging is disabled, abbr: VisDbg
	IC_visualDebugger* GetVisualDebugger(); 
	// Shorthand for GetVisualDebugger()
	inline IC_visualDebugger* VisDbg() { return GetVisualDebugger(); } 



	// Wrapper function for the visual debugger 
	// Checks if debugging is enabled before trying to add a debug string.
	void ICPrint(const IC_debugString& DebugString, bool Log);



	// Get frame time affected by time dilation.
	// Use GetFrameTime() if you don't want time dilation.
	float GetDeltaTime();

	// Change the time dilation of the game.
	// For example, if you want the game to run at 2x speed, set it to 2.0f.
	void SetTimeDilation(float newTimeDilation);
	// Self-explanatory
	float GetTimeDilation();

	// Pausing or unpausing the game.
	void SetPaused(bool newPaused);
	// Self-explanatory
	bool GetPaused();
protected:
	// Called at the start of the game.
	virtual void BeginPlay() = 0;
	// Called each frame.
	virtual void Tick(float deltaTime) = 0;

	// Called when the game is being closed.
	virtual void EndPlay() = 0;
};