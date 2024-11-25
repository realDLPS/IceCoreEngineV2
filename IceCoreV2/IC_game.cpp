#include "IC_game.h"

void IC_game::Init(bool debug, bool useWindowDefaults)
{
	if (useWindowDefaults)
	{
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);
		InitWindow(1200, 675, "IceCoreEngineV2");

		SetTargetFPS(120);
	}

	InitAudioDevice();

	if (debug)
	{
		visualDebugger = std::make_unique<IC_visualDebugger>();
	}

	graphicsManager = std::make_unique<IC_graphicsManager>();
	inputSystem = std::make_unique<IC_inputSystem>();
	objectSystem = std::make_unique<IC_objectSystem>();
	objectSystem.get()->game = this;
	assetManager = std::make_unique<IC_assetManager>();
	assetManager.get()->game = this;
	assetManager.get()->LoadCommonAssets();
	uiManager = std::make_unique<IC_uiManager>();
	uiManager.get()->game = this;

	// Call begin play
	BeginPlay();

	// Raylib loop
	while (!WindowShouldClose())
	{
		inputSystem->UpdateInputs();
		objectSystem->Update();

		Tick(GetDeltaTime());

		BeginDrawing();

		graphicsManager->Draw();

		// Could allow user defined functions to be called here, but that's for the future

		// Debug lines and such will be drawn here

		// UI will be drawn here
		uiManager->Draw(GetDeltaTime());
		DrawUI(GetDeltaTime());

		if (debug)
		{
			visualDebugger->DrawDebugStrings();
		}

		EndDrawing();
	}
	EndPlay();

	Unload();
	CloseWindow();
}

void IC_game::Unload()
{
	graphicsManager.reset();
	inputSystem.reset();
	visualDebugger.reset();

	uiManager.get()->Unload();
	uiManager.reset();

	objectSystem.get()->Unload();
	objectSystem.reset();

	assetManager.get()->UnloadAssets();
	assetManager.reset();
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

IC_objectSystem* IC_game::GetObjectSystem()
{
	return objectSystem.get();
}

IC_assetManager* IC_game::GetAssetManager()
{
	return assetManager.get();
}

IC_uiManager* IC_game::GetUiManager()
{
	return uiManager.get();
}

void IC_game::ICPrint(const IC_debugString& DebugString, bool Log)
{
	if(visualDebugger)
	{
		visualDebugger->AddDebugString(DebugString, Log);
	}
}

void IC_game::ICLog(const std::string& DebugString)
{
	if(visualDebugger)
	{
		visualDebugger->LogDebugString(DebugString);
	}
}

float IC_game::GetDeltaTime()
{
	if (paused)
	{
		return 0.0f;
	}
	return GetFrameTime() * timeDilation;
}

void IC_game::SetTimeDilation(float newTimeDilation)
{
	timeDilation = newTimeDilation;
}

float IC_game::GetTimeDilation()
{
	return timeDilation;
}

void IC_game::SetPaused(bool newPaused)
{
	paused = newPaused;
}

bool IC_game::GetPaused()
{
	return paused;
}
