#define NK_BUTTON_TRIGGER_ON_HOLD
#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include "IC_game.h"

void IC_game::Init(bool debug, bool useWindowDefaults)
{
	// Set the global game variable
	game = this;

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
	localisationSystem = std::make_unique<IC_localisationSystem>();
	localisationSystem.get()->LoadLocale(); // The default locale is set to "en"
	assetManager = std::make_unique<IC_assetManager>();
	assetManager.get()->LoadCommonAssets();
	nkCtx = InitNuklearEx(assetManager.get()->GetFont("DEFAULT"), DEFAULTFONTSIZE);
	uiTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

	// Call begin play
	BeginPlay();

	// Raylib loop
	while (!WindowShouldClose())
	{
		if (uiTexture.texture.width != GetScreenWidth() || uiTexture.texture.height != GetScreenHeight())
		{
			// Updating ui render texture if screen size changes
			UnloadRenderTexture(uiTexture);
			uiTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
		}
		nkCtx->delta_time_seconds = GetFrameTime();
		inputSystem->UpdateInputs(GetDeltaTime());
		objectSystem->Update();
		Tick(GetDeltaTime());

		hoveredElementCount = 0; // Reset the hover count
		DrawUI(GetDeltaTime()); // Tell the game to draw any UI

		// Draw anything the game wanted to draw into a render texture
		BeginTextureMode(uiTexture);
		ClearBackground(BLANK);
		DrawNuklear(nkCtx);
		EndTextureMode();

		BeginDrawing();

		graphicsManager->Draw();

		// Could allow user defined functions to be called here, but that's for the future

		// Debug lines and such will be drawn here

		// UI will be drawn here
		//uiManager->Draw(GetDeltaTime());
		
		// Draw the ui texture onto the screen
		DrawTextureRec(uiTexture.texture, { 0, 0, (float)uiTexture.texture.width, -(float)uiTexture.texture.height }, Vec2(0.0f), WHITE);

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

IC_localisationSystem* IC_game::GetLocalisationSystem()
{
	return localisationSystem.get();
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
