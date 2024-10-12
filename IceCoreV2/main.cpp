#include "raylib.h"

// IceCore helpers
#include "vectorHelpers.h"

// IceCore classes
#include "IC_graphicsManager.h"
#include "IC_visualDebugger.h"
#include "IC_inputSystem.h"

#include <format>

#ifndef _DEBUG

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#endif

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------


bool ToggleCursor(float value)
{
    if (value == 1.0f) // Is this a press?
    {
        if (IsCursorHidden())
        {
            ShowCursor();
            EnableCursor();
        }
        else
        {
            HideCursor();
            DisableCursor();
        }
    }
    return true; // Consume the input
}

int main(void)
{
    // Initialization
    const int screenWidth = 1200;
    const int screenHeight = 675;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "IceCoreEngineV2");

    SetTargetFPS(10000); // Lower this for your game, set this high for debugging.

    // IceCore classes
    IC_graphicsManager graphicsManager = IC_graphicsManager();
	IC_visualDebugger visualDebugger = IC_visualDebugger();
    IC_inputSystem inputSystem = IC_inputSystem();

#pragma region Input Mappings
    // Movement
    IC_mapping moveUp = IC_mapping({ IC_binding(KEY_W, 1.0f), IC_binding(KEY_S, -1.0f), IC_binding(GAMEPAD_AXIS_LEFT_Y, -1.0f) });
	IC_mapping moveRight = IC_mapping({ IC_binding(KEY_D, 1.0f), IC_binding(KEY_A, -1.0f), IC_binding(GAMEPAD_AXIS_LEFT_X, 1.0f) });

    inputSystem.AddMapping("MoveUp", moveUp, true);
	inputSystem.AddMapping("MoveRight", moveRight, true);

    // Rotation
    IC_mapping rotate = IC_mapping({ IC_binding(MOUSE_AXIS_X, 1.0f), IC_binding(GAMEPAD_AXIS_RIGHT_X, 1.0f), IC_binding(KEY_RIGHT, 1.0f), IC_binding(KEY_LEFT, -1.0f) });

	inputSystem.AddMapping("Rotate", rotate, true);

    // Showing cursor
    IC_mapping showCursor = IC_mapping({ IC_binding(KEY_C, 1.0f) });
    showCursor.AddDelegate(ToggleCursor);

    inputSystem.AddMapping("ShowCursor", showCursor, false);
#pragma endregion

    Texture2D circle = LoadTexture("Assets/Circle.png");
    Texture2D explosion = LoadTexture("Assets/Explosion.png");
    IC_sprite explosionSprite = IC_sprite(explosion, 4, 4, 16);
    Texture2D fire = LoadTexture("Assets/Fire.png");
    IC_sprite fireSprite = IC_sprite(fire, 1, 25, 25);
    Texture2D smoke = LoadTexture("Assets/Smoke.png");
    IC_sprite smokeSprite = IC_sprite(smoke, 7, 7, 45);

    visualDebugger.AddDebugString(IC_debugString("Hello", 5.0f, RED), false);


    HideCursor();
    DisableCursor();

    while (!WindowShouldClose())
    { 
        inputSystem.UpdateInputs(); // This should be called pretty early in a frame.

        visualDebugger.AddDebugString(IC_debugString(std::string("FPS: ") + std::to_string(GetFPS()), 0.0f), false);
        visualDebugger.AddDebugString(IC_debugString(std::string("Camera rotation: ") + std::to_string(graphicsManager.GetCameraRotation()), 0.0f), false);

        graphicsManager.AddToDrawQueue(IC_drawable(IC_sprite(circle), Vec2(0), Vec2(1.f), 0.f));

        graphicsManager.AddToDrawQueue(IC_drawable(explosionSprite, Vec2(-200.f, 200.f), Vec2(1.f), 0.0f, int(GetTime()*32) % 16));

        graphicsManager.AddToDrawQueue(IC_drawable(fireSprite, Vec2(-200.f), Vec2(1.f), 0.0f, int(GetTime() * 24) % 25));

        graphicsManager.AddToDrawQueue(IC_drawable(smokeSprite, Vec2(200.f), Vec2(1.f), 0.0f, int(GetTime() * 24) % 45));

        graphicsManager.SetCameraZoom(graphicsManager.GetCameraZoom() + GetMouseWheelMove() * 0.2f);
        float rotate = 0.0f;
        if (IsKeyDown(KEY_RIGHT))
        {
			rotate += 1.0f;
        }
        if(IsKeyDown(KEY_LEFT))
		{
			rotate -= 1.0f;
		}
        graphicsManager.SetCameraRotation(graphicsManager.GetCameraRotation() + inputSystem.GetAxisValue("Rotate") * -0.03f);
        
		graphicsManager.SetCameraPosition(graphicsManager.GetCameraPosition() + rotVec2(Vector2Normalize(Vec2(inputSystem.GetAxisValue("MoveRight"), inputSystem.GetAxisValue("MoveUp"))),graphicsManager.GetCameraRotation())*300.0f * GetFrameTime());
        

        BeginDrawing();
        graphicsManager.Draw();
        visualDebugger.DrawDebugStrings();
        EndDrawing();
    }

    UnloadTexture(circle);
	UnloadTexture(explosion);
	UnloadTexture(fire);
	UnloadTexture(smoke);
    CloseWindow();
    return 0;
}