#pragma once

#include "raylib.h"

// Standard library
#include <memory>

// IceCore classes
#include "IC_graphicsManager.h"
#include "IC_visualDebugger.h"
#include "IC_inputSystem.h"

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

	std::unique_ptr<IC_visualDebugger> visualDebugger;
public:
	// Call to start the game.
	// Creates IceCore classes and starts ticking.
	//
	// Set initialization variables like debug before this.
	void Init(bool debug = false, bool useWindowDefaults = true);

	// Call to stop the game.
	// Anything created by this class will be destroyed.
	void Unload();

	// System getters

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
protected:

	virtual void BeginPlay();
	// Called each frame.
	virtual void Tick(float deltaTime);
};