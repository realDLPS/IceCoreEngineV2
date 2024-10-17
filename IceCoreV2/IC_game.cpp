#include "IC_game.h"

void IC_game::Init(bool debug, bool useWindowDefaults)
{
	if (useWindowDefaults)
	{
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);
		InitWindow(1200, 675, "IceCoreEngineV2");

		SetTargetFPS(120);
	}


	graphicsManager = std::make_unique<IC_graphicsManager>();
	inputSystem = std::make_unique<IC_inputSystem>();

	if (debug)
	{
		visualDebugger = std::make_unique<IC_visualDebugger>();
	}

	// Call begin play
	BeginPlay();

	// Raylib loop
	while (!WindowShouldClose())
	{
		inputSystem->UpdateInputs();
		Tick(GetFrameTime());



		BeginDrawing();

		graphicsManager->Draw();

		// Could allow user defined functions to be called here, but that's for the future

		// Debug lines and such will be drawn here

		// UI will be drawn here

		if (debug)
		{
			visualDebugger->DrawDebugStrings();
		}

		EndDrawing();
	}

	CloseWindow();
}

void IC_game::Unload()
{
	graphicsManager.reset();
	inputSystem.reset();
	visualDebugger.reset();
}

IC_graphicsManager* IC_game::GetGraphicsManager()
{
	return graphicsManager.get();
}

IC_inputSystem* IC_game::GetInputSystem()
{
	return inputSystem.get();
}

IC_visualDebugger* IC_game::GetVisualDebugger()
{
	return visualDebugger.get();
}

void IC_game::ICPrint(const IC_debugString& DebugString, bool Log)
{
	if(visualDebugger)
	{
		visualDebugger->AddDebugString(DebugString, Log);
	}
}

void IC_game::BeginPlay()
{
}

void IC_game::Tick(float deltaTime)
{
}
